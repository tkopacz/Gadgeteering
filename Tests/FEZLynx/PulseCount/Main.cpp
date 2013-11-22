#include <iostream>

#include <Gadgeteering.h>

#include <Mainboards/FEZLynxS4.h>
#include <Modules/PulseCount.h>

using namespace std;
using namespace gadgeteering;
using namespace gadgeteering::mainboards;
using namespace gadgeteering::modules;

int main(int argc, char** argv)
{
	fez_lynx_s4 board;
	pulse_count counter(1);

	while(true)
	{
		cout << counter.read_encoders() << " " << static_cast<int>(counter.read_direction()) << endl;
		system::sleep(500);
	}
	
	return 0;
}
