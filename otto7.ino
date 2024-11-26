#include <Otto.h>
Otto Otto;
#include <Servo.h>
Servo AL, AR;
#include <SoftwareSerial.h>

#include <PlayRtttl.hpp>


char command = '0';
int adj[]={ 0, 0,};
int pos[]={ 90,90};
int shift = 60;
int shift_inc = 10;
int shift_delay = 50;

const char data[] = "VARIABLE#";
unsigned long int matrix;

#define LeftLeg 2 // left leg pin, servo[0]
#define RightLeg 3 // right leg pin, servo[1]
#define LeftFoot 4 // left foot pin, servo[2]
#define RightFoot 5 // right foot pin, servo[3]
#define Buzzer 13 //buzzer pin

#define PIN_AL 6 // left arm
#define PIN_AR 7 // right arm
void move_servo(){ AL.write(pos[1]+adj[1]); AR.write(pos[2]+adj[2]);}
#define CLK A1 // Clock pin
#define CS A2  // Chip Select pin
#define DIN A3 // Data In pin
#define Orientation 0// 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4
SoftwareSerial mySerial(11,12);

long ultrasound_distance_simple() {
   long duration, distance;
   digitalWrite(8,LOW);
   delayMicroseconds(2);
   digitalWrite(8, HIGH);
   delayMicroseconds(10);
   digitalWrite(8, LOW);
   duration = pulseIn(9, HIGH);
   distance = duration/58;
   return distance;
}


void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
Otto.home();

  AL.attach(PIN_AR);
AR.attach(PIN_AL);
move_servo();
delay(100);
  Otto.initMATRIX( DIN, CS, CLK, Orientation);
  mySerial.begin(9600);

  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
    Otto.home();
  AL.write(90);
  AR.write(90);
  delay(shift_delay);Otto.matrixIntensity(7);//the brightness of the LED matrix use values from 0 to 15 only
  Otto.writeText ( "I AM OTTO",80); // limited to CAPITAL LETTERS NUMBERS : ; < >  = @, MAX.9 characters

}

void loop() {
  if (ultrasound_distance_simple() < 15) {
    Otto.sing(S_OhOoh2);
    Otto.putMouth(smallSurprise);
    Otto.walk(1,1000,-1); // BACKWARD
  } else {
    Otto.home();
    AL.write(90);
    AR.write(90);
    delay(shift_delay);}
  if (mySerial.available()) {
    command = (mySerial.read());
  }
  switch (command) {
  case 'A':
    Otto.walk(1,1000,1); // FORWARD
    Otto.sing(S_superHappy);
    delay(100);
    command = '0';
    break;
   case 'B':
    Otto.walk(1,1000,-1); // BACKWARD
    Otto.sing(S_superHappy);
    delay(100);
    command = '0';
    break;
   case 'C':
    Otto.turn(1,1000,1); // LEFT
    Otto.sing(S_superHappy);
    delay(100);
    command = '0';
    break;
   case 'D':
    Otto.turn(1,1000,-1); // RIGHT
    Otto.sing(S_superHappy);
    delay(100);
    command = '0';
    break;
   case 'E':
    Otto.bend(1,1000,1);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'F':
    Otto.bend(1,1000,-1);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'G':
    Otto.shakeLeg(1,1000,-1);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'H':
    Otto.shakeLeg(1,1000,1);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'I':
    Otto.jump(1,1000);
    Otto.sing(S_confused);
    delay(100);
    command = '0';
    break;
   case 'J':
    AL.write(160);
    AR.write(20);
    delay(shift_delay);Otto.sing(S_mode1);
    delay(100);
    command = '0';
    break;
   case 'K':
    AL.write(20);
    AR.write(160);
    delay(shift_delay);Otto.sing(S_mode2);
    delay(100);
    command = '0';
    break;
   case 'L':
    for(int angle=90; angle<90+shift; angle+=shift_inc){  pos[1] = angle;    move_servo();  delay(shift_delay);}
    for(int angle=90+shift; angle>90-shift; angle-=shift_inc) { pos[1] = angle;  move_servo(); delay(shift_delay); }
    for(int angle=90-shift; angle<90; angle+=shift_inc) {pos[1] = angle;  move_servo();   delay(shift_delay); }
    Otto.sing(S_mode3);
    delay(100);
    command = '0';
    break;
   case 'M':
    for(int angle=90; angle<90+shift; angle+=shift_inc){  pos[2] = angle;    move_servo();  delay(shift_delay);}
    for(int angle=90+shift; angle>90-shift; angle-=shift_inc) { pos[2] = angle;  move_servo(); delay(shift_delay); }
    for(int angle=90-shift; angle<90; angle+=shift_inc) {pos[2] = angle;  move_servo();   delay(shift_delay); }
    Otto.sing(S_fart1);
    delay(100);
    command = '0';
    break;
   case 'N':
    Otto.moonwalker(1, 1000, 25, 1);
    Otto.sing(S_fart2);
    delay(100);
    command = '0';
    break;
   case 'O':
    Otto.moonwalker(1, 1000, 25, -1);
    Otto.sing(S_fart3);
    delay(100);
    command = '0';
    break;
   case 'P':
    Otto.crusaito(1, 1000, 25, 1);
    Otto.sing(S_OhOoh2);
    delay(100);
    command = '0';
    break;
   case 'Q':
    Otto.crusaito(1, 1000, 25, -1);
    Otto.sing(S_surprise);
    delay(100);
    command = '0';
    break;
   case 'R':
    Otto.flapping(1, 1000, 25, 1);
    Otto.sing(S_cuddly);
    delay(100);
    command = '0';
    break;
   case 'S':
    Otto.flapping(1, 1000, 25, -1);
    Otto.sing(S_OhOoh2);
    delay(100);
    command = '0';
    break;
   case 'T':
    Otto.swing(1, 1000, 25);
    Otto.sing(S_happy);
    delay(100);
    command = '0';
    break;
   case 'U':
    Otto.updown(1, 1000, 25);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'V':
    Otto.tiptoeSwing(1, 1000, 25);
    Otto.sing(S_OhOoh);
    delay(100);
    command = '0';
    break;
   case 'W':
    Otto.jitter(1, 1000, 25);
    Otto.sing(S_sad);
    delay(100);
    command = '0';
    break;
   case 'X':
    Otto.ascendingTurn(1, 1000, 25);
    Otto.sing(S_confused);
    delay(100);
    command = '0';
    break;
   case 'Y':
    Otto.playGesture(OttoSuperHappy);
    delay(100);
    command = '0';
    break;
   case 'Z':
    Otto.playGesture(OttoHappy);
    delay(100);
    command = '0';
    break;
   case 'a':
    Otto.playGesture(OttoSad);
    delay(100);
    command = '0';
    break;
   case 'b':
    Otto.playGesture(OttoSleeping);
    delay(100);
    command = '0';
    break;
   case 'c':
    Otto.playGesture(OttoConfused);
    delay(100);
    command = '0';
    break;
   case 'd':
    Otto.playGesture(OttoFretful);
    delay(100);
    command = '0';
    break;
   case 'e':
    Otto.playGesture(OttoLove);
    delay(100);
    command = '0';
    break;
   case 'f':
    Otto.playGesture(OttoAngry);
    delay(100);
    command = '0';
    break;
   case 'g':
    Otto.playGesture(OttoMagic);
    delay(100);
    command = '0';
    break;
   case 'h':
    Otto.playGesture(OttoWave);
    delay(100);
    command = '0';
    break;
   case 'i':
    Otto.playGesture(OttoVictory);
    delay(100);
    command = '0';
    break;
   case 'j':
    Otto.playGesture(OttoFail);
    delay(100);
    command = '0';
    break;
   case 'k':
    Otto.playGesture(OttoFart);
    delay(100);
    command = '0';
    break;
   case 'l':
    Otto.putMouth(happyOpen);
    Otto.sing(S_superHappy);
    delay(100);
    command = '0';
    break;
   case 'm':
    Otto.putMouth(happyClosed);
    Otto.sing(S_happy);
    delay(100);
    command = '0';
    break;
   case 'n':
    Otto.putMouth(smile);
    Otto.sing(S_happy_short);
    delay(100);
    command = '0';
    break;
   case 'o':
    Otto.putMouth(23);
    Otto.sing(S_sad);
    delay(100);
    command = '0';
    break;
   case 'p':
    Otto.putMouth(24);
    Otto.sing(S_sad);
    delay(100);
    command = '0';
    break;
   case 'q':
    Otto.putMouth(smallSurprise);
    Otto.sing(S_surprise);
    delay(100);
    command = '0';
    break;
   case 'r':
    Otto.putMouth(bigSurprise);
    Otto.sing(S_surprise);
    delay(100);
    command = '0';
    break;
   case 's':
    Otto.putMouth(confused);
    Otto.sing(S_confused);
    delay(100);
    command = '0';
    break;
   case 't':
    Otto.putMouth(tongueOut);
    Otto.sing(S_buttonPushed);
    delay(100);
    command = '0';
    break;
   case 'u':
    Otto.putMouth(culito);
    Otto.sing(S_OhOoh);
    delay(100);
    command = '0';
    break;
   case 'v':
    Otto.putMouth(lineMouth);
    Otto.sing(S_disconnection);
    delay(100);
    command = '0';
    break;
   case 'w':
    Otto.putMouth(xMouth);
    Otto.sing(S_surprise);
    delay(100);
    command = '0';
    break;
   case 'x':
    Otto.putMouth(okMouth);
    Otto.sing(S_OhOoh);
    delay(100);
    command = '0';
    break;
   case 'y':
    Otto.putMouth(heart);
    Otto.sing(S_cuddly);
    delay(100);
    command = '0';
    break;
   case 'z':
    Otto.putMouth(27);
    Otto.sing(S_surprise);
    delay(100);
    command = '0';
    break;
   case '1':
     Otto.setLed(0,0,0); Otto.setLed(0,1,1); Otto.setLed(0,2,1); Otto.setLed(0,3,1); Otto.setLed(0,4,1); Otto.setLed(0,5,1); Otto.setLed(0,6,0); Otto.setLed(0,7,0); Otto.setLed(1,0,0); Otto.setLed(1,1,0); Otto.setLed(1,2,0); Otto.setLed(1,3,1); Otto.setLed(1,4,0); Otto.setLed(1,5,0); Otto.setLed(1,6,0); Otto.setLed(1,7,0); Otto.setLed(2,0,0); Otto.setLed(2,1,1); Otto.setLed(2,2,1); Otto.setLed(2,3,1); Otto.setLed(2,4,1); Otto.setLed(2,5,1); Otto.setLed(2,6,0); Otto.setLed(2,7,0); Otto.setLed(3,0,0); Otto.setLed(3,1,0); Otto.setLed(3,2,0); Otto.setLed(3,3,0); Otto.setLed(3,4,0); Otto.setLed(3,5,0); Otto.setLed(3,6,0); Otto.setLed(3,7,0); Otto.setLed(4,0,0); Otto.setLed(4,1,1); Otto.setLed(4,2,0); Otto.setLed(4,3,0); Otto.setLed(4,4,0); Otto.setLed(4,5,1); Otto.setLed(4,6,0); Otto.setLed(4,7,0); Otto.setLed(5,0,0); Otto.setLed(5,1,1); Otto.setLed(5,2,1); Otto.setLed(5,3,1); Otto.setLed(5,4,1); Otto.setLed(5,5,1); Otto.setLed(5,6,0); Otto.setLed(5,7,0); Otto.setLed(6,0,0); Otto.setLed(6,1,1); Otto.setLed(6,2,0); Otto.setLed(6,3,0); Otto.setLed(6,4,0); Otto.setLed(6,5,1); Otto.setLed(6,6,0); Otto.setLed(6,7,0); Otto.setLed(7,0,0); Otto.setLed(7,1,0); Otto.setLed(7,2,0); Otto.setLed(7,3,0); Otto.setLed(7,4,0); Otto.setLed(7,5,0); Otto.setLed(7,6,0); Otto.setLed(7,7,0);Otto.sing(S_mode1);
    delay(100);
    command = '0';
    break;
   case '2':
    Otto.writeText ( "I LOVE YOU",80); // limited to CAPITAL LETTERS NUMBERS : ; < >  = @, MAX.9 characters
    Otto.sing(S_cuddly);
    delay(100);
    command = '0';
    break;
   case '3':
    playRtttlBlockingPGM(13,(char*)WeWishYou);
    delay(100);
    command = '0';
    break;
   case '4':
    playRtttlBlockingPGM(13,(char*)StarWars);
    Otto.putMouth(heart);
    delay(100);
    command = '0';
    break;
   case '5':
    playRtttlBlockingPGM(13,(char*)_20thCenFox);
    Otto.putMouth(okMouth);
    delay(100);
    command = '0';
    break;
   case '6':
    playRtttlBlockingPGM(13,(char*)Bond);
    Otto.putMouth(tongueOut);
    delay(100);
    command = '0';
    break;
   case '7':
    playRtttlBlockingPGM(13,(char*)AllIWant);
    Otto.putMouth(culito);
    delay(100);
    command = '0';
    break;
   case '8':
    playRtttlBlockingPGM(13,(char*)PinkPanther);
    Otto.putMouth(lineMouth);
    delay(100);
    command = '0';
    break;
   case '9':
    playRtttlBlockingPGM(13,(char*)TakeOnMe);
    Otto.putMouth(heart);
    delay(100);
    command = '0';
    break;
   case '0':
    Otto.home();
    AL.write(90);
    AR.write(90);
    delay(shift_delay);Otto.clearMouth();
    break;
   default :
    Otto.home();
    AL.write(90);
    AR.write(90);
    delay(shift_delay);Otto.clearMouth();
   }

}