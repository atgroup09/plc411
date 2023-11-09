/* @page rtos-data.c
 *       PLC411::RTE
 *       RTOS-task T_DATA
 *       2022, atgroup09@gmail.com
 */

#include "rtos-data.h"


#ifdef RTE_MOD_DI

/** @brief  Send data from DI_DATA_Q into REG
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DI_DATA_Q_ToReg(const PlcDI_Q_t *DataIn)
{
#ifdef DEBUG_LOG_DI_DATA_Q
	DebugLog("RTOS_DI_DATA_Q_ToReg\n");
#endif // DEBUG_LOG_DI_DATA_Q

    if(DataIn)
    {
        if(DataIn->Ch < PLC_DI_SZ)
        {
            uint8_t  BuffBy;
            uint16_t BuffWo;
            uint32_t BuffDWo;

            switch(DataIn->ID)
            {
				case PLC_DI_Q_ID_MODE:
                    BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_MODE__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_NORM_VAL:
                    BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_NORM_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_CNTR_VAL:
					BuffDWo = DataIn->Val;
                    REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffDWo);
					break;

				case PLC_DI_Q_ID_CNTR_SETPOINT:
					BuffDWo = DataIn->Val;
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffDWo);
					break;

				case PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_CNTR_SETPOINT_REACHED:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_REACHED__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_TACH_VAL:
					BuffWo = (uint16_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_TACH_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);
					break;

				case PLC_DI_Q_ID_TACH_SETPOINT:
					BuffWo = (uint16_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);
					break;

				case PLC_DI_Q_ID_TACH_SETPOINT_ALLOW:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_ALLOW__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_TACH_SETPOINT_REACHED:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_REACHED__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_RESET:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_RESET__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_STATUS:
					BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_DI_STATUS__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_DI_Q_ID_FILTER_DELAY:
					BuffBy = DataIn->Val;
                    REG_CopyRegByPos((REG_DI_FILTER_DELAY__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;
            }
#ifdef DEBUG_LOG_DI_DATA_Q
            DebugLog("DI[%d].ID=%d .Val=%d\n\n", DataIn->Ch, DataIn->ID, DataIn->Val);
#endif //DEBUG_LOG_DI_DATA_Q
        }
    }
}

/** @brief  Send data into RTOS_DI_Q
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DI_Q_Send(const REG_t *DataIn)
{
#ifdef DEBUG_LOG_DI_Q
	DebugLog("RTOS_DI_Q_Send\n");
#endif // DEBUG_LOG_DI_Q

	PlcDI_Q_t QueueData;
	ANY32_uwt BuffAny32;
	uint8_t   BuffBy;

	if(DataIn)
	{
		Type_InitWords(BuffAny32.words, TYPE_FLOAT_WSZ, 0);
		QueueData.ID = PLC_DI_Q_ID_NONE;

        switch(DataIn->GID)
        {
        	case REG_DI_TACH_SETPOINT__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_TACH_SETPOINT;
            		QueueData.Val = (uint32_t)BuffAny32.data_word;
        		}
				break;

        	case REG_DI_TACH_SETPOINT_ALLOW__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_TACH_SETPOINT_ALLOW;
            		QueueData.Val = (uint32_t)BuffAny32.data_byte;
        		}
				break;

        	case REG_DI_CNTR_SETPOINT__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_CNTR_SETPOINT;
            		QueueData.Val = BuffAny32.data_dword;
        		}
				break;

        	case REG_DI_CNTR_SETPOINT_ALLOW__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_CNTR_SETPOINT_ALLOW;
            		QueueData.Val = (uint32_t)BuffAny32.data_byte;
        		}
				break;

        	case REG_DI_MODE__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_MODE;
            		QueueData.Val = (uint32_t)BuffAny32.data_byte;
        		}
				break;

        	case REG_DI_RESET__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_RESET;
            		QueueData.Val = (uint32_t)BuffAny32.data_byte;
        		}
				break;

        	case REG_DI_FILTER_DELAY__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DI_Q_ID_FILTER_DELAY;
            		QueueData.Val = (uint32_t)BuffAny32.data_dword;
        		}
				break;
        }

		if(QueueData.ID != PLC_DI_Q_ID_NONE)
		{
			//@TODO Write Retain-data into FLASH/EEPROM
			//      if DataIn->Retain != REG_RETAIN_NONE
			//      ...

			//Send data into RTOS_DI_Q (not-blocking)
			xQueueSendToBack(RTOS_DI_Q, &QueueData, 0);

#ifdef DEBUG_LOG_DI_Q
            DebugLog("DI[%d].ID=%d .Val=%d\n\n", QueueData.Ch, QueueData.ID, QueueData.Val);
#endif //DEBUG_LOG_DI_Q
		}
	}
}

#endif //RTE_MOD_DI


#ifdef RTE_MOD_DO

/** @brief  Send data from DO_DATA_Q into REG
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DO_DATA_Q_ToReg(const PlcDO_Q_t *DataIn)
{
#ifdef DEBUG_LOG_DO_DATA
	DebugLog("RTOS_DO_DATA_Q_ToReg\n");
#endif // DEBUG_LOG_DO_DATA

    if(DataIn)
    {
        if(DataIn->Ch < PLC_DO_SZ)
        {
            uint8_t  BuffBy;
            float    BuffFlo;

            switch(DataIn->ID)
            {
            	case PLC_DO_Q_ID_MODE:
            		BuffBy = (uint8_t)DataIn->Val;
            		REG_CopyRegByPos((REG_DO_MODE__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

            	case PLC_DO_Q_ID_NORM_VAL:
            		BuffBy = (uint8_t)DataIn->Val;
            		REG_CopyRegByPos((REG_DO_NORM_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
            		break;

            	case PLC_DO_Q_ID_FAST_VAL:
            		BuffBy = (uint8_t)DataIn->Val;
            		REG_CopyRegByPos((REG_DO_FAST_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
            		break;

            	case PLC_DO_Q_ID_PWM_T:
            		BuffFlo = DataIn->Val;
            		REG_CopyRegByPos((REG_DO_PWM_PERIOD__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffFlo);
            		break;

            	case PLC_DO_Q_ID_PWM_D:
            		BuffFlo = DataIn->Val;
            		REG_CopyRegByPos((REG_DO_PWM_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffFlo);
            		break;

            	case PLC_DO_Q_ID_PWM_ALLOW:
            		BuffBy = (uint8_t)DataIn->Val;
            		REG_CopyRegByPos((REG_DO_PWM_ALLOW__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
            		break;

            	case PLC_DO_Q_ID_STATUS:
            		BuffBy = (uint8_t)DataIn->Val;
            		REG_CopyRegByPos((REG_DO_STATUS__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
            		break;
            }
#ifdef DEBUG_LOG_DO_DATA
            DebugLog("DO[%d].ID=%d .Val=%f\n\n", DataIn->Ch, DataIn->ID, DataIn->Val);
#endif //DEBUG_LOG_DO_DATA
        }
    }
}

/** @brief  Send data into RTOS_DO_Q
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_DO_Q_Send(const REG_t *DataIn)
{
#ifdef DEBUG_LOG_DO_DATA
	DebugLog("RTOS_DO_Q_Send\n");
#endif // DEBUG_LOG_DO_DATA

	PlcDO_Q_t QueueData;
	ANY32_uwt BuffAny32;
	uint8_t   BuffBy;

	if(DataIn)
	{
		Type_InitWords(BuffAny32.words, TYPE_FLOAT_WSZ, 0);
		QueueData.ID = PLC_DO_Q_ID_NONE;

        switch(DataIn->GID)
        {
			case REG_DO_MODE__GID:
				if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
				{
					QueueData.Ch  = DataIn->iGroup;
					QueueData.ID  = PLC_DO_Q_ID_MODE;
					QueueData.Val = (float)BuffAny32.data_byte;
				}
				break;

        	case REG_DO_NORM_VAL__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_NORM_VAL;
            		QueueData.Val = (float)BuffAny32.data_byte;
        		}
				break;

        	case REG_DO_FAST_VAL__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_FAST_VAL;
            		QueueData.Val = (float)BuffAny32.data_byte;
        		}
				break;

        	case REG_DO_PWM_PERIOD__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_PWM_T;
            		QueueData.Val = BuffAny32.data_float;
        		}
				break;

        	case REG_DO_PWM_VAL__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_PWM_D;
            		QueueData.Val = BuffAny32.data_float;
        		}
				break;

        	case REG_DO_PWM_ALLOW__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_PWM_ALLOW;
            		QueueData.Val = (float)BuffAny32.data_byte;
        		}
				break;

        	case REG_DO_STATUS__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_DO_Q_ID_STATUS;
            		QueueData.Val = (float)BuffAny32.data_byte;
        		}
				break;
        }

		if(QueueData.ID != PLC_DO_Q_ID_NONE)
		{
			//@TODO Write Retain-data into FLASH/EEPROM
			//      if DataIn->Retain != REG_RETAIN_NONE
			//      ...

			//Send data into RTOS_DO_Q (not-blocking)
			xQueueSendToBack(RTOS_DO_Q, &QueueData, 0);

#ifdef DEBUG_LOG_DO_DATA
            DebugLog("DO[%d].ID=%d .Val=%d\n\n", QueueData.Ch, QueueData.ID, QueueData.Val);
#endif //DEBUG_LOG_DO_DATA
		}
	}
}

#endif //RTE_MOD_DO


#ifdef RTE_MOD_AI

/** @brief  Send data from AI_DATA_Q into REG
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_AI_DATA_Q_ToReg(const PlcAI_Q_t *DataIn)
{
#ifdef DEBUG_LOG_AI_DATA_Q
	DebugLog("RTOS_AI_DATA_Q_ToReg\n");
#endif // DEBUG_LOG_AI_DATA_Q

    if(DataIn)
    {
        if(DataIn->Ch < PLC_AI_SZ)
        {
            uint8_t BuffBy;
            float   BuffFlo;

            switch(DataIn->ID)
            {
				case PLC_AI_Q_ID_MODE:
                    BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_AI_MODE__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;

				case PLC_AI_Q_ID_VAL:
					BuffFlo = DataIn->Val;
                    REG_CopyRegByPos((REG_AI_VAL__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffFlo);
					break;

				case PLC_AI_Q_ID_KA:
					BuffFlo = DataIn->Val;
                    REG_CopyRegByPos((REG_AI_KA__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffFlo);
					break;

				case PLC_AI_Q_ID_KB:
					BuffFlo = DataIn->Val;
                    REG_CopyRegByPos((REG_AI_KB__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffFlo);
					break;

				case PLC_AI_Q_ID_STATUS:
                    BuffBy = (uint8_t)DataIn->Val;
                    REG_CopyRegByPos((REG_AI_STATUS__POS+(DataIn->Ch)), REG_COPY_VAR_TO_MB__NO_MON, &BuffBy);
					break;
            }
#ifdef DEBUG_LOG_AI_DATA_Q
#ifdef DEBUG_LOG_AI_DATA_Q_VAL
            DebugLog("AI[%d].ID=%d .Val=%f\n\n", DataIn->Ch, DataIn->ID, DataIn->Val);
#else
            if(DataIn->ID != PLC_AI_Q_ID_VAL)
            {
            	DebugLog("AI[%d].ID=%d .Val=%f\n\n", DataIn->Ch, DataIn->ID, DataIn->Val);
            }
#endif //DEBUG_LOG_AI_DATA_Q_VAL
#endif //DEBUG_LOG_AI_DATA_Q
        }
    }
}

/** @brief  Send data into RTOS_AI_Q
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_AI_Q_Send(const REG_t *DataIn)
{
#ifdef DEBUG_LOG_AI_Q
	DebugLog("RTOS_AI_Q_Send\n");
#endif // DEBUG_LOG_AI_Q

	PlcAI_Q_t QueueData;
	ANY32_uwt BuffAny32;
	uint8_t   BuffBy;

	if(DataIn)
	{
		Type_InitWords(BuffAny32.words, TYPE_FLOAT_WSZ, 0);
		QueueData.ID = PLC_AI_Q_ID_NONE;

        switch(DataIn->GID)
        {
        	case REG_AI_MODE__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_AI_Q_ID_MODE;
            		QueueData.Val = (float)BuffAny32.data_byte;
        		}
				break;

        	case REG_AI_KA__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_AI_Q_ID_KA;
            		QueueData.Val = BuffAny32.data_float;
        		}
				break;

        	case REG_AI_KB__GID:
        		if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        		{
            		QueueData.Ch  = DataIn->iGroup;
            		QueueData.ID  = PLC_AI_Q_ID_KB;
            		QueueData.Val = BuffAny32.data_float;
        		}
				break;
        }

		if(QueueData.ID != PLC_AI_Q_ID_NONE)
		{
#ifdef DEBUG_LOG_AI_Q
            DebugLog("AI[%d].ID=%d .Val=%f\n\n", QueueData.Ch, QueueData.ID, QueueData.Val);
#endif //DEBUG_LOG_AI_Q

			//@TODO Write Retain-data into FLASH/EEPROM
			//      if DataIn->Retain != REG_RETAIN_NONE
			//      ...

			//Send data into RTOS_AI_Q (not-blocking)
			xQueueSendToBack(RTOS_AI_Q, &QueueData, 0);
		}
	}
}

#endif //RTE_MOD_AI


#ifdef RTE_MOD_SYS_REG

/** @brief  Set System Registers
 *  @param  DataIn - pointer to data.
 *  @return None.
 */
static void RTOS_SYS_REG_Set(const REG_t *DataIn)
{
#ifdef DEBUG_LOG_SYS_REG
	DebugLog("RTOS_SYS_REG_Set\n");
#endif // DEBUG_LOG_SYS_REG

	ANY32_uwt BuffAny32;
	uint8_t BuffBy;

	if(DataIn)
	{
		Type_InitWords(BuffAny32.words, TYPE_FLOAT_WSZ, 0);

        switch(DataIn->GID)
        {
        	case REG_SYS_CMD__GID:
        		if(DataIn->iReg == REG_SYS_CMD__POS_LED_USER)
        		{
        			if(REG_CopyValueFromMb(DataIn->Type, &BuffBy, BuffAny32.words, DataIn->MbTable, DataIn->pMbVar))
        			{
        				RTOS_LED_Q_SendMode(PLC_LED_USER, BuffAny32.data_byte);
        				REG_SYS_STAT1_Set(PLC_SYS_STAT1_LED_USER, BuffAny32.data_byte);
        			}
        		}
				break;
        }
	}
}

#endif //RTE_MOD_SYS_REG


#ifdef RTE_MOD_REG_MON

/** @brief  Managing Data from REG API (by value change-trigger)
 *  @param  IDxIn - register IDx (position in REGS).
 *  @return None
 */
static void RTOS_REG_MON_Set(uint16_t IDxIn)
{
#ifdef DEBUG_LOG_REG_MON
	DebugLog("RTOS_DATA_REG_MON_Set\n");
#endif // DEBUG_LOG_REG_MON

    REG_t *Reg = REG_GetByIDx(IDxIn);

    if(Reg)
    {
#ifdef DEBUG_LOG_REG_MON
    	DebugLog("REG[%d].iReg=%d .GroupID=%d .GID=%d\n\n", IDxIn, Reg->iReg, Reg->GroupID, Reg->GID);
#endif // DEBUG_LOG_REG_MON

        switch(Reg->GroupID)
        {
#ifdef RTE_MOD_DI
        	case REG_DI__GROUP:
        		RTOS_DI_Q_Send(Reg);
        		break;
#endif //RTE_MOD_DI

#ifdef RTE_MOD_DO
        	case REG_DO__GROUP:
        		RTOS_DO_Q_Send(Reg);
        		break;
#endif //RTE_MOD_DO

#ifdef RTE_MOD_AI
        	case REG_AI__GROUP:
        		RTOS_AI_Q_Send(Reg);
        		break;
#endif //RTE_MOD_AI

#ifdef RTE_MOD_SYS_REG
        	case REG_SYS__GROUP:
        		RTOS_SYS_REG_Set(Reg);
        		break;
#endif //RTE_MOD_SYS_REG

            default:
                (void)IDxIn;
        }
    }
}

#endif // RTE_MOD_REG_MON


/** @brief  Task DATA_T
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_DATA_Task(void *ParamsIn)
{
    //VARIABLES
#ifdef RTE_MOD_DI
    PlcDI_Q_t  QueueData_DI;
    BaseType_t QueueStatus_DI;
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
    PlcDO_Q_t  QueueData_DO;
    BaseType_t QueueStatus_DO;
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AI
    PlcAI_Q_t  QueueData_AI;
    BaseType_t QueueStatus_AI;
#endif // RTE_MOD_AI

#ifdef RTE_MOD_REG_MON
    uint16_t   QueueData_RegMonitor;
    BaseType_t QueueStatus_RegMonitor;
#endif // RTE_MOD_REG_MON

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
#ifdef RTE_MOD_DI
        //Data from DI_T
    	// read Queue (not-blocking)
    	QueueStatus_DI = xQueueReceive(RTOS_DI_DATA_Q, &QueueData_DI, 0);
        if(QueueStatus_DI == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
            //unpack DI-channel data
            RTOS_DI_DATA_Q_ToReg(&QueueData_DI);
            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
        //Data from DO_T
    	// read Queue (not-blocking)
    	QueueStatus_DO = xQueueReceive(RTOS_DO_DATA_Q, &QueueData_DO, 0);
        if(QueueStatus_DO == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
            //unpack DO-channel data
            RTOS_DO_DATA_Q_ToReg(&QueueData_DO);
            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AI
    	//Data from AI_T
        // read Queue (not-blocking)
        QueueStatus_AI = xQueueReceive(RTOS_AI_DATA_Q, &QueueData_AI, 0);
        if(QueueStatus_AI == pdPASS)
        {
            //LOCK
        	xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
            //unpack AI-channel data
        	RTOS_AI_DATA_Q_ToReg(&QueueData_AI);
            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
#endif // RTE_MOD_AI

#ifdef RTE_MOD_REG_MON
    	//Data from REG API (by value change-trigger)
        // read Queue (not-blocking)
        QueueStatus_RegMonitor = xQueueReceive(RTOS_DATA_REG_MONITOR_Q, &QueueData_RegMonitor, 0);
        if(QueueStatus_RegMonitor == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MBTABLES_MTX, portMAX_DELAY);
            //unpack updated register
            RTOS_REG_MON_Set(QueueData_RegMonitor);
            xSemaphoreGive(RTOS_MBTABLES_MTX);
            //UNLOCK
        }
#endif // RTE_MOD_REG_MON

        //fast switch to other task
        taskYIELD();
    }
}
