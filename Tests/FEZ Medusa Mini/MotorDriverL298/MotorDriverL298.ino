#include <Wire.h>
#include <SPI.h>

#include <Gadgeteering.h>

#include <Mainboards/FEZMedusaMini.h>
#include <Modules/MotorDriverL298.h>

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
	motor_driver_l298 driver(2);

	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 25);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 50);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 75);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 100);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 0);
	system::sleep(1000);

	driver.move_motor(motor_driver_l298::motors::MOTOR_1, -25);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, -50);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, -75);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, -100);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_1, 0);
	system::sleep(1000);

	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 25);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 50);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 75);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 100);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 0);
	system::sleep(1000);

	driver.move_motor(motor_driver_l298::motors::MOTOR_2, -25);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, -50);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, -75);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, -100);
	system::sleep(1000);
	driver.move_motor(motor_driver_l298::motors::MOTOR_2, 0);
	system::sleep(1000);

	return;
}
