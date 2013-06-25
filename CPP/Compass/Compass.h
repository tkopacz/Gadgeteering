#ifndef _COMPASS_H_
#define _COMPASS_H_

#include "../Gadgeteering/Mainboard.hpp"
#include "../Gadgeteering/Module.hpp"
#include "../Gadgeteering/Socket.hpp"
#include "../Gadgeteering/Types.hpp"
#include "../Gadgeteering/I2CDevice.hpp"
#include "../Gadgeteering/System.hpp"

#include <string.h>

namespace GHI
{
	namespace Modules
	{
		class Compass : protected Module
		{
			private:
				Interfaces::I2CDevice *i2c;

				unsigned char *_readBuffer8;
				unsigned char *_writeBuffer8;
				unsigned char *_writeBuffer16;
				unsigned char *readBuffer48;

				const double sq2p1 = 2.414213562373095048802e0F;
				const double sq2m1 = .414213562373095048802e0F;
				const double pio4 = .785398163397448309615e0F;
				const double pio2 = 1.570796326794896619231e0F;
				const double atan_p4 = .161536412982230228262e2F;
				const double atan_p3 = .26842548195503973794141e3F;
				const double atan_p2 = .11530293515404850115428136e4F;
				const double atan_p1 = .178040631643319697105464587e4F;
				const double atan_p0 = .89678597403663861959987488e3F;
				const double atan_q4 = .5895697050844462222791e2F;
				const double atan_q3 = .536265374031215315104235e3F;
				const double atan_q2 = .16667838148816337184521798e4F;
				const double atan_q1 = .207933497444540981287275926e4F;
				const double atan_q0 = .89678597403663861962481162e3F;

				class Registers
				{
					private:
						Registers();

					public:
						// From HMC5883.pdf Datasheet, pg. 12.              
						//                          R/W    Bit 7    Bit 6    Bit 5    Bit 4    Bit 3    Bit 2    Bit 1    Bit 0   
						// ------------------------------------------------------------------------------------------------------
						static const unsigned char CRA = 0x00;             //  R/W    
						static const unsigned char CRB = 0x01;             //  R/W 
						static const unsigned char MR = 0x02;             //  R/W
						static const unsigned char DXRA = 0x03;            //  R
						static const unsigned char DXRB = 0x04;            //  R
						static const unsigned char DZRA = 0x05;            //  R
						static const unsigned char DZRB = 0x06;            //  R
						static const unsigned char DYRA = 0x07;            //  R
						static const unsigned char DYRB = 0x08;            //  R
						static const unsigned char SR = 0x09;             //  R
						static const unsigned char IRA = 0x0A;             //  R
						static const unsigned char IRB = 0x0B;             //  R
						static const unsigned char IRC = 0x0C;             //  R
				};

				class Gain
				{
					private:
						Gain();

					public:
						static const unsigned char Gain1 = 0x00;
						static const unsigned char Gain2 = 0x20;
						static const unsigned char Gain3 = 0x40;
						static const unsigned char Gain4 = 0x60;
						static const unsigned char Gain5 = 0x80;
						static const unsigned char Gain6 = 0xA0;
						static const unsigned char Gain7 = 0xC0;
						static const unsigned char Gain8 = 0xE0;
				};

				class Mode
				{
					private:
						Mode();

					public:
						static const unsigned char Continous = 0x00;
						static const unsigned char SingleMode = 0x01;
						static const unsigned char IdleMode = 0x02;
						static const unsigned char SleepMode = 0x03;
				};

			public:
				Compass(int socket);

				class SensorData
				{        
					public:
						int X;
						int Y;
						int Z;
						double Angle;

						SensorData(double angle, int x, int y, int z);
				};

				SensorData RequestMeasurement();
				void SetGain(unsigned char gain);

				double Atan2(double y, double x);
				double Atans(double x);
				double Atanx(double x);
		};
	}
}

#endif