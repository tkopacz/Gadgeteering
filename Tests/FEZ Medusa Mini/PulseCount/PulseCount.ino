#include <Wire.h>
#include <SPI.h>

#include <Gadgeteering.h>

#include <Mainboards/FEZMedusaMini.h>
#include <Modules/PulseCount.h>

using namespace gadgeteering;
using namespace gadgeteering::mainboards;
using namespace gadgeteering::modules;

void loop()
{

}

void setup()
{
	Serial.begin(9600);

	fez_medusa_mini board;
	pulse_count counter(1);

	while(true)
	{
		Serial.print(counter.read_encoders()); Serial.print(" "); Serial.print(static_cast<int>(counter.read_direction())); Serial.println("");
		system::sleep(500);
	}
	
	return;
}
