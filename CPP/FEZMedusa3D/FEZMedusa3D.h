/*
Copyright 2013 GHI Electronics LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef _FEZMedusa3D_H_
#define _FEZMedusa3D_H_

#include "../Gadgeteering/Mainboard.hpp"
#include "../Gadgeteering/Socket.hpp"
#include "../Gadgeteering/SerialDevice.hpp"
#include "../Gadgeteering/SPIDevice.hpp"
#include "../Gadgeteering/I2CBus.hpp"
#include "../IO60P16/IO60P16.h"
#include "Environment.h"

class SPIClass;

namespace GHI {
	namespace Mainboards {
		class FEZMedusa3D : public GHI::Mainboard {

			public:
			class SPIBus : public GHI::Interfaces::SPIBus
			{
				SPIClass* spi;
				void setup(GHI::Interfaces::SPIConfiguration* configuration);
				void selectChip(GHI::Interfaces::SPIConfiguration* configuration);
				void deselectChip(GHI::Interfaces::SPIConfiguration* configuration);

				public:
					SPIBus(CPUPin mosi, CPUPin miso, CPUPin sck);
					virtual ~SPIBus();
					
					virtual void writeRead(const unsigned char* sendBuffer, unsigned char* receiveBuffer, unsigned int count, Interfaces::SPIConfiguration* configuration, bool deselectAfter = false);
			};

			class SerialDevice : public GHI::Interfaces::SerialDevice {
				public:
					SerialDevice(CPUPin tx, CPUPin rx, unsigned int baudRate, unsigned char parity, unsigned char stopBits, unsigned char dataBits);
					virtual ~SerialDevice();
		
					virtual void open();
					virtual void close();
					virtual void write(const unsigned char* buffer, unsigned int count);
					virtual unsigned int read(unsigned char* buffer, unsigned int count);
					virtual unsigned int available();
			};
	
			class I2CBus : public GHI::Interfaces::I2CBus
			{

#ifndef GADGETEERING_HARDWARE_I2C
					bool start;

					void clearSCL();
					bool readSCL();
					void clearSDA();
					bool readSDA();

					bool writeBit(bool bit);
					bool readBit();

					bool sendStartCondition();
					bool sendStopCondition();                       

					bool transmit(bool sendStart, bool sendStop, unsigned char data);
					unsigned char receive(bool sendAcknowledgeBit, bool sendStopCondition);
#endif

					public:
							I2CBus(CPUPin sda, CPUPin scl);
							virtual ~I2CBus();
							
							virtual unsigned int write(const unsigned char* buffer, unsigned int count, unsigned char address, bool sendStop);
							virtual unsigned int read(unsigned char* buffer, unsigned int count, unsigned char address, bool sendStop);
							virtual bool writeRead(const unsigned char* writeBuffer, unsigned int writeLength, unsigned char* readBuffer, unsigned int readLength, unsigned int* numWritten, unsigned int* numRead, unsigned char address);
			};
				FEZMedusa3D();
				virtual ~FEZMedusa3D();
				
				virtual void panic(unsigned char error, unsigned char specificError = 0);
				virtual void print(const char* toPrint);
				virtual void print(int toPrint);
				virtual void print(double toPrint);
				
				void setPWM(CPUPin pinNumber, double frequency, double dutyCycle, double duration); //Works only on socket 2.
				virtual void setPWM(CPUPin pin, double dutyCycle, double frequency);
				virtual bool readDigital(CPUPin pin);
				virtual void writeDigital(CPUPin pin, bool value);
				virtual double readAnalog(CPUPin pin);
				virtual double readAnalogProportion(CPUPin pin);
				virtual void writeAnalog(CPUPin pin, double voltage);
				virtual void writeAnalogProportion(CPUPin pin, double proportion);
				virtual void setIOMode(CPUPin pin, IOState state, ResistorMode resistorMode = ResistorModes::FLOATING);
		
				virtual Interfaces::SerialDevice* getSerialDevice(unsigned int baudRate, unsigned char parity, unsigned char stopBits, unsigned char dataBits, CPUPin txPin, CPUPin rxPin);
				virtual Interfaces::SPIBus* getSPIBus(CPUPin mosiPin, CPUPin misoPin, CPUPin sckPin);
				virtual Interfaces::I2CBus* getI2CBus(CPUPin sdaPin, CPUPin sclPin, bool isHardware = false);
		};
	}
}


#endif
