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

#include "SoftwareI2C.h"
#include "Mainboard.h"
#include "System.h"

using namespace gadgeteering;

#define i2c_delay() ;

software_i2c::software_i2c(cpu_pin sda, cpu_pin scl)
{
	this->start = false;
	this->read_scl();
	this->read_sda();
}

void software_i2c::clear_scl()
{
	mainboard->set_io_mode(this->scl, io_modes::DIGITAL_OUTPUT, resistor_modes::NONE);
	mainboard->write_digital(this->scl, false);
}

bool software_i2c::read_scl()
{
	mainboard->set_io_mode(this->scl, io_modes::DIGITAL_INPUT, resistor_modes::PULL_UP);
	return mainboard->read_digital(this->scl);
}

void software_i2c::clear_sda()
{
	mainboard->set_io_mode(this->sda, io_modes::DIGITAL_OUTPUT, resistor_modes::NONE);
	mainboard->write_digital(this->sda, false);
}

bool software_i2c::read_sda()
{
	mainboard->set_io_mode(this->sda, io_modes::DIGITAL_INPUT, resistor_modes::PULL_UP);
	return mainboard->read_digital(this->sda);
}

bool software_i2c::write_bit(bool bit)
{
	if (bit)
		this->read_sda();
	else
		this->clear_sda();

	i2c_delay();

	unsigned long end = system::time_elapsed() + 5000;
	while (!this->read_scl() && system::time_elapsed() < end)
		;

	if (bit && !this->read_sda())
		return false;

	i2c_delay();
	this->clear_scl();

	return true;
}

bool software_i2c::read_bit()
{
	this->read_sda();

	i2c_delay();

	unsigned long end = system::time_elapsed() + 5000;
	while (!this->read_scl() && system::time_elapsed() < end)
		;

	bool bit = this->read_sda();

	i2c_delay();
	this->clear_scl();

	return bit;
}

bool software_i2c::send_start_condition()
{
	if (this->start)
	{
		this->read_sda();
		i2c_delay();

		unsigned long end = system::time_elapsed() + 5000;
		while (!this->read_scl() && system::time_elapsed() < end)
			;

	}

	if (!this->read_sda())
		return false;

	this->clear_sda();
	i2c_delay();
	this->clear_scl();

	this->start = true;

	return true;
}

bool software_i2c::send_stop_condition()
{
	this->clear_sda();
	i2c_delay();

	unsigned long end = system::time_elapsed() + 5000;
	while (!this->read_scl() && system::time_elapsed() < end)
		;

	if (!this->read_sda())
		return false;

	i2c_delay();
	this->start = false;

	return true;
}

bool software_i2c::transmit(bool send_start, bool send_stop, unsigned char data)
{
	unsigned char bit;
	bool nack;

	if (send_start)
		this->send_start_condition();

	for (bit = 0; bit < 8; bit++)
	{
		this->write_bit((data & 0x80) != 0);

		data <<= 1;
	}

	nack = this->read_bit();

	if (send_stop)
		this->send_stop_condition();

	return nack;
}

unsigned char software_i2c::receive(bool send_ack, bool send_stop_condition)
{
	unsigned char d = 0;
	unsigned char bit = 0;

	for (bit = 0; bit < 8; bit++)
	{
		d <<= 1;

		if (this->read_bit())
			d |= 1;
	}

	this->write_bit(!send_ack);

	if (send_stop_condition)
		this->send_stop_condition();

	return d;
}

bool software_i2c::write(const unsigned char* buffer, unsigned int length, bool send_start, bool send_stop)
{
	bool result = true;

	if (!this->transmit(send_start, length == 1 ? send_stop : false, buffer[0]))
		result = false;

	for (unsigned int i = 1; i < length; i++)
		if (!this->transmit(false, i == length - 1 ? send_stop : false, buffer[i]))
			result = false;

	return result;
}

bool software_i2c::read(unsigned char* buffer, unsigned int length, bool send_start, bool send_stop)
{
	bool result = true;

	if (send_start)
		this->send_start_condition();

	for (unsigned int i = 0; i < length; i++)
		buffer[i] = this->receive(true, i == length - 1 ? send_stop : false);

	return result;
}