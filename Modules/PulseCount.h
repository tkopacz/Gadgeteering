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

#pragma once

#include "../Gadgeteering.h"

namespace gadgeteering
{
	namespace modules
	{
		class pulse_count
		{
			const socket& sock;
			interfaces::digital_input miso;
			interfaces::digital_output mosi;
			interfaces::digital_output clock;
			interfaces::digital_output cs;

			unsigned char ls7366_1b_wr[1]; // write one byte
			unsigned char ls7366_2b_wr[2]; // write two bytes
			unsigned char ls7366_3b_wr[3]; // write three bytes
			unsigned char ls7366_1b_rd[1]; // read two bytes
			unsigned char ls7366_2b_rd[2]; // read two bytes
			unsigned char ls7366_4b_rd[4]; // read four bytes

			struct commands
			{
				static const unsigned char LS7366_CLEAR = 0x00; // clear register
				static const unsigned char LS7366_READ = 0x40; // read register
				static const unsigned char LS7366_WRITE = 0x80; // write register
				static const unsigned char LS7366_LOAD = 0xC0; // load register
			};

			struct registers
			{
				static const unsigned char LS7366_MDR0 = 0x08; // select MDR0
				static const unsigned char LS7366_MDR1 = 0x10; // select MDR1
				static const unsigned char LS7366_DTR = 0x18; // select DTR
				static const unsigned char LS7366_CNTR = 0x20; // select CNTR
				static const unsigned char LS7366_OTR = 0x28; // select OTR
				static const unsigned char LS7366_STR = 0x30; // select STR
			};

			struct mdr0_mode
			{
				static const unsigned char LS7366_MDR0_QUAD0 = 0x00; // none quadrature mode
				static const unsigned char LS7366_MDR0_QUAD1 = 0x01; // quadrature x1 mode
				static const unsigned char LS7366_MDR0_QUAD2 = 0x02; // quadrature x2 mode
				static const unsigned char LS7366_MDR0_QUAD4 = 0x03; // quadrature x4 mode
				static const unsigned char LS7366_MDR0_FREER = 0x00; // free run mode
				static const unsigned char LS7366_MDR0_SICYC = 0x04; // single cycle count mode
				static const unsigned char LS7366_MDR0_RANGE = 0x08; // range limit count mode (0-DTR-0)
				static const unsigned char LS7366_MDR0_MODTR = 0x0C; // modulo-n count (n=DTR both dirs)
				static const unsigned char LS7366_MDR0_DIDX = 0x00; // disable index
				static const unsigned char LS7366_MDR0_LDCNT = 0x10; // config IDX as load DTR to CNTR
				static const unsigned char LS7366_MDR0_RECNT = 0x20; // config IDX as reset CNTR (=0)
				static const unsigned char LS7366_MDR0_LDOTR = 0x30; // config IDX as load CNTR to OTR
				static const unsigned char LS7366_MDR0_ASIDX = 0x00; // asynchronous index
				static const unsigned char LS7366_MDR0_SYINX = 0x40; // synchronous IDX (if !NQUAD)
				static const unsigned char LS7366_MDR0_FFAC1 = 0x00; // filter clock division factor=1
				static const unsigned char LS7366_MDR0_FFAC2 = 0x80; // filter clock division factor=2
				static const unsigned char LS7366_MDR0_NOFLA = 0x00; // no flags
			};

			struct count_mode
			{
				static const unsigned char NoneQuad = 0x00; // none quadrature mode
				static const unsigned char Quad1 = 0x01; // quadrature x1 mode
				static const unsigned char Quad2 = 0x02; // quadrature x2 mode
				static const unsigned char Quad4 = 0x03; // quadrature x4 mode
			};

			struct mdr1_mode
			{
				static const unsigned char LS7366_MDR1_4BYTE = 0x00; // 4 byte counter mode
				static const unsigned char LS7366_MDR1_3BYTE = 0x01; // 3 byte counter mode
				static const unsigned char LS7366_MDR1_2BYTE = 0x02; // 2 byte counter mode
				static const unsigned char LS7366_MDR1_1BYTE = 0x03; // 1 byte counter mode
				static const unsigned char LS7366_MDR1_ENCNT = 0x00; // enable counting
				static const unsigned char LS7366_MDR1_DICNT = 0x04; // disable counting
				static const unsigned char LS7366_MDR1_FLIDX = 0x20; // FLAG on IDX (index)
				static const unsigned char LS7366_MDR1_FLCMP = 0x40; // FLAG on CMP (compare)
				static const unsigned char LS7366_MDR1_FLCY = 0x80; // FLAG on CY (carry)
			};

			void initialize();

			unsigned char read_one_byte(unsigned char reg);
			unsigned short read_two_bytes(unsigned char reg);
			void write_one_byte(unsigned char reg);
			void write_two_bytes(unsigned char reg, unsigned char cmd);
			void software_spi_write_read(const unsigned char* write, unsigned int write_length, unsigned char* read, unsigned int read_length);

		public:
			typedef unsigned char direction;
			struct directions
			{
				static const direction DOWN = 0x00;
				static const direction UP = 0x01;
			};

			pulse_count(unsigned char socket_number);

			long read_encoders();
			unsigned char read_status_reg();
			direction read_direction();
			void set_count_mode(unsigned char new_mode);
			void clear_register();
		};
	}
}
