/*
Copyright 2013 Gadgeteering Electronics LLC

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

#include "Types.h"

using namespace Gadgeteering;

SPIConfiguration::SPIConfiguration()
{

}


SPIConfiguration::SPIConfiguration(bool chipSelectActiveState, unsigned int chipSelectSetupTime, unsigned int chipSelectHoldTime, bool clockIdleState, bool clockEdge, unsigned int clockRate)
{
	this->chipSelectActiveState = chipSelectActiveState;
	this->chipSelectSetupTime = chipSelectSetupTime;
	this->chipSelectHoldTime = chipSelectHoldTime;
	this->clockIdleState = clockIdleState;
	this->clockEdge = clockEdge;
	this->clockRate = clockRate;
}

serial_configuration::serial_configuration()
{

}

serial_configuration::serial_configuration(unsigned int baud_rate, serial_parity parity, serial_stop_bit stop_bits, unsigned char data_bits)
{
	this->baud_rate = baud_rate;
	this->parity = parity;
	this->stop_bits = stop_bits;
	this->data_bits = data_bits;
}

Color::Color()
{
	this->red = 0x00;
	this->green = 0x00;
	this->blue = 0x00;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	this->red = r;
	this->green = g;
	this->blue = b;
}

void Color::Set(unsigned char r, unsigned char g, unsigned char b)
{
	this->red = r;
	this->green = g;
	this->blue = b;
}

void Color::Set(Color color)
{
	this->Set(color.red, color.green, color.blue);
}
		
const Color Color::RED(0xFF, 0x00, 0x00);
const Color Color::GREEN(0x00, 0xFF, 0x00);
const Color Color::BLUE(0x00, 0x00, 0xFF);
const Color Color::WHITE(0xFF, 0xFF, 0xFF);
const Color Color::BLACK(0x00, 0x00, 0x00);