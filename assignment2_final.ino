#include <B31DGMonitor.h>   //Library is taken from canvas


#include<Ticker.h>          //IAutomatically run the frames

B31DGCyclicExecutiveMonitor monitor;     //Is taken from monitor
int D1_Ld = 1;                           // For task1, an LED is attached to pin 1
int D1_F = 7;                            // Taken into pin7 for task2 is frequency
float f1;                                
int Md1;
float f1_Rd;
int D3_F = 8;
float f2;
int M2;
float f2_Rd;
int potPin = 4;
int ERROR_LED = 17;
float potval;
float R_pot =0;
float x = 0;                             // For Task4, this variable used for average
float x1 = 0;                           // For Task4, this variable used for average
float x2 = 0;                             // For Task4, this variable used for average
float x3 = 0;                            // For Task4, this variable used for average
float xna_avg;
float half_max;
unsigned long frameTime = 0;     
unsigned long frameCounter = 0;     // From one frame to the next, the framecounter changes
Ticker ticker;                              //object for ticker



void setup() {
  Serial.begin(9600);              // baud rate= 9600 for serial monitor
  while(!Serial);
  Serial.println("Ready");

  pinMode(D1_Ld, OUTPUT);            //attach D1_led - output
  pinMode(D2_F, INPUT);              //attach D2_F - input
  pinMode(D3_F, INPUT);              //attach D3_F - input
  pinMode(potPin, INPUT);            //attach potpin to analog pin
  monitor.startMonitoring();
  frame();
  ticker.attach_ms(4, frame);


}

void loop() {
}


void frame() //The schedule is written as code and will be checked in this frame   function
{
  unsigned int slot = frameCounter % 50; //%50 is utilised, there are 50 frames and slot variable is used to switch cases.

  switch (slot)
  {
    case 0:  task1();            task3();              break;
    case 1:  task1();  task2();             task4():   break;
    case 2:  task1();            task3();              break;
    case 3:  task1();                                  break;
    case 4:  task1();                                  break;
    case 5:  task1();            task3();              break;
    case 6:  task1();  task2();             task4();   break;
    case 7:  task1();            task3();              break;
    case 8:  task1();            task3();              break;
    case 9:  task1();                                  break;
    case 10: task1();            task3();              break;
    case 11: task1();  task2();              task4();  break;
    case 12: task1();            task3();              break;
    case 13: task1();                                  break;
    case 14: task1();                                  break;
    case 15: task1();            task3();              break;
    case 16: task1();                        task4();  break;
    case 17: task1();            task3();              break;
    case 18: task1();            task3();              break;
    case 19: task1();                                  break;
    case 20: task1();            task3();              break;
    case 21: task1();  task2();              task4();  break;
    case 22: task1();            task3();              break;
    case 23: task1();                                  break;
    case 24: task1();                                 task5(); break;
    case 25: task1();            task3();              break;
    case 26: task1();                        task4();  break;
    case 27: task1();            task3();              break;
    case 28: task1();            task3();              break;
    case 29: task1();                                  break;
    case 30: task1();            task3();              break;
    case 31: task1();  task2();              task4();  break;
    case 32: task1();            task3();              break;
    case 33: task1();                                  break;
    case 34: task1();                                  break;
    case 35: task1();            task3();              break;
    case 36: task1();                                  break;
    case 37: task1();            task3();              break;
    case 38: task1();            task3();              break;
    case 39: task1();                                  break;
    case 40: task1();            task3();              break;
    case 41: task1();  task2();             task4();   break;
    case 42: task1();            task3();              break;
    case 43: task1();                                  break;
    case 44: task1();                                  break;
    case 45: task1();            task3();              break;
    case 46: task1();                        task4();  break;
    case 47: task1();            task3();              break;
    case 48: task1();            task3();              break;
    case 49: task1();                      task4();  task5();    break;
  }
  frameCounter++;

}


void task1()                 //0.4ms taken to task1 to get high signal for 200
{
  monitor.jobStarted(1);
  digitalWrite(D1_Ld, HIGH);
  delayMicroseconds(200);
  digitalWrite(D1_F, LOW);
  delayMicroseconds(50);
  digitalWrite(D1_F, HIGH);
  delayMicroseconds(30);  
  digitalWrite(D1_F, LOW);
  monitor.jobFinished(1);
}


void task2()                //3ms taken to task2  to understand square wave
{                           // calculate the frequency of the signal from 333Hz to 1000hz
  monitor.jobStarted(2);
  while (digitalRead(f1_in) == HIGH);
  t2 = micros();
  f1_Rd = (t2 - t1)*0.000001;
  f1 = 1/(f1_read*2);
  monitor.jobFinished(2);
}

void task3()    // 2ms taken to task 3 and frequency signal range blw froim 500hz to 1000hz
{
  monitor.jobStarted(3);
  while (digitalRead(f2_in) == HIGH);
  f2_read = (t4 - t3)*0.000001;
  monitor.jobFinished(3);
}


void task4()       // 0.2mstaken to task4 to calculate the potentiometer voltages 
{
  monitor.jobStarted(4);
  pot_M = analogRead(potPin);     // to read the R_pott
  R_pot = (3.3*potval)/4095;   
  x = x1;
  x1 = x2;
  x2 = x3;
  x3 = cal_val;
  ana_avg = (a + a1 + a2 + a3)/4;                      //average
  half_max = 3.3/2;
  if (ana_avg > half_max)  {digitalWrite(ERROR_LED, HIGH);}
  else {digitalWrite(ERROR_LED, LOW);}
  monitor.jobFinished(4);
}


void task5()     //0.3ms taken to tassk5 to show the values of task2&3
{
  monitor.jobStarted(5);
  M1 = 0;
  M2 = 0;
  M3 = ((f1 - 333)*99)/(1000 - 333);       //frequencies blw 0 - 99
  M4 = ((f2 - 500)*99)/(1000 - 500);

  if(f1_1<=0){f1_1 = 0;}
  else if(f1_1 > 99){f1_1 = 99;}
  else{f1_1 = f1_1;}

  if(f2_1<=0){f2_1 = 0;}
  else if(f2_1 > 99){f2_1 = 99;}
  else{f2_1 = f2_1;}
  Serial.printf("%d, %d\n",f1_1, f2_1);
  monitor.jobFinished(5);
}
