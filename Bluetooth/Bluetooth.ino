#include <SoftSerial_INT0.h>
#include "GermanKeyboard.h"

#define P_RX 2                        // Reception PIN (SoftSerial)
#define P_TX 1                        // Transmition PIN (SoftSerial)

SoftSerial BLE(P_RX, P_TX);           // Software serial port for control the BLE module

void setup()
{
	BLE.begin(57600);
	DigiKeyboard.delay(7500);
	DigiKeyboard.update();
	//String k = "asdl";
	p("test");
}
//bool germanLayout = true;
//static const char* string = "";
//char intarray[175];
//int o = 0;
void loop()
{
	//chars += 'a';
	DigiKeyboard.update(); // Update the USB connection (maintain alive the connection)
	while (BLE.available()) {
		//intarray[o++] += BLE.read();
		//chars += (char)BLE.read();
		s(BLE.read());
	}
	//if (!BLE.available())
	//{
	//	p(intarray);
	//	for (size_t i = 0; i < o; i++)
	//	{
	//		intarray[i] = 0;
	//	}
	//	o = 0;
	//}
}
/*
+
*/