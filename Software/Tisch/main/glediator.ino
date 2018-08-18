int serialReadBlocking() {
  while (!Serial.available()) {}
  return Serial.read(); 
}
void glediator(){
  while (serialReadBlocking() != 1) {} 
   
   for (long i=0; i < NUM_LEDS; i++) {
     leds[i].r = serialReadBlocking();
     leds[i].g = serialReadBlocking();
     leds[i].b = serialReadBlocking();
   }
}

