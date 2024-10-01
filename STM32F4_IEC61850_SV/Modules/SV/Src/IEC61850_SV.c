/*
 * IEC61850_SV.c
 *
 *  Created on: Oct 1, 2024
 *      Author: Professional
 */

#include "IEC61850_SV.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "semphr.h"

// Timer for signal emulation
extern TIM_HandleTypeDef htim2;

// Semaphore to emulate 50 Hz signal captured with 12800 Hz sample rate (256 samples per period)
osSemaphoreId_t signalSemHandle;

// Simulation of a 50 Hz sine wave captured with 12800 Hz sample rate
float VoltageSamples[POINTS_PER_PERIOD] = { 0, 0.0245288, 0.0490428, 0.0735273, 0.0979676, 0.122349, 0.146657, 0.170876, 0.194993, 0.218992, 0.242859,
		0.266581, 0.290142, 0.313528, 0.336726, 0.359721, 0.382499, 0.405048, 0.427353, 0.4494, 0.471177,
		0.492671, 0.513868, 0.534756, 0.555322, 0.575554, 0.595439, 0.614967, 0.634124, 0.6529, 0.671282,
		0.689261, 0.706825, 0.723964, 0.740667, 0.756924, 0.772726, 0.788063, 0.802926, 0.817305, 0.831193,
		0.844581, 0.85746, 0.869823, 0.881663, 0.892972, 0.903744, 0.913973, 0.923651, 0.932773, 0.941334,
		0.949329, 0.956752, 0.9636, 0.969868, 0.975552, 0.980649, 0.985156, 0.98907, 0.992389, 0.995111,
		0.997234, 0.998757, 0.999679, 1, 0.999718, 0.998835, 0.997351, 0.995267, 0.992584, 0.989304,
		0.985428, 0.98096, 0.975901, 0.970255, 0.964025, 0.957214, 0.949828, 0.941871, 0.933346, 0.92426,
		0.914618, 0.904425, 0.893688, 0.882413, 0.870608, 0.858278, 0.845432, 0.832077, 0.818222, 0.803874,
		0.789043, 0.773736, 0.757964, 0.741736, 0.725062, 0.707951, 0.690414, 0.672462, 0.654105, 0.635355,
		0.616222, 0.596718, 0.576856, 0.556646, 0.536101, 0.515234, 0.494056, 0.472581, 0.450822, 0.428792,
		0.406504, 0.383971, 0.361206, 0.338225, 0.31504, 0.291666, 0.268116, 0.244404, 0.220546, 0.196555,
		0.172445, 0.148232, 0.123929, 0.0995525, 0.0751156, 0.0506335, 0.0261209, 0.00159265, -0.0229366, -0.047452,
		-0.0719389, -0.0963825, -0.120768, -0.145081, -0.169307, -0.19343, -0.217438, -0.241314, -0.265045, -0.288617,
		-0.312015, -0.335226, -0.358234, -0.381027, -0.403591, -0.425912, -0.447977, -0.469772, -0.491284, -0.512501,
		-0.533409, -0.553997, -0.574251, -0.594159, -0.61371, -0.632892, -0.651692, -0.670101, -0.688106, -0.705698,
		-0.722864, -0.739596, -0.755883, -0.771714, -0.787082, -0.801975, -0.816387, -0.830306, -0.843727, -0.856639,
		-0.869036, -0.88091, -0.892254, -0.903062, -0.913325, -0.923039, -0.932198, -0.940796, -0.948827, -0.956288,
		-0.963173, -0.969479, -0.975201, -0.980336, -0.984882, -0.988834, -0.992192, -0.994953, -0.997115, -0.998677,
		-0.999638, -0.999997, -0.999755, -0.998911, -0.997466, -0.995421, -0.992777, -0.989535, -0.985698, -0.981268,
		-0.976247, -0.970639, -0.964447, -0.957674, -0.950325, -0.942405, -0.933917, -0.924867, -0.91526, -0.905103,
		-0.894402, -0.883162, -0.87139, -0.859095, -0.846282, -0.83296, -0.819137, -0.80482, -0.79002, -0.774744,
		-0.759002, -0.742803, -0.726158, -0.709075, -0.691565, -0.67364, -0.655309, -0.636584, -0.617475, -0.597995,
		-0.578156, -0.557968, -0.537445, -0.516598, -0.49544, -0.473984, -0.452243, -0.43023, -0.407958, -0.385441,
		-0.362691, -0.339723, -0.316551, -0.293189, -0.26965, -0.245948, -0.222099, -0.198116, -0.174014, -0.149807,
		-0.12551, -0.101137, -0.0767036, -0.052224, -0.027713 };

// Three-phased voltage signal
float ThreePhasedVolt[3];

// Sample buffers
float VoltA[ASDU_NUM];
float VoltB[ASDU_NUM];
float VoltC[ASDU_NUM];

const osSemaphoreAttr_t signalSem_attr = {
  .name = "signalSemaphore"
};

// SV publisher object
SVPublisher svPublisher;

// SVIds
char svId[8][12] = {"svpub1_test\0", "svpub2_test\0", "svpub3_test\0", "svpub4_test\0",
					"svpub5_test\0", "svpub6_test\0", "svpub7_test\0", "svpub8_test\0"};

// SV frame assembling and publishing task
void IEC61850_SV_Task(void *argument) {

	// Create a signal semaphore
	signalSemHandle = osSemaphoreNew(1, 0, &signalSem_attr);

	// Ethernet interface name in LWIP for STM32
	char* interface = "st";

	// Destination MAC address
	uint8_t macAddr[6] = {0x01, 0x0C, 0xCD, 0x04, 0x00, 0x01};

	// SV frame parameters configuration
	CommParameters frameParam;
	frameParam.vlanId = CONFIG_SV_CUSTOM_VLAN_ID;
	frameParam.vlanPriority = CONFIG_SV_CUSTOM_PRIORITY;
	frameParam.appId = CONFIG_SV_CUSTOM_APPID;
	for (int i = 0; i < 6; i++)
	{
		frameParam.dstAddress[i] = macAddr[i];
	}

	// Create the SV Publisher object
	svPublisher = SVPublisher_create(&frameParam, interface);

	//SV frame ASDUs configuration
	if (svPublisher) {

		// ASDU info structure
		ASDU_Inf ASDUs[ASDU_NUM];

		// Samples (points) per second
		uint16_t smpCntMax = SIGNAL_FREQ * POINTS_PER_PERIOD;

		// Adding ASDUs to svpublisher
	  	for (uint8_t i = 0; i < ASDU_NUM; ++i) {
	  		ASDUs[i].asdu = SVPublisher_addASDU(svPublisher, svId[0], NULL, 1);
	  	}

	  	// Adding 4 currents with quality (Q) and 4 voltages with Q
	  	// To add more data, use corresponding functions (addFLOAT, addINT etc. from sv_publisher.h)
        for (uint8_t i = 0; i < ASDU_NUM; ++i) {

      	  ASDUs[i].CurrentA = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);		// Current
      	  ASDUs[i].CurrA_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);	// Quality
      	  ASDUs[i].CurrentB = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].CurrB_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
      	  ASDUs[i].CurrentC = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].CurrC_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
      	  ASDUs[i].CurrentN = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].CurrN_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
      	  ASDUs[i].VoltageA = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);		// Voltage
      	  ASDUs[i].VoltA_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);	// Quality
      	  ASDUs[i].VoltageB = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].VoltB_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
      	  ASDUs[i].VoltageC = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].VoltC_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
      	  ASDUs[i].VoltageN = SVPublisher_ASDU_addINT32(ASDUs[i].asdu);
      	  ASDUs[i].VoltN_Q = SVPublisher_ASDU_addQuality(ASDUs[i].asdu);
        }

        SVPublisher_setupComplete(svPublisher);

        // Sample (point) counter
        uint16_t smpCnt = 0;

        // Start timer to simulate signals
        HAL_TIM_Base_Start_IT(&htim2);

        // Set synchronization status (in a real application it should be changed every time synch status changes)
		for (uint8_t i = 0; i < ASDU_NUM; ++i) {
			SVPublisher_ASDU_setSmpSynch(ASDUs[i].asdu, SV_SMPSYNCH_GLOBAL);
		}

        // You can add any condition of SV publisher operation
        while (1) {

        	if(osSemaphoreAcquire(signalSemHandle , portMAX_DELAY) == osOK) {

				for (uint8_t ASDU_num = 0; ASDU_num < ASDU_NUM; ++ASDU_num) {

					// Setting currents values in the frame
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrentA, 0);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrA_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrentB, 0);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrB_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrentC, 0);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrC_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrentN, 0);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].CurrN_Q, QUALITY_VALIDITY_GOOD);

					// Setting voltages values in the frame
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltageA, 100 * VoltA[ASDU_num]);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltA_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltageB, 100 * VoltB[ASDU_num]);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltB_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltageC, 100 * VoltC[ASDU_num]);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltC_Q, QUALITY_VALIDITY_GOOD);
					SVPublisher_ASDU_setINT32(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltageN, 0);
					SVPublisher_ASDU_setQuality(ASDUs[ASDU_num].asdu, ASDUs[ASDU_num].VoltN_Q, QUALITY_VALIDITY_GOOD);

					// Update sample counter
					SVPublisher_ASDU_setSmpCnt(ASDUs[ASDU_num].asdu, smpCnt);
					smpCnt++;
					if (smpCnt >= smpCntMax) {
						smpCnt = 0;
					}

				}
				// Publish SV frame
				SVPublisher_publish(svPublisher);

        	}

        }

	}

}

void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  		// 3 phased signal
  		static uint16_t currSample[3] = {0, 85, 171};
  		// Sample number in buffer
  		static uint8_t sampleNum = 0;

  		// 3 phased voltage emulation
  		for (uint8_t i = 0; i < 3; i++) {
  			ThreePhasedVolt[i] =  230 * 1.41 * VoltageSamples[currSample[i]++];

  			if (currSample[i] > POINTS_PER_PERIOD - 1) {
  				currSample[i] = 0;
  			}
  		}

  		// Put voltage in a buffer
  		VoltA[sampleNum] = ThreePhasedVolt[0];
  		VoltB[sampleNum] = ThreePhasedVolt[1];
  		VoltC[sampleNum] = ThreePhasedVolt[2];

  		sampleNum++;

  		if (sampleNum > ASDU_NUM - 1) {

  			sampleNum = 0;
  			// Give semaphore to SV task
  			static BaseType_t xHigherPriorityTaskWoken;
  			xHigherPriorityTaskWoken = pdFALSE;

  			xSemaphoreGiveFromISR(signalSemHandle, &xHigherPriorityTaskWoken);
  			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

  		}

  /* USER CODE END TIM2_IRQn 1 */
}
