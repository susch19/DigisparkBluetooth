
#include <FAB_LED.h>
#include <HID.h>

// Declare the LED protocol and the port
sk6812<D, 1>  strip;

// How many pixels to control
const int numPixels = 60;

// How bright the LEDs will be (max 255)
const uint8_t maxBrightness = 60;

// The pixel array to display
rgbw  pixels[numPixels] = {};

int k = 0;

void updateColors(int i, int rgb)
{
	int r = rgb >> 16;
	int g = (rgb >> 8) % 256;
	int b = rgb % 256;

	if (r > 0) r = 255;
	if (b > 0) b = 255;
	if (g > 0) g = 255;

	pixels[i - 1].g = 0; //Rot
	pixels[i - 1].r = 0; //Rot
	pixels[i - 1].b = 0; //Rot
	for (int lop = 1; lop <= 10; lop++)
	{
		pixels[numPixels - lop].r = 0;
		pixels[numPixels - lop].g = 0;
		pixels[numPixels - lop].b = 0;
		pixels[numPixels - lop].w = 0;
	}
	for (int o = i; o < i + 10; o++)
	{
		pixels[o].r = g; // grün
		pixels[o].b = b; // blau
		pixels[o].g = r; //Rot
		pixels[o].w = 255;

	}
	strip.sendPixels(numPixels, pixels);
}


void setup()
{
	strip.clear(1000);
}
void loop()
{
	for (int i = 0; i < 3; i++)
	{
		int t = 256 << i * 8;
		for (int led = 0; led < numPixels; led++)
		{
			updateColors(led, t);
			delay(5);
		}
	}

	/*if (k % numPixels == 0) {
		strip.clear(numPixels);
	}*/
}
