#ifndef _TOUCHC8_H_
#define _TOUCHC8_H_

#include "../Gadgeteering/Gadgeteering.h"

namespace GHI {
	namespace Modules {
		class TouchC8 : public Module {
			static const unsigned char I2C_ADDRESS = 0x2B;
			static const unsigned char IRQ_SRC = 0x0;
			static const unsigned char CAP_STAT_MSB = 0x1;
			static const unsigned char CAP_STAT_LSB = 0x2;
			static const unsigned char WHL_POS_MSB = 0x3;
			static const unsigned char WHL_POS_LSB = 0x4;
			static const unsigned char WHEELS = 8;

			Interfaces::DigitalOutput* reset;
			Interfaces::I2CDevice* device;
			
			void Reset();
			void ConfigureSPM();
			void WriteSPM(unsigned char address, const unsigned char data[9]);

			public:
				typedef unsigned char Button;
				class Buttons
				{
					public:
						static const Button A = 0x2;
						static const Button B = 0x4;
						static const Button C = 0x8;
				};

				typedef unsigned char Direction;
				class Directions
				{
					public:
						static const Direction Clockwise = 0;
						static const Direction CounterClockwise = 1;
				};

				TouchC8(unsigned char socketNumber);
				~TouchC8();
				
				bool IsButtonPressed(Button button);
				bool IsWheelPressed();
				bool IsProximityDetected();
				double GetWheelPosition();
				Direction GetWheelDirection();
		};
	}
}

#endif
