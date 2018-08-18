int px = 1;
int py = 1;
int angle = 45;
int blauPunkte = 0;
int rotPunkte = 0;
int speedup = 3;

void ballMalen(int x, int y){
  leds[XY(x,y)] = CRGB::White;
}
void maleBrackets(){
  for(int i=0; i<=9; i++){
    if(IRWert[XY(9,i)] > grenzwert){
    leds[XY(9,i)] = CRGB::Red;
  }
  }
  for(int i=0; i<=9; i++){
    if(IRWert[XY(0,i)] > grenzwert){
    leds[XY(0,i)] = CRGB::Blue;
  }
  }
}
void readyAnimation(){
  clear();
  for(int a = -1; a <=9; a+=2){
    for(int i = 0; i<=a; i++){
      leds[XY(4,i)] = CRGB::Green;
      leds[XY(5,i)] = CRGB::Green;
    }
    FastLED.show();
    delay(500);
}
   for(int i = 0; i<=9; i++){
    leds[XY(4,i)] = CRGB::Red;
    leds[XY(5,i)] = CRGB::Red;
  }
  FastLED.show();
  delay(500);
}
void reset(){
  geschwindigkeit = 200;
  int r = random(0,3);
  if (r == 0){
    px=1;
    py=1;
    angle = 45;
  }
  else if (r == 1){
    px=8;
    py=1;
    angle = 135;
  }
  else if (r == 2){
    px=8;
    py=8;
    angle = 225;
  }
  else{
    px=1;
    py=8;
    angle = 315;
  }
}

void schneller(){
  geschwindigkeit -= speedup;
}
void checkWinner(){
  if(px == 9){
    blueWins();
  }
  if(px == 0){
    redWins();
  }
  
}
boolean checkReady(){
  leseIR();
  leds[XY(9,0)] = CRGB::Yellow;
  leds[XY(0,9)] = CRGB::Yellow;
  FastLED.show();
  if(IRWert[XY(9,0)] > grenzwert and IRWert[XY(0,9)] > grenzwert){
    Serial.println("true");
    return true;
  }else{
    return false;
  }
}
void neustart(){
  blauPunkte = 0;
  rotPunkte = 0;
  fill(CRGB::Green);
  reset();
  while(checkReady() == false){delay(100);}
  readyAnimation();
  Serial.println("neustart");
}
void blueWins(){
  fill(CRGB::Blue);
  FastLED.show();
  delay(500);
  clear();
  blauPunkte ++;
  if(blauPunkte == 5){
    for (int p = 0; p < NUM_LEDS; p++) {
    leds[p] = CRGB::Blue;
    delay(20);
    FastLED.show();
    }
    neustart();
    }else{
      zeigePunkte(); 
      delay(5000);
      reset();
    }
}
void redWins(){
  fill(CRGB::Red);
  FastLED.show();
  delay(500);
  clear();
  rotPunkte ++;
  if(rotPunkte == 5){
    for (int p = 0; p < NUM_LEDS; p++) {
    leds[p] = CRGB::Red;
    delay(20);
    FastLED.show();
  }
  neustart();
  }else{
    zeigePunkte();
    delay(5000);
    reset();
  }
  
  
}

void zeigePunkte(){
  for(int a = 0; a<=4; a++){
    for(int i = 0; i < rotPunkte*2; i++){
      leds[XY(9-i,a)] = CRGB::Red;
    }
  }
  for(int a = 9; a>=5; a--){
    for(int i = 0; i<blauPunkte*2; i++){
      leds[XY(i,a)] = CRGB::Blue;
    }
  }
  FastLED.show();
}

void calcAngleIncrement() {
  
  if (angle == 45)  {
    px += 1;
    py += 1;
  }
  else if (angle == 135)  {
    px -= 1;
    py += 1;
  }
  else if (angle == 180)  {
    px -= 1;
  }
  else if (angle == 225)  {
    px -= 1;
    py -= 1;
  }
  else if (angle == 315)  {
    px += 1;
    py -= 1;
  }
}

void clear(){
  for (int p=0;p< NUM_LEDS;p++){
    leds[p] = CRGB::Black;
  }
}

int checkCollision(){
  if(px ==8 and py ==9 or px ==8 and py ==0 or px ==1 and py ==9 or px ==1 and py ==0){return 5;}
  
  if(px == 8){ 
    return 1;
  }
  else if(py == 9){
    return 2;
  }
  else if(px == 1){
    return 3;
  }
  else if(py == 0){
    return 4;
  }
  else{
    return 0;
  }
}
int checkBracketR(){
  if( IRWert[XY(9,py)] > grenzwert or IRWert[XY(9,py -1)] > grenzwert or IRWert[XY(9,py +1)] > grenzwert){
    return 1;
  }
  else{return 0;}
}
int checkBracketL(){
  if(IRWert[XY(0,py+1)] > grenzwert or IRWert[XY(0,py)] > grenzwert or IRWert[XY(0,py -1)] > grenzwert){
    return 1;
  }
  else{return 0;}
}
void winkelAendern(){
  if      (checkCollision() == 5 and angle == 45){angle = 225;schneller();}
  else if (checkCollision() == 5 and angle == 135){angle = 315;schneller();}
  else if (checkCollision() == 5 and angle == 225){angle = 45;schneller();}
  else if (checkCollision() == 5 and angle == 315){angle = 135;schneller();}
  
  else if (checkCollision() == 1 and checkBracketR() == 1 and angle == 315){angle = 225;schneller();}
  else if (checkCollision() == 4 and angle == 225){angle = 135;}
  else if (checkCollision() == 3 and checkBracketL() == 1 and angle == 135){angle = 45;schneller();}
  else if (checkCollision() == 2 and angle == 45){angle = 315;}

  
  else if(checkCollision() == 1 and checkBracketR() == 1 ){angle += 90;schneller();}
  else if(checkCollision() == 2){angle += 90;}
  else if(checkCollision() == 3 and checkBracketL() == 1 ){angle += 90;schneller();}
  else if(checkCollision() == 4){angle = 45;}
  
  else{}
}

void pong(){
  clear();
  checkWinner();
  maleBrackets();
  calcAngleIncrement();  
  ballMalen(px,py);   
  winkelAendern();
  delay(geschwindigkeit);
  
}

