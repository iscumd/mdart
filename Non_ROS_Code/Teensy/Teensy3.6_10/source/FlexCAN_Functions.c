/*
 * FlexCAN_Functions.c
 *
 *  Created on: May 27, 2018
 *      Author: Gamer
 */

/*!
 * @brief FlexCAN Call Back function
 */
#include "board.h"
#include "fsl_flexcan.h"
#include "UART_Functions.h"

#define EXAMPLE_CAN CAN0
#define EXAMPLE_CAN_CLKSRC kCLOCK_BusClk
#define EXAMPLE_CAN_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define RX_MESSAGE_BUFFER_0 (0)
#define RX_MESSAGE_BUFFER_1 (1)
#define RX_MESSAGE_BUFFER_2 (2)
#define RX_MESSAGE_BUFFER_3 (3)

#define TX_MESSAGE_BUFFER_4 (4)
#define TX_MESSAGE_BUFFER_5 (5)
#define TX_MESSAGE_BUFFER_6 (6)
#define TX_MESSAGE_BUFFER_7 (7)
#define TX_MESSAGE_BUFFER_8 (8)
#define TX_MESSAGE_BUFFER_9 (9)
#define TX_MESSAGE_BUFFER_10 (10)
#define TX_MESSAGE_BUFFER_11 (11)

volatile bool txComplete = false;
volatile bool rx0Complete = false;
volatile bool rx1Complete = false;
volatile bool rx2Complete = false;
volatile bool rx3Complete = false;

uint8_t buff0FlexCANRx[8] = {0};
uint8_t buff1FlexCANRx[8] = {0};
uint8_t buff2FlexCANRx[8] = {0};
uint8_t buff3FlexCANRx[8] = {0};

flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txXfer, rxXfer0, rxXfer1, rxXfer2, rxXfer3;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
flexcan_fd_frame_t txFrame, rxFrame;
#else
flexcan_frame_t rxFrame0, rxFrame1, rxFrame2, rxFrame3;
#endif

void FlexCAN0_TX4(flexcan_frame_t *);
void FlexCAN0_TX5(flexcan_frame_t *);
void FlexCAN0_TX6(flexcan_frame_t *);
void FlexCAN0_TX7(flexcan_frame_t *);
void FlexCAN0_TX8(flexcan_frame_t *);

void FlexCAN0_TX(void);

static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
{
    switch (status)
    {
        /* Process FlexCAN Rx event. */
        case kStatus_FLEXCAN_RxIdle:
        {
            if (RX_MESSAGE_BUFFER_0 == result)
            {
            	buff0FlexCANRx[0] = rxFrame0.dataByte0;
            	buff0FlexCANRx[1] = rxFrame0.dataByte1;
            	buff0FlexCANRx[2] = rxFrame0.dataByte2;
            	buff0FlexCANRx[3] = rxFrame0.dataByte3;
            	buff0FlexCANRx[4] = rxFrame0.dataByte4;
            	buff0FlexCANRx[5] = rxFrame0.dataByte5;
            	buff0FlexCANRx[6] = rxFrame0.dataByte6;
            	buff0FlexCANRx[7] = rxFrame0.dataByte7;

				rx0Complete = true;

				FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer0);
            }
            else if (RX_MESSAGE_BUFFER_1 == result)
            {
            	buff1FlexCANRx[0] = rxFrame1.dataByte0;
            	buff1FlexCANRx[1] = rxFrame1.dataByte1;
            	buff1FlexCANRx[2] = rxFrame1.dataByte2;
            	buff1FlexCANRx[3] = rxFrame1.dataByte3;
            	buff1FlexCANRx[4] = rxFrame1.dataByte4;
            	buff1FlexCANRx[5] = rxFrame1.dataByte5;
            	buff1FlexCANRx[6] = rxFrame1.dataByte6;
            	buff1FlexCANRx[7] = rxFrame1.dataByte7;

				rx1Complete = true;

				FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer1);
            }
            else if (RX_MESSAGE_BUFFER_2 == result)
            {
            	buff2FlexCANRx[0] = rxFrame2.dataByte0;
            	buff2FlexCANRx[1] = rxFrame2.dataByte1;
            	buff2FlexCANRx[2] = rxFrame2.dataByte2;
            	buff2FlexCANRx[3] = rxFrame2.dataByte3;
            	buff2FlexCANRx[4] = rxFrame2.dataByte4;
            	buff2FlexCANRx[5] = rxFrame2.dataByte5;
            	buff2FlexCANRx[6] = rxFrame2.dataByte6;
            	buff2FlexCANRx[7] = rxFrame2.dataByte7;

				rx2Complete = true;

				FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer2);
            }
            else
            {
            	buff3FlexCANRx[0] = rxFrame3.dataByte0;
            	buff3FlexCANRx[1] = rxFrame3.dataByte1;
            	buff3FlexCANRx[2] = rxFrame3.dataByte2;
            	buff3FlexCANRx[3] = rxFrame3.dataByte3;
            	buff3FlexCANRx[4] = rxFrame3.dataByte4;
            	buff3FlexCANRx[5] = rxFrame3.dataByte5;
            	buff3FlexCANRx[6] = rxFrame3.dataByte6;
            	buff3FlexCANRx[7] = rxFrame3.dataByte7;

				rx3Complete = true;

				FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer3);
            }
        }
        break;

        /* Process FlexCAN Tx event. */
        case kStatus_FLEXCAN_TxIdle:
        {
            if (TX_MESSAGE_BUFFER_4 == result)
            {
                txComplete = true;
            }
        }
        break;

        case kStatus_FLEXCAN_TxBusy:
			break;

        case kStatus_FLEXCAN_TxSwitchToRx:
			break;

        case kStatus_FLEXCAN_RxBusy:
			break;

        case kStatus_FLEXCAN_RxOverflow:
			break;

        case kStatus_FLEXCAN_RxFifoBusy:
			break;

        case kStatus_FLEXCAN_RxFifoIdle:
			break;

        case kStatus_FLEXCAN_RxFifoOverflow:
			break;

        case kStatus_FLEXCAN_RxFifoWarning:
			break;

        case kStatus_FLEXCAN_ErrorStatus:
			break;

        case kStatus_FLEXCAN_UnHandled:
			break;

        default:
            break;
    }
}

void FlexCAN0_TX4(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_4;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_4, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX5(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_5;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_5, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX6(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_6;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_6, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX7(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_7;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_7, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX8(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_8;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_8, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX9(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_9;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_9, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX10(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_10;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_10, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN0_TX11(flexcan_frame_t *txFrame)
{
    /* Send data through Tx Message Buffer. */
    txXfer.mbIdx = TX_MESSAGE_BUFFER_11;

    /* Setup Tx Message Buffer. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
#else
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_11, true);
#endif

    /* Prepare Tx Frame for sending. */
    txFrame->format = kFLEXCAN_FrameFormatExtend;
    txFrame->type = kFLEXCAN_FrameTypeData;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
	txXfer.framefd = &txFrame;
	FLEXCAN_TransferFDSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#else
	txXfer.frame = txFrame;
	FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
#endif

}

void FlexCAN_Init()
{
	flexcan_config_t flexcanConfig;
    flexcan_rx_mb_config_t mbConfig;

    /* Init FlexCAN module. */
    /*
     * flexcanConfig.clkSrc = kFLEXCAN_ClkSrcOsc;
     * flexcanConfig.baudRate = 1000000U;
     * flexcanConfig.maxMbNum = 16;
     * flexcanConfig.enableLoopBack = false;
     * flexcanConfig.enableSelfWakeup = false;
     * flexcanConfig.enableIndividMask = false;
     * flexcanConfig.enableDoze = false;
     */
    FLEXCAN_GetDefaultConfig(&flexcanConfig);
#if (!defined(FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE)) || !FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE
    flexcanConfig.clkSrc = kFLEXCAN_ClkSrcPeri;
    flexcanConfig.baudRate = 500000U;
    flexcanConfig.enableLoopBack = false;

#endif /* FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE */

    FLEXCAN_Init(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ);
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    /* Enable CAN FD operation with flexible payload and data rate. */
    FLEXCAN_FDEnable(EXAMPLE_CAN, BYTES_IN_MB, false);
#endif

    /* Setup Rx Message Buffer. */
    mbConfig.format = kFLEXCAN_FrameFormatExtend;
    mbConfig.type = kFLEXCAN_FrameTypeData;
    mbConfig.id = FLEXCAN_ID_EXT(0x901);
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#else
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_0, &mbConfig, true);
#endif

    /* Setup Rx Message Buffer. */
    mbConfig.id = FLEXCAN_ID_EXT(0x902);
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#else
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_1, &mbConfig, true);
#endif

    /* Setup Rx Message Buffer. */
    mbConfig.id = FLEXCAN_ID_EXT(0x903);
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#else
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_2, &mbConfig, true);
#endif

    /* Setup Rx Message Buffer. */
    mbConfig.id = FLEXCAN_ID_EXT(0x904);
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    FLEXCAN_SetFDRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
#else
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_3, &mbConfig, true);
#endif

    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);

    /* Start receive data through Rx Message Buffer. */
    rxXfer0.mbIdx = RX_MESSAGE_BUFFER_0;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    rxXfer0.framefd = &rxFrame0;
    FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer0);
#else
    rxXfer0.frame = &rxFrame0;
    FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer0);
#endif

    /* Start receive data through Rx Message Buffer. */
    rxXfer1.mbIdx = RX_MESSAGE_BUFFER_1;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    rxXfer1.framefd = &rxFrame1;
    FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer1);
#else
    rxXfer1.frame = &rxFrame1;
    FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer1);
#endif

    /* Start receive data through Rx Message Buffer. */
    rxXfer2.mbIdx = RX_MESSAGE_BUFFER_2;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    rxXfer2.framefd = &rxFrame2;
    FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer2);
#else
    rxXfer2.frame = &rxFrame2;
    FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer2);
#endif

    /* Start receive data through Rx Message Buffer. */
    rxXfer3.mbIdx = RX_MESSAGE_BUFFER_3;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    rxXfer3.framefd = &rxFrame3;
    FLEXCAN_TransferFDReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer3);
#else
    rxXfer3.frame = &rxFrame3;
    FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer3);
#endif
}

