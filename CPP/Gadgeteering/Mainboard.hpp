#ifndef _MAINBOARD_H_
#define _MAINBOARD_H_

#include <Arduino.h>

class Module {
	protected:
		Module();
};

class Socket {
	static const int PINS_PER_SOCKET = 10;
	static const int PIN_UNCONNECTED = -1;
	
	public:
		typedef byte Pin;
		typedef int Type;
		typedef byte IOState;
		typedef byte ResistorMode;

		const int number;
		const Type type;
		Pin pins[Socket::PINS_PER_SOCKET];
		
		//I didn't use enums because their members are hoisted into and pollute
		//the parent scope, and Arduino doesn't have C++11 enum class yet.
		class IOStates {
			public:
				static const IOState OUT = 0;
				static const IOState IN = 1;
				static const IOState PWM = 2;
		};

		class Pins {
			public:
				static const Pin Three = 3;
				static const Pin Four = 4;
				static const Pin Five = 5;
				static const Pin Six = 6;
				static const Pin Seven = 7;
				static const Pin Eight = 8;
				static const Pin Nine = 9;
		};

		class Types {
			public:
				static const Type A = 0x00000001;
				static const Type B = 0x00000002;
				static const Type C = 0x00000004;
				static const Type D = 0x00000008;
				static const Type E = 0x00000010;
				static const Type F = 0x00000020;
				static const Type G = 0x00000040;
				static const Type H = 0x00000080;
				static const Type I = 0x00000100;
				static const Type K = 0x00000200;
				static const Type O = 0x00000400;
				static const Type P = 0x00000800;
				static const Type R = 0x00001000;
				static const Type S = 0x00002000;
				static const Type T = 0x00004000;
				static const Type U = 0x00008000;
				static const Type X = 0x00010000;
				static const Type Y = 0x00020000;
				static const Type Z = 0x00040000;
				static const Type DL = 0x00080000;
		};

		class ResistorModes {
			public:
				static const ResistorMode PULL_UP = 0;
				static const ResistorMode PULL_DOWN = 1;
				static const ResistorMode FLOATING = 2;
		};

		Socket(int number, Type type);

		void ensureTypeIsSupported(Type type);

		virtual void setPWM(Pin pinNumber, double dutyCycle, double frequency);
		virtual bool readDigital(Pin pinNumber);
		virtual void writeDigital(Pin pinNumber, bool value);
		virtual double readAnalog(Pin pinNumber);
		virtual void writeAnalog(Pin pinNumber, double voltage);
		virtual void setIOMode(Pin pinNumber, IOState state, ResistorMode resistorMode = ResistorModes::FLOATING);
};

class Mainboard {
	struct ListNode {
		Socket* socket;
		ListNode* next;
	};

	ListNode* sockets;

	protected:
		Mainboard();

		Socket* registerSocket(Socket* socket);

	public:
		void panic(const char* error);
		Socket* getSocket(int number);
};

extern Mainboard* mainboard;

#endif
