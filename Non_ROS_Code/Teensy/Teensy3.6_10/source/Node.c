/*
 * The Clear BSD License
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "UART_Functions.h"
#include "FlexCAN_Functions.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void FlexCAN_Init(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW button is pressed */
volatile bool 	timerFlag = false;
static bool		CAN_stUpdt = false;

uint8_t 	CAN_stMotCMD = 0;

uint16_t 	CAN_degMot1Ang = 0;
uint16_t 	CAN_degMot2Ang = 0;
uint16_t 	CAN_degMot3Ang = 0;
uint16_t 	CAN_degMot4Ang = 0;

uint32_t 	CAN_valMot1Data = 0x1539;
uint32_t 	CAN_valMot2Data = 0x1539;
uint32_t 	CAN_valMot3Data = 0x1539;
uint32_t 	CAN_valMot4Data = 0x1539;

uint8_t txbuff[] = "Uart polling example\r\nBoard will send back received characters\r\n";
/*!
 * @brief Main function
 */
int main(void)
{
	char i = 0, j = 0;
	uint16_t	idCAN = 0;
	flexcan_frame_t txFrame;

	SysTick_Config(12000000);

	/* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    gpio_pin_config_t canvs_config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);

	/* Init output CAN Slew Rate. */
	GPIO_PinInit(BOARD_CAN_VS_GPIO, BOARD_CAN_VS_GPIO_PIN, &canvs_config);

	UART0_Init();

	UART0_Tx(txbuff,sizeof(txbuff));

    FlexCAN_Init();

    while(1)
    {
    	if(CAN_stUpdt)
    	{
    		switch(CAN_stMotCMD)
    		{
    			case 1:
    			{
    				idCAN = 0x000;
    			}
    			break;

    			case 2:
    			{
    				idCAN = 0x100;
    			}
    			break;

    			case 3:
    			{
    				idCAN = 0x300;
    			}
    			break;

    			default:
    			{
    				idCAN = 0x200;
    			}
   				break;
    		}
		    txFrame.id = FLEXCAN_ID_EXT(idCAN | 0x001);
		    txFrame.length = 4;
		    txFrame.dataWord0 = CAN_valMot1Data;

		    FlexCAN0_TX4(&txFrame);

		    txFrame.id = FLEXCAN_ID_EXT(idCAN | 0x002);
		    txFrame.length = 4;
		    txFrame.dataWord0 = CAN_valMot2Data;

		    FlexCAN0_TX5(&txFrame);

		    txFrame.id = FLEXCAN_ID_EXT(idCAN | 0x003);
		    txFrame.length = 4;
		    txFrame.dataWord0 = CAN_valMot3Data;

		    FlexCAN0_TX6(&txFrame);

		    txFrame.id = FLEXCAN_ID_EXT(idCAN | 0x004);
		    txFrame.length = 4;
		    txFrame.dataWord0 = CAN_valMot4Data;

		    FlexCAN0_TX7(&txFrame);

		    /* Prepare Tx Frame for sending. */
		    txFrame.id = FLEXCAN_ID_EXT(0xC01);
		    txFrame.length = 2;
			txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(CAN_degMot1Ang >> 8) | CAN_WORD0_DATA_BYTE_1(CAN_degMot1Ang);

		    FlexCAN0_TX8(&txFrame);

		    /* Prepare Tx Frame for sending. */
		    txFrame.id = FLEXCAN_ID_EXT(0xC02);
		    txFrame.length = 2;
			txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(CAN_degMot2Ang >> 8) | CAN_WORD0_DATA_BYTE_1(CAN_degMot2Ang);

		    FlexCAN0_TX9(&txFrame);

		    /* Prepare Tx Frame for sending. */
		    txFrame.id = FLEXCAN_ID_EXT(0xC03);
		    txFrame.length = 2;
			txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(CAN_degMot3Ang >> 8) | CAN_WORD0_DATA_BYTE_1(CAN_degMot3Ang);

		    FlexCAN0_TX10(&txFrame);

		    /* Prepare Tx Frame for sending. */
		    txFrame.id = FLEXCAN_ID_EXT(0xC04);
		    txFrame.length = 2;
			txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(CAN_degMot4Ang >> 8) | CAN_WORD0_DATA_BYTE_1(CAN_degMot4Ang);

		    FlexCAN0_TX11(&txFrame);

		    CAN_stUpdt = false;
    	}


    	if (timerFlag)
    	{
    		i++;

    		if(i>= 10)
    		{
    			CAN_stUpdt = true;
//    			CAN_stMotCMD = 1;
//
//    			if(CAN_degMot1Ang < 1000)
//    			{
//    				CAN_degMot1Ang+=10;
//    			}
//    			else
//    			{
//    				CAN_degMot1Ang = 0;
//    			}

    			GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
    			i =0;
    			j++;
    		}
			timerFlag = 0;
    	}

		if(rx0Complete)
		{
			memcpy(txbuff,buff0FlexCANRx,sizeof(txbuff));
    		UART0_Tx(txbuff, 8);

    	    rx0Complete = false;
		}

		if(rx1Complete)
		{
			memcpy(txbuff,buff1FlexCANRx,sizeof(txbuff));
    		UART0_Tx(txbuff, 8);

    	    rx1Complete = false;
		}

		if(rx2Complete)
		{
			memcpy(txbuff,buff2FlexCANRx,sizeof(txbuff));
    		UART0_Tx(txbuff, 8);

    	    rx2Complete = false;
		}

		if(rx3Complete)
		{
			memcpy(txbuff,buff3FlexCANRx,sizeof(txbuff));
    		UART0_Tx(txbuff, 8);

    	    rx3Complete = false;
		}

		if(UART0_stRxCmplt)
		{
			if(UART0_valRxData[1] == 26)
			{
				switch(UART0_valRxData[2])
				{
					case 0:
					{
						CAN_stMotCMD = 1;
					}
					break;

					case 1:
					{
						CAN_stMotCMD = 2;
					}
					break;

					case 2:
					{
						CAN_stMotCMD = 3;
					}
					break;

					case 3:
					{
						CAN_stMotCMD = 4;
					}
					break;

					default:
					{
						CAN_stMotCMD = 0;
					}
				}

				CAN_valMot1Data = ((uint32_t) UART0_valRxData[3]) << 24 | ((uint32_t) UART0_valRxData[4]) << 16 |
									((uint32_t) UART0_valRxData[5]) << 8 |  ((uint32_t) UART0_valRxData[6]);
				CAN_valMot2Data = ((uint32_t) UART0_valRxData[7]) << 24 | ((uint32_t) UART0_valRxData[8]) << 16 |
									((uint32_t) UART0_valRxData[9]) << 8 |  ((uint32_t) UART0_valRxData[10]);
				CAN_valMot3Data = ((uint32_t) UART0_valRxData[11]) << 24 | ((uint32_t) UART0_valRxData[12]) << 16 |
									((uint32_t) UART0_valRxData[13]) << 8 |  ((uint32_t) UART0_valRxData[14]);
				CAN_valMot4Data = ((uint32_t) UART0_valRxData[15]) << 24 | ((uint32_t) UART0_valRxData[16]) << 16 |
									((uint32_t) UART0_valRxData[17]) << 8 |  ((uint32_t) UART0_valRxData[18]);

				CAN_degMot1Ang = ((uint32_t) UART0_valRxData[19]) << 8 | ((uint32_t) UART0_valRxData[20]);
				CAN_degMot2Ang=  ((uint32_t) UART0_valRxData[21]) << 8 | ((uint32_t) UART0_valRxData[22]);
				CAN_degMot3Ang = ((uint32_t) UART0_valRxData[23]) << 8 | ((uint32_t) UART0_valRxData[24]);
				CAN_degMot4Ang = ((uint32_t) UART0_valRxData[25]) << 8 | ((uint32_t) UART0_valRxData[26]);

				CAN_stUpdt = true;

				memcpy(txbuff,'\0',sizeof(txbuff));
				strcpy((char *)txbuff,"Received command\r\n");
				UART0_Tx(txbuff, strlen(txbuff));

			}
		    UART0_stRxCmplt = false;
		}
    }
}

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service function of systick.
 *
 * This function raises a flag
 */
void BOARD_SYSTICK_IRQ_HANDLER(void)
{
	timerFlag = true;
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
