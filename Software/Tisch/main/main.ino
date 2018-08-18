#include "FastLED.h"
#include <Wire.h>
#define NUM_LEDS 100
const int dataline = 2;
CRGB leds[NUM_LEDS];
int bit1 = 0;
int bit2 = 0;
int bit3 = 0;

int r = 0;
int g = 0;
int b = 0;

int grenzwert = 450;
int geschwindigkeit = 160;

int programm = 0;

int IRWert[104];
//int IRPos = 0;
//int IRTimer[100];

void leseIR(){
  for ( int a = 0 ; a <= 12; a++ ) {
    digitalWrite(30 + a, LOW);
    for ( int i = 0 ; i <= 7; i++ ) {
      bit1 = bitRead(i, 0);
      bit2 = bitRead(i, 1);
      bit3 = bitRead(i, 2);

      digitalWrite(5, bit1);
      digitalWrite(6, bit2);
      digitalWrite(7, bit3);

      IRWert[i + (a * 8)] = analogRead(A0);
    }
    digitalWrite(30 + a, HIGH);

  }
}
//set every pixel to color color is a HTML wweb color name example: fill(CRGB::Red);
void fill(CRGB color){
   for (int p = 0; p < NUM_LEDS; p++) {
    leds[p] = color;
  }
}

// set Pixel in Matrix. This function translates x,y cords into real table led nr.
void setpixel(int x, int y, CRGB color) {

  leds[XY(x, y)] = (color);
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int rec = Wire.read();    // receive byte as an integer
  Serial.println(rec);         // print the integer
  if(rec >= 81){
    FastLED.setBrightness((rec-80)*25); // rec[81,90] -> rec-80 [1,10] setBrightness(x) x[0,255]
  }else{
    programm = rec;
  }
}

void setup() { 
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  LEDS.addLeds<WS2812B, dataline>(leds, NUM_LEDS);
  konfiguriereMultiplexer();
  startAnimation();
  //maleTestKanten();
  neustart();
}



void loop() {
  if(programm == 10){
    glediator();
  }else if(programm == 11){
    leseIR();
    pong();
  }else if(programm == 12){
    leseIR();
    paint();
  }else if(programm == 0){
    fill(CRGB::HotPink);
  }else if(programm == 1){
    fill(CRGB::Purple);
  }else if(programm == 2){
    fill(CRGB::Blue);
  }else if(programm == 3){
    fill(CRGB::Cyan);
  }else if(programm == 4){
    fill(CRGB::Green);
  }else if(programm == 5){
    fill(CRGB::Lime);
  }else if(programm == 6){
    fill(CRGB::Yellow);
  }else if(programm == 7){
    fill(CRGB::Orange);
  }else if(programm == 8){
    fill(CRGB::Red);
  }else if(programm == 9){
    fill(CRGB::White);
  }
  FastLED.show();
}



//-------------funktionen-------------
void startAnimation() {
  for (int p = 0; p < NUM_LEDS; p++) {
    leds[p] = CRGB::Blue;
    FastLED.show();
  }
}

void konfiguriereMultiplexer() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  for (int i = 29; i <= 42; i++) {
    pinMode(i, OUTPUT);
  }
  for (int p = 31; p < 43; p++) {
    digitalWrite(p, HIGH);
  }
}

// returns the led nr by the x and y coords
int XY( int x, int y) {
  int i;
  int matrixBreite = 10;
  if ( y & 0x01) {
    // ungerade Reihen
    int reverseX = (10 - 1) - x;
    i = (y * matrixBreite) + reverseX;
  } else {
    // gerade Reihen
    i = (y * matrixBreite) + x;
  }
  return i;
}



