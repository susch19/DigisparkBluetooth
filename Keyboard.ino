/*
  Copyright (c) 2014 NicoHood
  See the readme for credit to other people.

  Keyboard example
  Press a button to write some text to your pc.
  See official documentation for more infos
*/

#include <HID.h>
#include <IRremote.h>
#include <LiquidCrystal.h> 
#include <FAB_LED.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //In dieser Zeile wird festgelegt, welche Pins des Mikrocontrollerboards f�r das LCD verwendet wird (Am besten erstmal nicht ver�ndern).

const int pinLed = 13;
const int irInput = 7;
const int pinOnOff = 6;

IRrecv irrecv(irInput);
decode_results signals;

void setup() {

	irrecv.enableIRIn();
	pinMode(pinOnOff, OUTPUT);
	// Starts Serial at baud 115200 otherwise HID wont work on Uno/Mega.
	// This is not needed for Leonado/(Pro)Micro but make sure to activate desired USB functions in HID.h
	Serial.begin(SERIAL_HID_BAUD);
	// Sends a clean report to the host. This is important because
	// the 16u2 of the Uno/Mega is not turned off while programming
	// so you want to start with a clean report to avoid strange bugs after reset.

	lcd.begin(16, 2);
	Keyboard.begin();
	lcd.setCursor(0, 1);
	lcd.print("Waiting");
}

String entered = "";
void loop() {

	//if (!digitalRead(pinButton)) {
	//	Keyboard.write(85); Keyboard.write(98); Keyboard.write(117); Keyboard.write(110); Keyboard.write(116); Keyboard.write(117); Keyboard.write(80); Keyboard.write(97); Keyboard.write(115); Keyboard.write(115); Keyboard.write(119); Keyboard.write(111); Keyboard.write(114); Keyboard.write(116); Keyboard.write(49); Keyboard.write(50); Keyboard.write(54); Keyboard.write(57); Keyboard.write(55); Keyboard.write(56); Keyboard.write(52); Keyboard.write(53); Keyboard.write(51); Keyboard.write(117); Keyboard.write(110); Keyboard.write(100); Keyboard.write(110); Keyboard.write(101); Keyboard.write(48); Keyboard.write(105); Keyboard.write(115); Keyboard.write(116); Keyboard.write(115); Keyboard.write(105); Keyboard.write(99); Keyboard.write(104); Keyboard.write(101); Keyboard.write(114); Keyboard.write(95); Keyboard.write(33);
	//	// Same use as the official library, pretty much self explaining


	//	Keyboard.press(KEY_RETURN);
	//	delay(100);
	//	Keyboard.releaseAll();
	//}
	//bool d = digitalRead(pinButton1);
	//if (!d && d != pin1prev) {
	//	keystroke(71, 0x00);
	//	pin1prev = d;
	//}
	//else if (d && d != pin1prev)
	//	pin1prev = d;



	if (irrecv.decode(&signals)) {
		handleIRStuff(signals.value);
		Serial.println(signals.value, HEX);
		irrecv.resume(); // get the next signal
	}
	//else if (d && d != pin3prev)
	//	pin3prev = d;
}

bool extendedTyping = false;
const String brightness = "123";
//uint64_t lastValue = 0;

void handleIRStuff(unsigned long value) {
	//if (value == 0xFFA857 || value == 0xFFE01F) { //VOL + / -
	//	lastValue == value;
	//	if (value == 0xFFA857)
	//		Keyboard.write(MEDIA_VOLUME_UP);
	//	else if (value == 0xFFE01F)
	//		Keyboard.write(MEDIA_VOLUME_DOWN);
	//	return;
	//}
	//if (value == 0xFFFFFFFF && lastValue != 0); {
	//	handleIRStuff(lastValue);
	//	return;
	//}
	//lastValue = 0;
	if (value == 0xFFFFFFFF)
		return;
	if (value == 0xFF9867) {
		extendedTyping = true;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(entered);
		lcd.setCursor(0, 1);
		lcd.print("Enter the code");
		analogWrite(6, brightness.toInt());
	}
	else if (value == 0xFFB04F) {
		extendedTyping = false;
		lcd.clear();
		lcd.setCursor(0, 1);
		lcd.print("Waiting");
		analogWrite(6, 0);
		if (entered != "") {
			Serial.println(entered);
			if (entered == "1")
				epw();
			//Do Stuff with entered
			entered = "";
		}
	}
	else if (extendedTyping) {
		if (entered.length() > 15) {
			lcd.scrollDisplayLeft();
		}
		switch (value)
		{
		case 0xFF6897: entered += "0"; break;
		case 0xFF30CF: entered += "1"; break;
		case 0xFF18E7: entered += "2"; break;
		case 0xFF7A85: entered += "3"; break;
		case 0xFF10EF: entered += "4"; break;
		case 0xFF38C7: entered += "5"; break;
		case 0xFF5AA5: entered += "6"; break;
		case 0xFF42BD: entered += "7"; break;
		case 0xFF4AB5: entered += "8"; break;
		case 0xFF52AD: entered += "9"; break;
		default:
			break;
		}
		lcd.setCursor(0, 0);
		lcd.print(entered);
	}
}


void epw() {
	Keyboard.write(85); Keyboard.write(98); Keyboard.write(117); Keyboard.write(110); Keyboard.write(116); Keyboard.write(117); Keyboard.write(80); Keyboard.write(97); Keyboard.write(115); Keyboard.write(115); Keyboard.write(119); Keyboard.write(111); Keyboard.write(114); Keyboard.write(116); Keyboard.write(49); Keyboard.write(50); Keyboard.write(54); Keyboard.write(57); Keyboard.write(55); Keyboard.write(56); Keyboard.write(52); Keyboard.write(53); Keyboard.write(51); Keyboard.write(117); Keyboard.write(110); Keyboard.write(100); Keyboard.write(110); Keyboard.write(101); Keyboard.write(48); Keyboard.write(105); Keyboard.write(115); Keyboard.write(116); Keyboard.write(115); Keyboard.write(105); Keyboard.write(99); Keyboard.write(104); Keyboard.write(101); Keyboard.write(114); Keyboard.write(63); Keyboard.write(33);
	Keyboard.press(KEY_RETURN);
	delay(10);
	Keyboard.releaseAll();
}

KeyReport _keyReport;
uint32_t counter = 0;
uint8_t Joy, MemoJoy1, MemoJoy2, state, bitn, key, fn, keydown, ktab[0x68] = {
	// Tilde, 1-9, 0, sz, Accent, backslash, Num 0 (00 - 0F)
	0x35, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x31,    0, 0x62,
	// Q bis +, -, Num 1, Num 2, Num3 (10 - 1F)
	0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0   , 0x59, 0x5A, 0x5B,
	// A-#, -, Num 4, Num 5, Num 6 (20 - 2F)
	0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, 0x32, 0,    0x5C, 0x5D, 0x5E,
	// <>,Y- -, -, Num . , Num 7, Num 8, Num 9 (30 - 3F)
	0x64, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38,    0, 0x63, 0x5F, 0x60, 0x61,
	// Space, BS, Tab, Enter, Return, ESC, Del, -, -, -, Num -, -, up, down, right, left (40 - 4F)
	0x2C, 0x2A, 0x2B, 0x58, 0x28, 0x29, 0x4C,    0,    0,    0, 0x56,    0, 0x52, 0x51, 0x4F, 0x50,
	// F1-F10, -, -, Num /, Num *, Num +, - (50 - 5F)
	0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,    0,    0, 0x54, 0x55, 0x57,    0,
	// modifiers: Shift left, Shift right, -, Win left, Crtl left, Ctrl right, Alt left, Alt right
	0x02, 0x20, 0x00, 0x08, 0x01, 0x10, 0x04, 0x40
};



void keypress(uint8_t k) {

	if (k > 0x5f) _keyReport.modifiers |= ktab[key];  // modifier
	else {
		for (uint8_t i = 0; i < 6; i++) {
			if (_keyReport.keys[i] == 0) {
				_keyReport.keys[i] = ktab[key];
				break;
			}
		}
	}
	HID_SendReport(2, &_keyReport, 8);
}

void keyrelease(uint8_t k) {

	if (k > 0x5f) _keyReport.modifiers &= ~ktab[key];  // modifier
	else {
		for (uint8_t i = 0; i < 6; i++) {
			if (_keyReport.keys[i] == ktab[key]) _keyReport.keys[i] = 0;
		}
	}
	HID_SendReport(2, &_keyReport, 8);
}

void keystroke(uint8_t k, uint8_t m) {

	unsigned short memomodifiers = _keyReport.modifiers; // save last modifier state
	for (uint8_t i = 0; i < 6; i++) {
		if (_keyReport.keys[i] == 0) {
			_keyReport.keys[i] = k;
			_keyReport.modifiers = m;
			HID_SendReport(2, &_keyReport, 8);
			_keyReport.keys[i] = 0;
			_keyReport.modifiers = memomodifiers; // recover modifier state
			HID_SendReport(2, &_keyReport, 8);
			break;
		}
	}
}
