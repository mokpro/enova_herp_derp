#include "Arduino.h"

/***********************************************************/

// Serial MP3 Player Catalex (YX5300 chip)
#include "mp3serial.h"
int lightPin = 0;  //define a pin for Photo resistor
bool low = false;

void setup() {
	Serial.begin(9600);
	mp3.begin(9600);
	delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
	delay(200);
	sendCommand(CMD_PLAY_W_VOL, 0X0F01); // Playing a 15 (0x0F) Vol the song num 01 (0x01).
}


void loop() {
 	char c=' ';
 	int lightPinOutput;

 	lightPinOutput = analogRead(lightPin);
 	delay(200);

	if(lightPinOutput < 700 && !low) {
		low = true;
		c = 'n';
	} else if(lightPinOutput >= 700){
		low = false;
	}


  if( Serial.available() )
		c = Serial.read();

	if(c != ' ')
		sendMP3Command(c);

  // Check for the answer.
  if (mp3.available())
    Serial.println(decodeMP3Answer());

  delay(100);
}
