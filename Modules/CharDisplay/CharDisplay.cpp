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

#include "CharDisplay.h"

using namespace Gadgeteering;
using namespace Gadgeteering::Modules;
using namespace Gadgeteering::Interfaces;

CharDisplay::CharDisplay(unsigned char socketNumber) {
	this->socket = mainboard->getSocket(socketNumber);
	this->socket->ensureTypeIsSupported(Socket::Types::Y);

    this->lcdRS = new DigitalOutput(socket, Socket::Pins::Four, false);
    this->lcdE = new DigitalOutput(socket, Socket::Pins::Three, false);
    this->lcdD4 = new DigitalOutput(socket, Socket::Pins::Five, false);
    this->lcdD5 = new DigitalOutput(socket, Socket::Pins::Seven, false);
    this->lcdD6 = new DigitalOutput(socket, Socket::Pins::Nine, false);
    this->lcdD7 = new DigitalOutput(socket, Socket::Pins::Six, false);

    this->backlight = new DigitalOutput(socket, Socket::Pins::Eight, true);
	
    this->sendCommand(0x33);
    this->sendCommand(0x32);
    this->sendCommand(CharDisplay::DISP_ON);
	
    this->clear();
			
	System::Sleep(3);
}

CharDisplay::~CharDisplay() {
    delete this->lcdRS;
    delete this->lcdE;
    delete this->lcdD4;
    delete this->lcdD5;
    delete this->lcdD6;
    delete this->lcdD7;
    delete this->backlight;
}

void CharDisplay::sendNibble(unsigned char b) {
    this->lcdD7->write((b & 0x8) != 0);
    this->lcdD6->write((b & 0x4) != 0);
    this->lcdD5->write((b & 0x2) != 0);
    this->lcdD4->write((b & 0x1) != 0);
				
    this->lcdE->write(true);
	this->lcdE->write(false);

	System::Sleep(1);
}

void CharDisplay::sendByte(unsigned char b) {
    this->sendNibble((char)(b >> 4));
    this->sendNibble(b);
}

void CharDisplay::sendCommand(unsigned char c) {
    this->lcdRS->write(false); //set LCD to data mode
	this->sendByte(c);

	System::Sleep(2);

    this->lcdRS->write(true); //set LCD to data mode  
}

void CharDisplay::print(const char* string) {
	while (*string != '\0')
		this->print(*(string++));
}

void CharDisplay::print(char character) {
	this->sendByte(character);
}

void CharDisplay::clear() {
    this->sendCommand(CharDisplay::CLR_DISP);
	System::Sleep(2);
}

void CharDisplay::cursorHome() {
    this->sendCommand(CharDisplay::CUR_HOME);
	System::Sleep(2);
}

void CharDisplay::setCursor(unsigned char row, unsigned char col) {
    char offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    this->sendCommand(CharDisplay::SET_CURSOR | offsets[row] | col);
}

void CharDisplay::setBacklight(bool state) {
    this->backlight->write(state);
}