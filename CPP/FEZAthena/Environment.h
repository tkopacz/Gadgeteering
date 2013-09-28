#define GADGETEERING_MAINBOARD_UNO 1
#define GADGETEERING_MAINBOARD_MEGA 2
#define GADGETEERING_MAINBOARD_MEGA_ADK 3
#define GADGETEERING_MAINBOARD_DUE 4
#define GADGETEERING_MAINBOARD_MEDUSA 5

#ifndef GADGETEERING_MAINBOARD
	#define GADGETEERING_MAINBOARD GADGETEERING_MAINBOARD_DUE
#endif

#if (GADGETEERING_MAINBOARD == GADGETEERING_MAINBOARD_DUE)
	#define SYSTEM_CLOCK 84000U /*KHz*/
	#define GADGETEERING_SYSTEM_CLOCK 84000U /*KHz*/
	#define GADGETEERING_EXTENDED_SPI 1
	#define GADGETEERING_HARDWARE_SPI 1
#elif (GADGETEERING_MAINBOARD == GADGETEERING_MAINBOARD_UNO)
	#define SYSTEM_CLOCK 16000U /*KHz*/
	#define GADGETEERING_SYSTEM_CLOCK 16000U /*KHz*/
#elif (GADGETEERING_MAINBOARD == GADGETEERING_MAINBOARD_MEGA)
	#define SYSTEM_CLOCK 16000U /*KHz*/
	#define GADGETEERING_SYSTEM_CLOCK 16000U /*KHz*/
#elif (GADGETEERING_MAINBOARD == GADGETEERING_MAINBOARD_MEDUSA)
	#define SYSTEM_CLOCK 12000U /*KHz*/
	#define GADGETEERING_SYSTEM_CLOCK 12000U /*KHz*/
#endif