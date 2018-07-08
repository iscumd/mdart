/*
 * FlexCAN_Functions.h
 *
 *  Created on: May 27, 2018
 *      Author: Gamer
 */

#ifndef FLEXCAN_FUNCTIONS_H_
#define FLEXCAN_FUNCTIONS_H_

#include "board.h"
#include "fsl_flexcan.h"

extern bool rx0Complete;
extern bool rx1Complete;
extern bool rx2Complete;
extern bool rx3Complete;

extern uint8_t buff0FlexCANRx[];
extern uint8_t buff1FlexCANRx[];
extern uint8_t buff2FlexCANRx[];
extern uint8_t buff3FlexCANRx[];

extern void FlexCAN0_TX4(flexcan_frame_t *);
extern void FlexCAN0_TX5(flexcan_frame_t *);
extern void FlexCAN0_TX6(flexcan_frame_t *);
extern void FlexCAN0_TX7(flexcan_frame_t *);
extern void FlexCAN0_TX8(flexcan_frame_t *);
extern void FlexCAN0_TX9(flexcan_frame_t *);
extern void FlexCAN0_TX10(flexcan_frame_t *);
extern void FlexCAN0_TX11(flexcan_frame_t *);

#endif /* FLEXCAN_FUNCTIONS_H_ */
