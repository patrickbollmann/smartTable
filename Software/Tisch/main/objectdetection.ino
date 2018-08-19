void objectdetection(){
  for ( int a = 0 ; a <= 100; a++ ) {
    if(IRWert[a] > grenzwert){
      leds[a] = CRGB( r, g, b);
      IRTimer[a] = 5;
    }else if(IRTimer[a] > 0){
      leds[a] = CRGB( r, g, b);
      IRTimer[a] -= 1;
    }else{
      leds[a] = CRGB::Black;
    } 
  }
}

