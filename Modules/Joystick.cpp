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

#include "Joystick.h"

using namespace gadgeteering;
using namespace gadgeteering::modules;
using namespace gadgeteering::interfaces;

Joystick::Joystick(unsigned char socketNumber)
{
	socket* t_socket = mainboard->getSocket(socketNumber);
	t_socket->ensureTypeIsSupported(socket::types::A);

    this->button = new digital_input(socket, socket::pins::Three, resistor_modes::PULL_UP);
	this->x = new analog_input(socket, socket::pins::Four);
	this->y = new analog_input(socket, socket::pins::Five);
}

Joystick::~Joystick()
{
	delete this->button;
	delete this->x;
	delete this->y;
}

bool Joystick::isPressed()
{
	return !this->button->read();
}

void Joystick::getXY(double* x, double* y)
{
	if (x) *x = this->getX();
	if (y) *y = this->getY();
}

double Joystick::getX()
{
	return this->x->readProportion();
}

double Joystick::getY()
{
	return 1.0 - this->y->readProportion();
}