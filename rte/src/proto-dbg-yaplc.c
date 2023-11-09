/* @page plc_debug.c
 *       PLC411::RTE
 *       BEREMIZ YAPLC Debug protocol
 *       2020-2023, atgroup09@gmail.com
 */

#include "proto-dbg-yaplc.h"


dbg_t dbg;

plc_dbg_proto_t plc_dbg_ctrl = { .state = GET_CMD };

static dbg_fifo_t dbg_serial_rx;


static int dbg_fifo_write_byte(dbg_fifo_t * fifo, uint8_t d)
{
    if (DBG_FIFO_SIZE > fifo->bytes)
    {
        fifo->buf[fifo->write++] = d;
        fifo->write %= DBG_FIFO_SIZE;
        fifo->bytes++;
        return 1; // Success
    }
    else
    {
        return 0; // Fail
    }
}

static int dbg_fifo_read_byte(dbg_fifo_t * fifo, uint8_t *d)
{
    if (0 != fifo->bytes)
    {
        *d = fifo->buf[fifo->read++];
        fifo->read %= DBG_FIFO_SIZE;
        fifo->bytes--;
        return 1; //Success
    }
    else
    {
        return 0; //Fail
    }
}

static void dbg_serial_start_transfer(uint8_t DirIn)
{
	if(DirIn == DBG_SERIAL_RX)
	{
		if(dbg.RxState == DBG_SERIAL_FREE)
		{
			dbg.RxState = DirIn;
			dbg.RxCnt   = 0;
			//unknown response size, then used maximum buffer size
			//real response size will be return from IDLE-callback
	        PlcUart_StartReceive(dbg.Handler, dbg.RxBuff, DBG_SERIAL_BUFF_SIZE);
		}
	}
    else if(DirIn == DBG_SERIAL_TX)
    {
    	if(dbg.TxState == DBG_SERIAL_FREE)
    	{
        	dbg.TxState = DirIn;
            PlcUart_StartTransmit(dbg.Handler, dbg.TxBuff, dbg.TxCnt);
    	}
	}
}

int dbg_serial_write(unsigned char *data_in, unsigned short data_sz)
{
	int res = 0;

	if(dbg.TxState == DBG_SERIAL_FREE)
	{
		//copy input data into Tx-buffer
		res = Type_CopyBytes(data_in, data_sz, dbg.TxBuff);
	    if(res)
	    {
	    	dbg.TxCnt = data_sz;
	    	dbg_serial_start_transfer(DBG_SERIAL_TX);
	    }
	}

    return res;
}

int dbg_serial_read(unsigned char *data_in, unsigned short data_sz)
{
	int res = 0;

	if(dbg.RxState == DBG_SERIAL_FREE)
	{
		if(dbg.RxCnt)
		{
			for(uint8_t i=0; i<dbg.RxCnt; i++)
			{
				if(!dbg_fifo_write_byte(&dbg_serial_rx, dbg.RxBuff[i])) break;
			}
			//ready new Rx-transfer
			dbg_serial_start_transfer(DBG_SERIAL_RX);
		}
	}

    while(data_sz--)
    {
        if(dbg_fifo_read_byte(&dbg_serial_rx, data_in))
        {
        	data_in++;
            res++;
        }
        else
        {
            break;
        }
    }

    return res;
}


void dbg_init(void)
{
    plc_dbg_ctrl.state     = GET_CMD;
    plc_dbg_ctrl.timer     = 0;
    plc_dbg_ctrl.data_hook = (void(*)(void))0;

    dbg.SlaveID = PLC_COM1_SLAVE_ADDR;
    dbg.RxCnt   = 0;
    dbg.TxCnt   = 0;
    dbg.RxState = DBG_SERIAL_FREE;
    dbg.TxState = DBG_SERIAL_FREE;
    dbg.Handler = &PLC_UART1;

    dbg_serial_start_transfer(DBG_SERIAL_RX);
}


void dbg_handler(void)
{
    if(!PLC_APP_CURR) return;

    //Check timer, break connection on timeout
    if (PLC_DBG_TIMER_THR < PLC_TIMER(plc_dbg_ctrl.timer))
    {
        plc_dbg_ctrl.state = GET_CMD;
        PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);
        plc_dbg_ctrl.data_hook = (void(*)(void))0;
    }

    switch(plc_dbg_ctrl.state)
    {
        case GET_CMD:
        default:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(dbg_serial_read(&plc_dbg_ctrl.cmd, 1))
            {
                //Handle command stage 1 (Immediate actions)
                switch (plc_dbg_ctrl.cmd)
                {
                    case DBG_CMD_START:
                    {
                        PlcApp_Start();
                    }
                    break;

                    case DBG_CMD_STOP:
                    {
                        PlcApp_Stop();
                    }
                    break;
                }

                // Answer to host
                plc_dbg_ctrl.state = PUT_ACK;
                plc_dbg_ctrl.tr_buf.data[0] = plc_dbg_ctrl.cmd;
                plc_dbg_ctrl.tr_buf.data[1] = PLC_APP_STATE;
                plc_dbg_ctrl.tmp_len        = 2;
                plc_dbg_ctrl.tmp            = &plc_dbg_ctrl.tr_buf.data[0];
            }
        }
        break;

        case PUT_ACK:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res             = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp     += write_res;
                plc_dbg_ctrl.tmp_len -= write_res;
            }
            else
            {
                plc_dbg_ctrl.state = PARSE_CMD;
            }
        }
        break;

        case PARSE_CMD:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            //Handle command stage 2
            switch(plc_dbg_ctrl.cmd)
            {
                case DBG_CMD_START:
                case DBG_CMD_STOP:
                {
                    plc_dbg_ctrl.state = GET_CMD;
                }
                break;

                case DBG_CMD_RESET:
                {
                    //Enter dbg mode if not there
                    //plc_dbg_mode = true;
                    //plc_backup_invalidate();
                    //plc_boot_mode_enter();
                }
                break;

                case DBG_CMD_GET_V:
                {
                    plc_dbg_ctrl.state     = GET_DEBUG_DATA;
                    plc_dbg_ctrl.data_hook = PLC_APP_CURR->dbg_data_free; //Free buffer when transfer ends.
                }
                break;

                case DBG_CMD_SET_V:
                {
                    plc_dbg_ctrl.state = GET_DATA_LEN;
                    PLC_APP_CURR->dbg_suspend(0);
                    PLC_APP_CURR->dbg_vars_reset();
                    //Get 4 byte data length, little endian
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.data_len;
                }
                break;

                case DBG_CMD_GET_ID:
                {
                    plc_dbg_ctrl.state = PUT_ID_LEN;
                    //Transfer 4 byte data length, little endian
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.data_len;
                    //Than Transfer 32 bytes of data
                    plc_dbg_ctrl.data_len = 32;
                    plc_dbg_ctrl.data = (uint8_t *)PLC_APP_CURR->id;
                }
                break;

                case DBG_CMD_GET_LC:
                {
                    uint8_t i;
                    for (i = 0; i < 4; i++)
                    {
                        plc_dbg_ctrl.tr_buf.log_cnt[i] = PLC_APP_CURR->log_cnt_get(i);
                    }
                    plc_dbg_ctrl.state = PUT_LC_LEN;
                    //Transfer 4 byte data length, little endian
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.data_len;
                    //Than Transfer 32 bytes of data
                    plc_dbg_ctrl.data_len = 16;
                    plc_dbg_ctrl.data = (uint8_t *)&plc_dbg_ctrl.tr_buf.log_cnt[0];
                }
                break;

                case DBG_CMD_GET_LM:
                {
                    plc_dbg_ctrl.state = GET_MSG_LEVEL;
                }
                break;

                case DBG_CMD_CLR_LM:
                {
                    plc_dbg_ctrl.state = GET_CMD;
                    PLC_APP_CURR->log_cnt_reset();
                }
                break;

                case DBG_CMD_IDLE:
                default:
                {
                    plc_dbg_ctrl.state = GET_CMD;
                }
                break;

                case DBG_CMD_SET_RTC:
                {
                    plc_dbg_ctrl.state = GET_RTC_DATA;
                    plc_dbg_ctrl.data_len = 6;
                    plc_dbg_ctrl.data = (uint8_t *)&plc_dbg_ctrl.tr.set_rtc;
                }
                break;
            }
        }
        break;
        //==========================================================================================
        case GET_RTC_DATA:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.data_len)
            {
                int read_res;
                //Must read before timeout!
                read_res = dbg_serial_read(plc_dbg_ctrl.data, plc_dbg_ctrl.data_len);
                plc_dbg_ctrl.data     += read_res;
                plc_dbg_ctrl.data_len -= read_res;
            }
            else
            {
                /*
                tm new_time;
                //Set RTC
                new_time.tm_year = plc_dbg_ctrl.tr.set_rtc.year;
                new_time.tm_mon  = plc_dbg_ctrl.tr.set_rtc.mon;
                new_time.tm_day  = plc_dbg_ctrl.tr.set_rtc.day;
                new_time.tm_hour = plc_dbg_ctrl.tr.set_rtc.hour;
                new_time.tm_min  = plc_dbg_ctrl.tr.set_rtc.min;
                new_time.tm_sec  = plc_dbg_ctrl.tr.set_rtc.sec;
                plc_rtc_dt_set(&new_time);
                */
                plc_dbg_ctrl.state = GET_CMD;
            }
        }
        break;

        case GET_DEBUG_DATA:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(0 == PLC_APP_CURR->dbg_data_get(&plc_dbg_ctrl.tr.get_val.tick, (long unsigned int *)&plc_dbg_ctrl.data_len, (void **)&plc_dbg_ctrl.data))
            {
                //Transfer data
                plc_dbg_ctrl.data_len += 4; //Must transfer tick
            }
            else
            {
                plc_dbg_ctrl.data_len = 0; //No data available
            }
            plc_dbg_ctrl.state   = PUT_DEBUG_LEN;
            plc_dbg_ctrl.tmp_len = 4;
            plc_dbg_ctrl.tmp     = (uint8_t *)&plc_dbg_ctrl.data_len;
        }
        break;

        case PUT_DEBUG_LEN:
        {
            PLC_CLEAR_TIMER (plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
            }
            else
            {
                if(0 < plc_dbg_ctrl.data_len)
                {
                    //When length transfered transfer data
                    plc_dbg_ctrl.state = PUT_DEBUG_TICK;
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.get_val.tick;
                }
                else
                {
                    plc_dbg_ctrl.state = GET_CMD;
                }
            }
        }
        break;

        case PUT_DEBUG_TICK:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp      += write_res;
                plc_dbg_ctrl.tmp_len  -= (uint8_t)write_res;
                plc_dbg_ctrl.data_len -= write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_DATA;
            }
        }
        break;
        //==========================================================================================
        case GET_DATA_LEN:
        {
            if(plc_dbg_ctrl.tmp_len)
            {
                int read_res;
                //Must read before timeout!
                read_res = dbg_serial_read(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp     += read_res;
                plc_dbg_ctrl.tmp_len -= read_res;
            }
            else
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

                if (0 < plc_dbg_ctrl.data_len)
                {
                    plc_dbg_ctrl.state = GET_VAR_IDX;
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp     = (uint8_t *)&plc_dbg_ctrl.tr.set_val.var_idx;
                }
                else
                {
                    PLC_APP_CURR->dbg_resume();
                    plc_dbg_ctrl.state = GET_CMD;
                }
            }
        }
        break;

        case GET_VAR_IDX:
        {
            if(plc_dbg_ctrl.tmp_len)
            {
                //Must read before timeout!
                int read_res;
                read_res = dbg_serial_read(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp         += read_res;
                plc_dbg_ctrl.tmp_len     -= read_res;
                plc_dbg_ctrl.data_len    -= read_res;
            }
            else
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);
                plc_dbg_ctrl.state = GET_FORCE_LEN;
            }
        }
        break;

        case GET_FORCE_LEN:
        {
            if(dbg_serial_read(&plc_dbg_ctrl.tmp_len, 1))
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

                plc_dbg_ctrl.data_len--;
                if (0 == plc_dbg_ctrl.tmp_len)
                {
                    //No force data
                    PLC_APP_CURR->dbg_var_register(plc_dbg_ctrl.tr.set_val.var_idx, (void *)0);

                    if (0 >= plc_dbg_ctrl.data_len)
                    {
                        //When all data transfered get next command
                        PLC_APP_CURR->dbg_resume();
                        plc_dbg_ctrl.state = GET_CMD;
                    }
                    else
                    {
                        plc_dbg_ctrl.state = GET_VAR_IDX;
                        plc_dbg_ctrl.tmp_len = 4;
                        plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.set_val.var_idx;
                    }
                }
                else
                {
                    plc_dbg_ctrl.state = GET_FORCE_DATA;
                    plc_dbg_ctrl.data = (uint8_t *)&plc_dbg_ctrl.tr_buf.data[0];
                }
            }
        }
        break;

        case GET_FORCE_DATA:
        {
            if (plc_dbg_ctrl.tmp_len)
            {
                int read_res;
                //Must read before timeout!
                read_res = dbg_serial_read(plc_dbg_ctrl.data, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.data        += read_res;
                plc_dbg_ctrl.tmp_len     -= (uint8_t)read_res;
                plc_dbg_ctrl.data_len    -= read_res;
                //Panic on error
            }
            else
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

                PLC_APP_CURR->dbg_var_register(plc_dbg_ctrl.tr.set_val.var_idx, &plc_dbg_ctrl.tr_buf.data[0]);
                if (0 >= plc_dbg_ctrl.data_len)
                {
                    //When all data transfered get next command
                    PLC_APP_CURR->dbg_resume();
                    plc_dbg_ctrl.state = GET_CMD;
                }
                else
                {
                    plc_dbg_ctrl.state = GET_VAR_IDX;
                    plc_dbg_ctrl.tmp_len = 4;
                    plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.set_val.var_idx;
                }
            }
        }
        break;
        //==========================================================================================
        case PUT_ID_LEN:
        //==========================================================================================
        case PUT_LC_LEN:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_DATA;
            }
        }
        break;
        //==========================================================================================
        case GET_MSG_LEVEL:
        {
            if(dbg_serial_read(&plc_dbg_ctrl.tr.get_log_msg.level, 1))
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);
                plc_dbg_ctrl.state = GET_MSG_ID;
                plc_dbg_ctrl.tmp_len = 4;
                plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.get_log_msg.msg_id;
            }
        }
        break;

        case GET_MSG_ID:
        {
            if(plc_dbg_ctrl.tmp_len)
            {
                int read_res;
                //Must read before timeout
                read_res = dbg_serial_read(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp         += read_res;
                plc_dbg_ctrl.tmp_len      -= read_res;
                plc_dbg_ctrl.data_len     -= read_res;
            }
            else
            {
                PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);
                plc_dbg_ctrl.state    = PUT_MSG_LEN;

                plc_dbg_ctrl.data_len = PLC_APP_CURR->log_msg_get(
                                            plc_dbg_ctrl.tr.get_log_msg.level,
                                            plc_dbg_ctrl.tr.get_log_msg.msg_id,
                                            &plc_dbg_ctrl.tr_buf.log_msg[0],
                                            256,
                                            &plc_dbg_ctrl.tr.get_log_msg.tick,
                                            &plc_dbg_ctrl.tr.get_log_msg.sec,
                                            &plc_dbg_ctrl.tr.get_log_msg.nsec
                                       );

                plc_dbg_ctrl.data_len += 12; // Tick+Sec+NSec+Data
                plc_dbg_ctrl.data = (uint8_t *)&plc_dbg_ctrl.tr_buf.log_msg[0];

                plc_dbg_ctrl.tmp_len = 4;
                plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.data_len;
            }
        }
        break;

        case PUT_MSG_LEN:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_MSG_TICK;

                plc_dbg_ctrl.tmp_len = 4;
                plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.get_log_msg.tick;
            }
        }
        break;

        case PUT_MSG_TICK:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
                plc_dbg_ctrl.data_len -= write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_MSG_SEC;

                plc_dbg_ctrl.tmp_len = 4;
                plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.get_log_msg.sec;
            }
        }
        break;

        case PUT_MSG_SEC:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
                plc_dbg_ctrl.data_len -= write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_MSG_NSEC;

                plc_dbg_ctrl.tmp_len = 4;
                plc_dbg_ctrl.tmp = (uint8_t *)&plc_dbg_ctrl.tr.get_log_msg.nsec;
            }
        }
        break;

        case PUT_MSG_NSEC:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(plc_dbg_ctrl.tmp_len)
            {
                int write_res;
                write_res = dbg_serial_write (plc_dbg_ctrl.tmp, plc_dbg_ctrl.tmp_len);
                plc_dbg_ctrl.tmp += write_res;
                plc_dbg_ctrl.tmp_len -= (uint8_t)write_res;
                plc_dbg_ctrl.data_len -= write_res;
            }
            else
            {
                //When length transfered transfer data
                plc_dbg_ctrl.state = PUT_DATA;
            }
        }
        break;
        //==========================================================================================
        case PUT_DATA:
        {
            PLC_CLEAR_TIMER(plc_dbg_ctrl.timer);

            if(0 < plc_dbg_ctrl.data_len)
            {
                int write_res;
                write_res = dbg_serial_write(plc_dbg_ctrl.data, plc_dbg_ctrl.data_len);
                plc_dbg_ctrl.data += write_res;
                plc_dbg_ctrl.data_len -= write_res;
            }
            else
            {
                //When all data transfered get next command
                if (plc_dbg_ctrl.data_hook)
                {
                    plc_dbg_ctrl.data_hook();
                    plc_dbg_ctrl.data_hook = (void(*)(void))0;
                }
                plc_dbg_ctrl.state = GET_CMD;
            }
        }
        break;
    }
}
