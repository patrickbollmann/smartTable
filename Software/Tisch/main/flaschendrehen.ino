int pos = 0;
int flaschendrehenFelder[]={0,1,2,3,4,5,6,7,8,9,10,29,30,49,50,69,70,89,90,91,92,93,94,95,96,97,98,99,80,79,60,59,40,39,20,19,0};


void flaschendrehen(){
  if(IRWert[45] > 950 or IRWert[44] > 950 or IRWert[54] > 950 or IRWert[55] > 950){
  int runden = 0;
   
  int u =0;
  int i = 0;
  runden = random(50,200);
  
  for(i=0;i<26;i++){
    leds[flaschendrehenFelder[i]] = CRGB::Black;
  }
  leds[44] = CRGB::Black;
  leds[45] = CRGB::Black;
  leds[54] = CRGB::Black;
  leds[55] = CRGB::Black;
  
  FastLED.show();
  
  
  while(u<runden) {
    Serial.println("random:");
    Serial.println(u);
    Serial.println(runden);
    if(pos==36){
      pos=0;
    }
    leds[flaschendrehenFelder[pos]] = CRGB::Black;
    leds[flaschendrehenFelder[pos+1]] = CRGB::Red;
    FastLED.show();
    delay(20);
    u++;
    pos++;
  }
  
  
  }
  
  leds[44] = CRGB::Blue;
  leds[45] = CRGB::Blue;
  leds[54] = CRGB::Blue;
  leds[55] = CRGB::Blue;
  FastLED.show();
}


