#define ROBOT_NAME "MyInputStick"

// If you haven't configured your device before use this
#define BLUETOOTH_SPEED 38400 //This is the default baudrate that HC-05 uses
// If you are modifying your existing configuration, use this:
// #define BLUETOOTH_SPEED 57600

#include <SoftSerial_INT0.h>

// Swap RX/TX connections on bluetooth chip
//   Pin 10 --> Bluetooth TX
//   Pin 11 --> Bluetooth RX
SoftSerial BLE(2, 1); // RX, TX

					  /*
					  The possible baudrates are:
					  AT+UART=1200,0,0 -------1200
					  AT+UART=2400,0,0 -------2400
					  AT+UART=4800,0,0 -------4800
					  AT+UART=9600,0,0 -------9600 - Default for hc-06
					  AT+UART=19200,0,0 ------19200
					  AT+UART=38400,0,0 ------38400
					  AT+UART=57600,0,0 ------57600 - Johnny-five speed
					  AT+UART=115200,0,0 -----115200
					  AT+UART=230400,0,0 -----230400
					  AT+UART=460800,0,0 -----460800
					  AT+UART=921600,0,0 -----921600
					  AT+UART=1382400,0,0 ----1382400
					  */

void setup() {
	pinMode(5, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
	digitalWrite(5, HIGH);
	Serial.begin(9600);

	Serial.println("Starting config");
	BLE.begin(BLUETOOTH_SPEED);
	delay(1000);

	// Should respond with OK
	BLE.print("AT\r\n");
	waitForResponse();

	// Should respond with its version
	BLE.print("AT+VERSION\r\n");
	waitForResponse();

	// Set pin to 0000
	BLE.print("AT+PSWD=1269\r\n");
	waitForResponse();

	// Set the name to ROBOT_NAME
	String rnc = String("AT+NAME=") + String(ROBOT_NAME) + String("\r\n");
	BLE.print(rnc);
	waitForResponse();

	// Set baudrate to 57600
	BLE.print("AT+UART=57600,0,0\r\n");
	waitForResponse();

	Serial.println("Done!");
	pinMode(1, OUTPUT);
}

void waitForResponse() {
	delay(1000);
	while (BLE.available()) {
		Serial.write(BLE.read());
	}
	Serial.write("\n");
}

void loop() {
	digitalWrite(1, LOW);
	delay(500);
	digitalWrite(1, HIGH);
	delay(500);
}