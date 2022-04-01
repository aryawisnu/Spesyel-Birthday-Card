#include <TinyOzOLED.h>
#include <TinyWireM.h>
#include <tinyNeoPixel.h>
//insialisasi pin
#define MIC_PIN A2 
#define PIN 1
#define PIEZO_PIN 3
//data
tinyNeoPixel pixels = tinyNeoPixel(16, PIN, NEO_GRB);
int sensorValue;
bool a = false;

//NOTE FOR MELODIES
#define NOTE_C4  262//
#define NOTE_D4  294//
#define NOTE_E4  330//
#define NOTE_F4  349//
#define NOTE_G4  392//
#define NOTE_A4  440//
#define NOTE_AS4 466//
#define NOTE_C5  523/

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 2, 2, 2, 1, /*line 1*/
  4, 4, 2, 2, 2, 1, /*line 2*/
  4, 4, 2, 2, 4, 4, 2, 1, /*line 3*/
  4, 4, 2, 2, 2, 1
};

void setup() {
  //pinMode(PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  pixels.begin();
  OzOled.init();                 
  OzOled.setNormalDisplay();  
  OzOled.setHorizontalMode();   
  pixels.setBrightness(40);
  pixels.show(); 

    OzOled.setCursorXY(0,0);   
    OzOled.printString("      HAPPY ");  
    OzOled.setCursorXY(0,1);   
    OzOled.printString("     BIRTHDAY");
    OzOled.setCursorXY(0,2);  
    OzOled.printString("    COMEL !!! "); 

  for (int thisNote = 0; thisNote < 27 ; thisNote++) {
    //nyalakan led warna random
    int r = random(0,255);
    int g = random(0,255);
    int b = random(0,255);
    pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.setPixelColor(1, pixels.Color(r,g,b));
    pixels.show();
    //mainkan nada
    int noteDuration = 1000/noteDurations[thisNote];
    tone(PIEZO_PIN, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIEZO_PIN);
  }
    OzOled.clearDisplay(); 
    OzOled.setCursorXY(0,0);   
    OzOled.printString("  MAKE A WISH");  
    OzOled.setCursorXY(0,1);   
    OzOled.printString("    AND TIUP");
    OzOled.setCursorXY(0,2);  
    OzOled.printString("  LILINNYA!!!! ");  
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(MIC_PIN);
  if(a==false){
  pixels.setPixelColor(0, pixels.Color(255,20,5));
  pixels.setPixelColor(1, pixels.Color(255,20,5));
  pixels.setBrightness(random(0,100));
  pixels.show();
  delay(100);
    if (sensorValue < 200 && a==false){
      OzOled.clearDisplay(); 
      OzOled.setCursorXY(0,0);   
      OzOled.printString(" Jangan Lupa ");  
      OzOled.setCursorXY(0,1);   
      OzOled.printString("      SCAN ");
      OzOled.setCursorXY(0,2);  
      OzOled.printString(" BARCODENYAA!!!");
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.show(); 
      a = true;
      }
  }
}
