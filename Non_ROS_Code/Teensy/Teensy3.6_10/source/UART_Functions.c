/*
 * UART_Functions.c
 *
 *  Created on: May 27, 2018
 *      Author: Gamer
 */

#include "board.h"
#include "fsl_uart.h"

#define DEMO_UART UART0
#define DEMO_UART_CLKSRC SYS_CLK
#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(SYS_CLK)

volatile bool rxBufferEmpty = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;

bool 		UART0_stRxCmplt = 0;
uint8_t 	UART0_valRxData[40] = {0};

static uint8_t 	UART0_ctRxPtr;
static uint8_t 	UART0_ctElapsedTick = 0;
static uint8_t 	UART0_valChkSum = 0;

uart_handle_t g_uartHandle;
uart_transfer_t xfer;
uart_transfer_t sendXfer;
uart_transfer_t receiveXfer;

uint8_t rxbuff = 0;

void UART0_Init(void);
void UART0_Tx(uint8_t * , uint8_t  );
/*******************************************************************************
 * Code
 ******************************************************************************/

/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing = false;
    }

    if (kStatus_UART_RxIdle == status)
    {
    	UART0_ctElapsedTick = 0;

    	if((UART0_stRxCmplt == 0)&&(UART0_ctRxPtr < 35))
    	{
    		UART0_valRxData[UART0_ctRxPtr] = rxbuff;

    		if(UART0_ctRxPtr == 0)
    		{
    			UART0_stRxCmplt 	= 0;
    			UART0_valChkSum 	= 0;

    			if(UART0_valRxData[UART0_ctRxPtr] == 0xA0)
    			{
    				UART0_valChkSum ^= UART0_valRxData[UART0_ctRxPtr];
    				UART0_ctRxPtr++;
    			}
    			else
    			{
    				UART0_ctRxPtr 		= 0;
    			}
    		}
    		else if(UART0_ctRxPtr == 1)
    		{
    			if(UART0_valRxData[UART0_ctRxPtr] >= 0x02)
    			{
					UART0_valChkSum ^= UART0_valRxData[UART0_ctRxPtr];
					UART0_ctRxPtr++;
    			}
    			else
    			{
    				UART0_ctRxPtr 		= 0;
    				UART0_valChkSum 	= 0;
    			}
    		}
    		else if((UART0_ctRxPtr >= 2) && (UART0_ctRxPtr < (UART0_valRxData[1]+ 1)))
    		{
    			UART0_valChkSum ^= UART0_valRxData[UART0_ctRxPtr];
    			UART0_ctRxPtr++;
    		}
    		else
    		{
    			if((unsigned char)UART0_valChkSum == UART0_valRxData[UART0_ctRxPtr])
    			{
    				UART0_stRxCmplt 	= true;
    			}
    			UART0_ctRxPtr 		= 0;
    		}
    	}
        UART_TransferReceiveNonBlocking(DEMO_UART, &g_uartHandle, &receiveXfer, NULL);
    }
}

void UART0_Tx(uint8_t * txbuff, uint8_t len )
{
	xfer.data = txbuff;
	xfer.dataSize = len;
	UART_TransferSendNonBlocking(DEMO_UART, &g_uartHandle, &xfer);
}

void UART0_Init()
{
	uart_config_t config;
	/*
	 * config.baudRate_Bps = 115200U;
	 * config.parityMode = kUART_ParityDisabled;
	 * config.stopBitCount = kUART_OneStopBit;
	 * config.txFifoWatermark = 0;
	 * config.rxFifoWatermark = 1;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	UART_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);
	UART_TransferCreateHandle(DEMO_UART, &g_uartHandle, UART_UserCallback, NULL);

    receiveXfer.data = &rxbuff;
    receiveXfer.dataSize = 1;
    UART_TransferReceiveNonBlocking(DEMO_UART, &g_uartHandle, &receiveXfer, NULL);
}
