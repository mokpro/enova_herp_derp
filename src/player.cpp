#include "Arduino.h"

/***********************************************************/

// Serial MP3 Player Catalex (YX5300 chip)
#include "mp3serial.h"
int lightPin0 = 0;  //define a pin for Photo resistor
int lightPin1 = 1;  //define a pin for Photo resistor

bool low = false;
int16_t lastSongPlayed = 0X0F00;


void setup() {
	Serial.begin(9600);
	mp3.begin(9600);
	delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
	delay(200);
	sendCommand(CMD_PLAY_W_VOL, 0X0F01); // Playing a 15 (0x0F) Vol the song num 01 (0x01).
}

void playSong(int16_t songToPlay) {

	// Playing a 15 (0x0F) Vol the song num 01 (0x01).
	if(lastSongPlayed != songToPlay) {
		lastSongPlayed = songToPlay;
		sendCommand(CMD_PLAY_W_VOL, songToPlay);
	}
}

void loop() {
 	char c=' ';
 	int lightPin0Reading;
	int lightPin1Reading;

 	lightPin0Reading = analogRead(lightPin0);
	lightPin1Reading = analogRead(lightPin1);

 	delay(200);

	// Serial.print("lightPin0Reading: ");
	// Serial.print(lightPin0Reading);
	// Serial.println("");
	//
	// Serial.print("lightPin1Reading: ");
	// Serial.print(lightPin1Reading);
	// Serial.println("");

	if(lightPin0Reading < 700 && !low) {
		low = true;
		playSong(0X0F02);
	} else if(lightPin0Reading >= 700){
		low = false;
	}

	if(lightPin1Reading < 700 && !low) {
		low = true;
		playSong(0X0F04);
	} else if(lightPin1Reading >= 700){
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
