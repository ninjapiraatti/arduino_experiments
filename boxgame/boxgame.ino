/*
 Created by Rui Santos
 
 All the resources for this project:
 http://randomnerdtutorials.com/
*/

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
#define outputC 7

 int counter = 0; 
 int aState;
 int aLastState;  

LedControl lc=LedControl(12,11,10,1);

// delay time between faces
unsigned long delaytime=1000;
int val;
int rot_output;
int rot_old;
int player_position;



byte row[8]= {B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001};
byte cols[2]= {B10000000,B00000001};

void setup() {
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0);
    pinMode (outputA,INPUT);
    pinMode (outputB,INPUT);
    Serial.begin (9600);
    aLastState = digitalRead(outputA);
    player_position = 0;
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

void drawRotary(int rot_output){
    if (rot_output > rot_old) {
        if (player_position == 30)
            player_position = 0;
        else
            player_position++;
    }
    else if (rot_output < rot_old)
        if (player_position == 0)
            player_position = 30;
        else
            player_position--;
    lc.clearDisplay(0);
    drawPlayer(player_position);
    rot_old = rot_output;
}

int      readRotary() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(player_position);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
   return(counter);
}

void loop(){
  val = analogRead(12);
     Serial.println(val);
   rot_output = readRotary();
  drawRotary(rot_output);
}