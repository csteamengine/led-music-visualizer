#include <FastLED.h>

//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 
#define DATA_PIN     6
#define NUM_LEDS    20
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define BUTTONDOWN    11
#define BUTTONUP      12

// I'm seeing best results using band 4 to isolate the drumbeats
#define DRUM_BAND 4

// Depending on the music you're playing and the volume you have it set to, you may need to tweak either 
// the volume or this level to respond to all the drumbeats but not to other elements of the music
#define DRUM_VOLUME_THRESHOLD 170

// Leave this at 1 for a good basic fade, or decrease it to 0 for a quicker fade, or increase it to 2, 3, 
// etc. for a more drawn-out fade
#define FADE_DELAY 1

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;
int hue = 0;

int fadeCountdown = FADE_DELAY;

CRGB leds[NUM_LEDS];

/********************Setup Loop*************************/
void setup() {
  pinMode(BUTTONUP, INPUT_PULLUP);
  pinMode(BUTTONDOWN, INPUT_PULLUP);
  
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  turnOffAllLeds();
}

/**************************Main Function Loop*****************************/
void loop() {
  readButtons();
  readFrequencies();
  setLeds();
  fadeLeds();
  //printFrequenciesOne();
  //printFrequenciesTwo();
  delay(50);
 
}

void readButtons(){
  if(digitalRead(BUTTON_UP) == LOW && digitalRead(BUTTON_DOWN) == LOW){
    readLedCount();   
  }
}

void readLedCount(){
  int ledCount = NUM_LEDS;
  while(1){
    //TODO make sure this is the right color
    fill_solid(leds, ledCount, CHSV(hue, 255, BRIGHTNESS));
    if(digitalRead(BUTTON_UP) == LOW && digitalRead(BUTTON_DOWN) == HIGH){
      ledCount++;
    }else if(digitalRead(BUTTON_UP) == HIGH && digitalRead(BUTTON_DOWN) == LOW){
      ledCount--;
    }else if(digitalRead(BUTTON_UP) == LOW && digitalRead(BUTTON_DOWN) == LOW){
      updateLedCount();
      break;
    }
    delay(50);
  }
}

void updateLedCount(){
  //TODO update the EEPROM with new LED count
  //TODO flash LED strip to confirm updated count
}
void fadeLeds(){
  if (fadeCountdown == 0) {
    fadeToBlackBy(leds, NUM_LEDS, 1);
    FastLED.show();
    fadeCountdown = FADE_DELAY;
  } else {
    fadeCountdown--;
  }
}

//This function is very basic and will be updated and improved.
void setLeds(){
  if (freq_amp == DRUM_BAND && (Frequencies_One[DRUM_BAND] > DRUM_VOLUME_THRESHOLD || Frequencies_Two[DRUM_BAND] > DRUM_VOLUME_THRESHOLD)) {
    // We're fading all the time, but only going to 100% brightness when there's a beat
    fill_solid(leds, NUM_LEDS, CHSV(hue, 255, BRIGHTNESS));
    // Might as well have some color variation
    hue = (hue + 1) % 256;
  } 
}

void turnOffAllLeds() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

/*******************Pull frquencies from Spectrum Shield********************/
void readFrequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

void printFrequenciesOne(){
  Serial.print("Freq 1: ");
  for(int i = 0; i<7; i++){
    Serial.print(" ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(Frequencies_One[i]);
  }
  Serial.println("");
}

void printFrequenciesTwo(){
  Serial.print("Freq 1: ");
  for(int i = 0; i<7; i++){
    Serial.print(" ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(Frequencies_Two);
  }
  Serial.println("");
}
