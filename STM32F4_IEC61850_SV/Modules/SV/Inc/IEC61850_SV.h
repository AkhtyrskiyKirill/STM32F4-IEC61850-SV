/*
 * IEC61850_SV.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Professional
 */

#ifndef SV_INC_IEC61850_SV_H_
#define SV_INC_IEC61850_SV_H_

#include "sv_publisher.h"

//SV frame parameters defines
#define CONFIG_SV_CUSTOM_PRIORITY 4
#define CONFIG_SV_CUSTOM_VLAN_ID 0
#define CONFIG_SV_CUSTOM_APPID 0x4000

// Synchronization status defines
#define SV_SMPSYNCH_GLOBAL 2
#define SV_SMPSYNCH_LOCAL 1
#define SV_SMPSYNCH_NONE 0

// ASDUs quantity in one SV frame
#define ASDU_NUM 8

// Points per signal period
#define POINTS_PER_PERIOD 256
// Captured signal frequency
#define SIGNAL_FREQ 50

// ASDU information structure
// Edit implementation if you need other data in ASDU
// According to IEC61850-9-2 Implementation guideline each ASDU
// Contains 4 currents with quality info (validity, test flag etc.) and 4 voltages with quality info
typedef struct asduInfStruct {
	  SVPublisher_ASDU asdu;
	  int CurrentA;
	  int CurrA_Q;
	  int CurrentB;
	  int CurrB_Q;
	  int CurrentC;
	  int CurrC_Q;
	  int CurrentN;
	  int CurrN_Q;
	  int VoltageA;
	  int VoltA_Q;
	  int VoltageB;
	  int VoltB_Q;
	  int VoltageC;
	  int VoltC_Q;
	  int VoltageN;
	  int VoltN_Q;
} ASDU_Inf;



// SV frame assembling and publishing task
void IEC61850_SV_Task(void *argument);

#endif /* SV_INC_IEC61850_SV_H_ */
