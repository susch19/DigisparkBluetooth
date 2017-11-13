
void setup() {
	pinMode(0, OUTPUT);
}
void loop(){
	digitalWrite(0, 1);
	delay(100);
	digitalWrite(0, 0);
	delay(100);
}