#include <Bounce2.h>
//We always have to include the library
#include "LedControlMS.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define NBR_MTX 2 
#define LEFT_PIN 11
#define RIGHT_PIN 12
LedControl lc=LedControl(8,10,9, NBR_MTX);

String digits= "1234567890";
char string1[] = "1234567890";
int digitCounter=0;
/* we always wait a bit between updates of the display */
unsigned long delaytime=300;

// Instantiate a Bounce object
Bounce leftBounce = Bounce(); 
Bounce rightBounce = Bounce(); 

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  Serial.begin (9600);
  Serial.println("Setup");
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  leftBounce.attach(LEFT_PIN);
  rightBounce.attach(RIGHT_PIN);
  leftBounce.interval(1); // interval in ms
  rightBounce.interval(1); // interval in ms
  
  digitCounter=0;
  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
  /* Set the brightness to a medium values */
    lc.setIntensity(i,8);
  /* and clear the display */
    lc.clearDisplay(i);
  }
  /*
  Serial.println("LED0: 0 0");
  lc.setLed(0,0,0,true);
  delay(1000);
  Serial.println("LED0: 0 7");
  lc.setLed(0,0,7,true);
  delay(1000);
  Serial.println("LED0: 7 0");
  lc.setLed(0,7,0,true);
  delay(1000);
  Serial.println("LED0: 7 7");  
  lc.setLed(0,7,7,true);
  delay(1000);
  Serial.println("LED0: 0 0 off");
  lc.setLed(0,0,0,false);
  delay(1000);
  Serial.println("LED0: 0 7 off");
  lc.setLed(0,0,7,false);
  delay(1000);
  Serial.println("LED0: 7 0 off");
  lc.setLed(0,7,0,false);
  delay(1000);
  Serial.println("LED0: 7 7 off");  
  lc.setLed(0,7,7,false);
  delay(1000);  
  //clearAll();
  
  lc.setRow(0,1,0x0C);
  delay(1000);
  lc.clearDisplay(0);
  lc.setRow(0,1,0xC0);
  delay(1000);
  lc.clearDisplay(0);

  lc.setColumn(0,1,0x0C);
  delay(1000);
  lc.clearDisplay(0);
  lc.setColumn(0,1,0xC0);
  delay(1000);
  lc.clearDisplay(0);
  
  lc.writeString(0,"Hola Mundo");
  delay(1000);
  lc.clearAll();
  scrollLeft('O');
  delay(1000);
  lc.clearAll();
  scrollRight('O');
  delay(1000);
  lc.clearAll();
*/
}


void loop() { 
  //char ch= digits[digitCounter];
  //digitCounter++;
  //if (digitCounter>9) digitCounter=0;
  //lc.displayChar(0, lc.getCharArrayPosition(ch));
  //delay(1000);
  //lc.clearAll();
  
  leftBounce.update();
  rightBounce.update();
  
  int leftValue = leftBounce.read();
  int rightValue = rightBounce.read();
  
  if(leftValue == LOW)
  {
    printLeftString("< ");
  }
  
  if(rightValue == LOW)
  {
    printRightString(" >");
  }
  
  if(leftValue == rightValue)
  {
    lc.displayChar(0, lc.getCharArrayPosition('^'));
    delay(150);
    lc.clearDisplay(0);
    delay(150);
  }
  

  //scrollLeft('z');
  //scrollRight('z');
}

void printLeftString(char* s){
  while (*s != 0){
    scrollLeft(*s);
    s++;
  }
}

void printRightString(char* s){
  while (*s != 0){
    scrollRight(*s);
    s++;
  }
}

void scrollLeft(char ch){
  int pos =lc.getCharArrayPosition(ch);
  for (int scroll =-3; scroll<3; scroll++) {
     for (int i=scroll; i<5;i++) {
        lc.setRow(0,i-scroll, alphabetBitmap[pos][i]);
    } 
    delay(65);
    lc.clearDisplay(0);
  }
}

void scrollRight(char ch){
  int pos =lc.getCharArrayPosition(ch);
  for (int scroll =0; scroll<8; scroll++) {
     for (int i=0; i<6;i++) {
        if (scroll+i<8) lc.setRow(0, scroll+i, alphabetBitmap[pos][i]);
    } 
    delay(55);
    lc.clearDisplay(0);
  }
}
