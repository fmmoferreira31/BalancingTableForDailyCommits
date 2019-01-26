int turnOn = 0;
bool isOn = false;
int redOn = 0;
bool isRedOn = false;
int blueOn = 0;
bool isBlueOn = false;
int yellowOn = 0;
bool isYellowOn = false;
int greenOn = 0;
bool isGreenOn = false;
int feedRed = 7;
int feedBlue = 2;
int feedGreen = 6;
unsigned long redTime = 0;
unsigned long blueTime = 0;
unsigned long greenTime = 0;
unsigned long yellowTime = 0;
unsigned long totalTime = 0;
//20 segundos
const unsigned long minMinute = 200;
//40 segundos
const unsigned long maxMinute = 400;
//30 segundos
const unsigned long onTime = 300;
//2 minutos
const unsigned long minTime = 1200;
//2.6 minutos
const unsigned long maxTime = 1600;
const int buttonDelay = 250;
const int timeDelay = 100;
const int feedbackDelay = 3000;

void setup() {
// onButton + white led
pinMode(14, OUTPUT);
pinMode(9, INPUT);
digitalWrite(14, LOW);
// redButton + Red led
pinMode(18, OUTPUT);
pinMode(19, INPUT);
digitalWrite(18, LOW);
// blueButton + Blue led
pinMode(13, OUTPUT);
pinMode(12, INPUT);
digitalWrite(13, LOW);
// yellowButton + yellow led
pinMode(8, OUTPUT);
pinMode(15, INPUT);
digitalWrite(8, LOW);
// greenButton + green led
pinMode(10, OUTPUT);
pinMode(11, INPUT);
digitalWrite(10, LOW);
//BalancerLeds
pinMode(feedRed, OUTPUT);
pinMode(feedBlue, OUTPUT);
pinMode(feedGreen, OUTPUT);

}

void loop() {
turnOn = digitalRead(9);
redOn = digitalRead(19);
blueOn = digitalRead(12);
yellowOn = digitalRead(15);
greenOn = digitalRead(11);
//Liga e Desliga o Aparelho.
if (turnOn == HIGH) {
  delay(250);
  if(isOn){
    isOn = false;
  }else
    isOn = true;
}

//Controlador
if(isOn){
  stopTimer();
  digitalWrite(14, HIGH);
  checkRed();
  checkBlue();
  checkYellow();
  checkGreen();                              
} else {
  turnOff();
}
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(feedRed, red);
  analogWrite(feedGreen, green);
  analogWrite(feedBlue, blue);  
}


void turnOff() {
  digitalWrite(14, LOW);
  isRedOn = false;
  digitalWrite(18, LOW);
  isBlueOn = false;
  digitalWrite(13, LOW);
  isYellowOn = false;
  digitalWrite(8, LOW);
  isGreenOn = false;
  digitalWrite(10, LOW);
  stopTimer();
  feedback();
}

void checkRed(){
if(isRedOn){
  digitalWrite(18, HIGH);
  redElapsedTime();
}else{
  digitalWrite(18, LOW);
}
if(redOn == HIGH){
  delay(buttonDelay);
  if(isRedOn){
    isRedOn = false;
  }else {
    clearRed();
    isRedOn = true;
  }
}
}

void clearRed(){
  isBlueOn = false;
  digitalWrite(13, LOW);
  isYellowOn = false;
  digitalWrite(8, LOW);
  isGreenOn = false;
  digitalWrite(10, LOW);
}

void checkBlue() {
  if(isBlueOn){
  digitalWrite(13, HIGH);
  blueElapsedTime();
}else{
  digitalWrite(13, LOW);
}
if(blueOn == HIGH){
  delay(buttonDelay);
  if(isBlueOn){
    isBlueOn = false;
  }else {
    clearBlue();
    isBlueOn = true;
  }
}
}

void clearBlue() {
  isRedOn = false;
  digitalWrite(18, LOW);
  isYellowOn = false;
  digitalWrite(8, LOW);
  isGreenOn = false;
  digitalWrite(10, LOW);
}

void checkYellow() {
  if(isYellowOn){
  digitalWrite(8, HIGH);
  yellowElapsedTime();
}else{
  digitalWrite(8, LOW);
}
if(yellowOn == HIGH){
  delay(buttonDelay);
  if(isYellowOn){
    isYellowOn = false;
  }else {
    clearYellow();
    isYellowOn = true;
  }
}
}

void clearYellow() {
  isRedOn = false;
  digitalWrite(18, LOW);
  isBlueOn = false;
  digitalWrite(13, LOW);
  isGreenOn = false;
  digitalWrite(10, LOW);
}

void checkGreen() {
  if(isGreenOn){
  digitalWrite(10, HIGH);
  greenElapsedTime();
}else{
  digitalWrite(10, LOW);
}
if(greenOn == HIGH){
  delay(buttonDelay);
  if(isGreenOn){
    isGreenOn = false;
  }else {
    clearGreen();
    isGreenOn = true;
  }
}
}

void clearGreen() {
  isRedOn = false;
  digitalWrite(18, LOW);
  isBlueOn = false;
  digitalWrite(13, LOW);
  isYellowOn = false;
  digitalWrite(8, LOW);
}

void redElapsedTime(){
  delay(timeDelay);
  redTime = redTime + 1;
  if(redTime <= minMinute){
    setColor(255, 255, 0);
  }else if(redTime > minMinute && redTime <= maxMinute){
    setColor(0, 255, 0);
  }else{
    setColor(255, 0, 0);
  }
}

void blueElapsedTime(){
  delay(timeDelay);
  blueTime = blueTime + 1;
  if(blueTime <= minMinute){
    setColor(255, 255, 0);
  }else if(blueTime > minMinute && blueTime <= maxMinute){
    setColor(0, 255, 0);
  }else{
    setColor(255, 0, 0);
  }
}

void greenElapsedTime(){
  delay(timeDelay);
  greenTime = greenTime + 1;
  if(greenTime <= minMinute){
    setColor(255, 255, 0);
  }else if(greenTime > minMinute && greenTime <= maxMinute){
    setColor(0, 255, 0);
  }else if(greenTime > maxMinute){
    setColor(255, 0, 0);
  }
}

void yellowElapsedTime(){
  delay(timeDelay);
  yellowTime = yellowTime + 1;
  if(yellowTime <= minMinute){
    setColor(255, 255, 0);
  }else if(yellowTime > minMinute && yellowTime <= maxMinute){
    setColor(0, 255, 0);
  }else{
    setColor(255, 0, 0);
  }
}


void stopTimer(){
  if(!isRedOn && !isBlueOn && !isGreenOn && !isYellowOn){
      setColor(0, 0, 0);
  }
}

void feedback(){
  totalTime = redTime + blueTime + greenTime + yellowTime;
  if( redTime != 0){
    if( redTime > onTime && redTime < maxMinute ){
      digitalWrite(18, HIGH);
      setColor(0, 255, 0);
      delay(feedbackDelay);
      digitalWrite(18, LOW);
      setColor(0, 0, 0);
      redTime = 0;
    }else {
      digitalWrite(18, HIGH);
      setColor(255, 0, 0);
      delay(feedbackDelay);
      digitalWrite(18, LOW);
      setColor(0, 0, 0);
      redTime = 0;
    }
  }
  if( blueTime != 0){
    if( blueTime > onTime && blueTime < maxMinute ){
      digitalWrite(13, HIGH);
      setColor(0, 255, 0);
      delay(feedbackDelay);
      digitalWrite(13, LOW);
      setColor(0, 0, 0);
      blueTime = 0;
    }else {
      digitalWrite(13, HIGH);
      setColor(255, 0, 0);
      delay(feedbackDelay);
      digitalWrite(13, LOW);
      setColor(0, 0, 0);
      blueTime = 0;
    }
  }
  if( yellowTime != 0){
    if( yellowTime > onTime  && yellowTime < maxMinute){
      digitalWrite(8, HIGH);
      setColor(0, 255, 0);
      delay(feedbackDelay);
      digitalWrite(8, LOW);
      setColor(0, 0, 0);
      yellowTime = 0;
    }else {
      digitalWrite(8, HIGH);
      setColor(255, 0, 0);
      delay(feedbackDelay);
      digitalWrite(8, LOW);
      setColor(0, 0, 0);
      yellowTime = 0;
    }
  }
  if( greenTime != 0){
    if( greenTime > onTime && greenTime < maxMinute ){
      digitalWrite(10, HIGH);
      setColor(0, 255, 0);
      delay(feedbackDelay);
      digitalWrite(10, LOW);
      setColor(0, 0, 0);
      greenTime = 0;
    }else {
      digitalWrite(10, HIGH);
      setColor(255, 0, 0);
      delay(feedbackDelay);
      digitalWrite(10, LOW);
      setColor(0, 0, 0);
      greenTime = 0;
    }
  }
  if( totalTime != 0){
    if( totalTime > minTime && totalTime < maxTime ){
      digitalWrite(14, HIGH);
      setColor(0, 255, 0);
      delay(feedbackDelay);
      digitalWrite(14, LOW);
      setColor(0, 0, 0);
      totalTime = 0;
    }else {
      digitalWrite(14, HIGH);
      setColor(255, 0, 0);
      delay(feedbackDelay);
      digitalWrite(14, LOW);
      setColor(0, 0, 0);
      totalTime = 0;
    }
  }
}
