void paint(){
  
  //farbe wählen
  if(IRWert[3] > grenzwert){
    r = 0;
    g = 255;
    b = 255;
  }
  else if(IRWert[2] > grenzwert){
    r = 0;
    g = 0;
    b = 255;
  }
  else if(IRWert[1] > grenzwert){
    r = 160;
    g = 32;
    b = 240;
  }
  else if(IRWert[7] > grenzwert){
    r = 255;
    g = 0;
    b = 0;
  }
  else if(IRWert[6] > grenzwert){
    r = 255;
    g = 140;
    b = 0;
  }
  else if(IRWert[5] > grenzwert){
    r = 255;
    g = 255;
    b = 0;
  }
  else if(IRWert[4] > grenzwert){
    r = 0;
    g = 255;
    b = 0;
  }
  
  if(IRWert[0] > grenzwert){
    clear();
  }
  //setze Pixel
  for ( int a = 0 ; a <= 100; a++ ) {
    if(IRWert[a] > grenzwert){
      leds[a] = CRGB( r, g, b);
    }
    //setze farbauswahl
    leds[9] = CRGB( r, g, b);
    leds[7] = CRGB::Red;
    leds[6] = CRGB::Orange;
    leds[5] = CRGB::Yellow;
    leds[4] = CRGB::Green;
    leds[3] = CRGB::Cyan;
    leds[2] = CRGB::Blue;
    leds[1] = CRGB::Purple;
    leds[0] = CRGB::Black;
  }
  FastLED.show(); //bild rendern
}
