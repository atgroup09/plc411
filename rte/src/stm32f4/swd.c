/* @page swd.c
 *       PLC411::RTE
 *       SWD/SWO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022, atgroup09@gmail.com
 */

#include "swd.h"


/** @brief  Write byte into SWD/SWO.
 *  @param  ByteIn - byte to write.
 *  @return Result:
 *  @arg    = BIT_FALSE - byte is not sent
 *  @arg    = BIT_TRUE  - byte is sent
 */
static uint8_t ITM_WriteByte(uint8_t ByteIn)
{
	//ITM.enabled && ITM.Port0.enabled
	if(((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) && ((ITM->TER & (1UL<<PLC_SWD_PORT)) != 0UL))
	{
		//wait until STIMx is ready...
		while(ITM->PORT[PLC_SWD_PORT].u32 == 0UL)
		{
			asm("NOP");
		}

		//send one byte
		ITM->PORT[PLC_SWD_PORT].u8 = ByteIn;

		return (BIT_TRUE);
	}

	return (BIT_FALSE);
}

/** @brief  Print byte.
 *  @param  ByteIn - byte.
 *  @return None.
 */
inline void PlcSwd_PrintByte(uint8_t ByteIn)
{
	ITM_WriteByte(ByteIn);
}

/** @brief  Print string.
 *  @param  StrIn - pointer to string.
 *  @param  StrLenIn - size of string.
 *  @return None.
 */
void PlcSwd_PrintStr(const char *StrIn, uint8_t StrLenIn)
{
	uint8_t i = 0;

	if(StrIn && StrLenIn > 0)
	{
		for(i=0; i<StrLenIn; i++)
		{
			//if(StrIn[i] == '\0') break;
			ITM_SendChar(StrIn[i]);
			//if(StrIn[i] == '\n') break;
		}
	}
}

/** @brief  Init.
 *  @param  None.
 *  @return None.
 */
void PlcSwd_Init(void)
{
	//Enable ITM
	ITM->TCR |= ITM_TCR_ITMENA_Msk;
	//Enable Port
	ITM->TER |= (1UL << PLC_SWD_PORT);
}
