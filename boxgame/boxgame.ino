#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(6, 8);
//   avoid using pins with LEDs attached

#include "LedControl.h"
#include "binary.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10

 C = Switch at pin 7
 B = DT at pin 8
 A = CLK at pin 6
*/
#define outputA 6
#define outputB 8
#define SW 7

 int counter = 0; 
 int aState;
 int aLastState;
 int btnState;  
 int score = 0;
 int lives = 5;
 long unsigned int enemylifespan = 0;

LedControl lc=LedControl(12,11,10,1);

// delay time between faces
int val;
int rot_output;
int rot_old;
int player_position;
int enemy_row = 2;
int enemy_col = 2;
int enemy_ori = 0;
int difficulty = 3000;
unsigned long lastButtonPress = 0;



byte row[8]= {B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001};
byte ex1[8]= {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001};
byte cross[8]= {B00000000,B00011000,B00011000,B01111110,B01111110,B00011000,B00011000,B00000000};
byte over1[8]= {B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001};
byte cols[2]= {B10000000,B00000001};
byte fullrow[1] = {B11111111};

void setup() {
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0);
    //pinMode (outputA,INPUT);
    //pinMode (outputB,INPUT);
    pinMode(SW, INPUT_PULLUP);
    Serial.begin (9600);
    aLastState = digitalRead(outputA);
    player_position = 0;
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

void    drawPlayer(int player_position) {
    if (player_position < 8)
        lc.setRow(0,0,row[player_position]);
    else if (player_position >= 8 && player_position < 14)
        lc.setRow(0,(player_position - 7),cols[1]);
    else if (player_position >= 14 && player_position < 22)
        lc.setRow(0,7,row[21 - player_position]);
    else
        lc.setRow(0,(31 - player_position),cols[0]);
}

void drawRotary(int rot_output, int btnState){
    if (rot_output > rot_old) {
        if (player_position == 30)
            player_position = 0;
        else
            player_position++;
        Serial.print("Position: ");
        Serial.print(player_position);
        Serial.print(" btnState: ");
        Serial.println(btnState);
    }
    else if (rot_output < rot_old) {
        if (player_position == 0)
            player_position = 30;
        else
            player_position--;
        Serial.print("Position: ");
        Serial.print(player_position);
        Serial.print(" btnState: ");
        Serial.println(btnState);
    }
    lc.clearDisplay(0);
    drawPlayer(player_position);
    drawEnemy();
    rot_old = rot_output;
}

/*
int      readRotary() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter--;
     } else {
       counter++;
     }
     Serial.print("Position: ");
     Serial.println(player_position);
   } 
   delay(1);
   aLastState = aState; // Updates the previous state of the outputA with the current state
   return(counter);
}
*/

int     checkForHit() {
    if (player_position < 8) {
      if (enemy_ori == 0)
        return (0);
      if (player_position == enemy_col)
        return (1);
      Serial.print(player_position);
      Serial.print(" | ");
      Serial.print(enemy_row);
      Serial.print(" | ");
      Serial.print(enemy_col);
      Serial.print(" | ");
      Serial.println(enemy_ori);
    } else if (player_position >= 8 && player_position < 14) {
      if (enemy_ori == 1)
        return (0);
      if (player_position - 7 == enemy_row)
        return (1);
      Serial.print(player_position);
      Serial.print(" | ");
      Serial.print(enemy_row);
      Serial.print(" | ");
      Serial.print(enemy_col);
      Serial.print(" | ");
      Serial.println(enemy_ori);
    } else if (player_position >= 14 && player_position < 22) {
      if (enemy_ori == 0)
        return (0);
      if (21 - player_position == enemy_col)
        return (1);
      Serial.print(player_position);
      Serial.print(" | ");
      Serial.print(enemy_row);
      Serial.print(" | ");
      Serial.print(enemy_col);
      Serial.print(" | ");
      Serial.println(enemy_ori);
    } else {
      if (enemy_ori == 1)
        return (0);
      if (31 - player_position == enemy_row)
        return (1);
      Serial.print(player_position);
      Serial.print(" | ");
      Serial.print(enemy_row);
      Serial.print(" | ");
      Serial.print(enemy_col);
      Serial.print(" | ");
      Serial.println(enemy_ori);
    }
  return (0);
}

int     generateEnemy () {
    enemy_col = random(1,6);
    enemy_row =  random(1,6);
    if (random(0,2) == 0) {
      enemy_ori = 0;
    } else {
      enemy_ori =  1;
    }
    enemylifespan = millis();
    difficulty -= 50;
    return (0);
}

int     drawEnemy() {
    if (enemy_ori == 0) {
        lc.setRow(0,enemy_row,row[enemy_col]);
        lc.setRow(0,enemy_row,row[enemy_col + 1]);
    } else {
        lc.setRow(0,enemy_row,row[enemy_col]);
        lc.setRow(0,enemy_row + 1,row[enemy_col]);
    } 
    return (0);
}

int     gameover() {
    //printByte(over1);
    byte scorebytes[8] = {B00000000};
    lc.clearDisplay(0);
    Serial.println(itoa(score, scorebytes, 2));
    lc.setRow(0,0,scorebytes[0]);
    lc.setRow(0,1,scorebytes[1]);
    lc.setRow(0,2,scorebytes[2]);
    lc.setRow(0,3,scorebytes[3]);
    lc.setRow(0,4,scorebytes[4]);
    lc.setRow(0,5,scorebytes[5]);
    lc.setRow(0,6,scorebytes[6]);
    lc.setRow(0,7,scorebytes[7]);
    delay(4000);
    score = 0;
    lives = 5;
    difficulty = 3000;
}

int     readButton() {
    millis();
    btnState = digitalRead(SW);
    //Serial.print(btnState);
  //If we detect LOW signal, button is pressed
    if (millis() - enemylifespan > difficulty) {
      printByte(ex1);
      delay(300);
      lives--;
      generateEnemy();
      return(btnState);
    }
    if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
        if (millis() - lastButtonPress > 50) {
          if (player_position < 8) {
              lc.setRow(0,0,row[player_position]);
              lc.setRow(0,1,row[player_position]);
              lc.setRow(0,2,row[player_position]);
              lc.setRow(0,3,row[player_position]);
              lc.setRow(0,4,row[player_position]);
              lc.setRow(0,5,row[player_position]);
              lc.setRow(0,6,row[player_position]);
              lc.setRow(0,7,row[player_position]);
          }
          else if (player_position >= 8 && player_position < 14)
              lc.setRow(0,(player_position - 7),fullrow[0]);
          else if (player_position >= 14 && player_position < 22) {
              lc.setRow(0,0,row[21 - player_position]);
              lc.setRow(0,1,row[21 - player_position]);
              lc.setRow(0,2,row[21 - player_position]);
              lc.setRow(0,3,row[21 - player_position]);
              lc.setRow(0,4,row[21 - player_position]);
              lc.setRow(0,5,row[21 - player_position]);
              lc.setRow(0,6,row[21 - player_position]);
              lc.setRow(0,7,row[21 - player_position]);
          }
          else
              lc.setRow(0,(31 - player_position),fullrow[0]);
          Serial.println("FIRE!");
          if (checkForHit() == 0) {
            printByte(ex1);
            lives--;
          }
          else {
            printByte(cross);
            score++;
          }
          delay(300);
          generateEnemy();
        }
        // Remember last button press event
        lastButtonPress = millis();
    }
    // Put in a slight delay to help debounce the reading
    delay(1);
    return (btnState);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }
  rot_output = oldPosition / 4;
  btnState = readButton();
  if (lives < 1) {
    gameover();
  } else {
  //Serial.println(btnState);
    drawRotary(rot_output, btnState);
    drawEnemy();
  }
}