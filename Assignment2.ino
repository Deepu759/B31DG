#include <B31DGMonitor.h>

#include<Ticker.h>

B31DGCyclicExecutiveMonitor monitor;
int t1_out = 1;
int f1_in = 8;
float f1;
int f1_1;
float f1_read;
unsigned long t1;
unsigned long t2;
int f2_in = 9;
float f2;
int f2_1;
float f2_read;
unsigned long t3;
unsigned long t4;
int potPin = 4;
int ERROR_LED = 19;
float potval;
float cal_val =0;
float a1 = 0;
float a2 = 0;
float a3 = 0;
float a4 = 0;
float ana_avg;
float half_max;
unsigned long frameTime = 0;
unsigned long frameCounter = 0;
Ticker ticker;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Ready");

  pinMode(t1_out, OUTPUT);
  pinMode(f1_in, INPUT);
  pinMode(f2_in, INPUT);
  pinMode(potPin, INPUT);
  pinMode(ERROR_LED, OUTPUT);
  monitor.startMonitoring();
  frame();
  ticker.attach_ms(4, frame);


}

void loop() {
  // put your main code here, to run repeatedly:
  //frame();

}


void frame()
{
  unsigned int slot = frameCounter % 50;

  switch (slot)
  {
    case 0:  task1();            task3();              break;
    case 1:  task1();  task2();                        break;
    case 2:  task1();            task3();              break;
    case 3:  task1();                      task4();    break;
    case 4:  task1();            task3();              break;
    case 5:  task1();  task2();                        break;
    case 6:  task1();            task3();              break;
    case 7:  task1();                                  break;
    case 8:  task1();            task3();              break;
    case 9:  task1();                      task4();    break;
    case 10: task1();            task3();              break;
    case 11: task1();  task2();                        break;
    case 12: task1();            task3();              break;
    case 13: task1();                      task4();    break;
    case 14: task1();            task3();              break;
    case 15: task1();  task2();                        break;
    case 16: task1();            task3();              break;
    case 17: task1();                                  break;
    case 18: task1();            task3();              break;
    case 19: task1();                      task4();    break;
    case 20: task1();            task3();              break;
    case 21: task1();  task2();                        break;
    case 22: task1();            task3();              break;
    case 23: task1();                      task4();  task5();    break;
    case 24: task1();            task3();              break;
    case 25: task1();  task2();                        break;
    case 26: task1();            task3();              break;
    case 27: task1();                                  break;
    case 28: task1();            task3();              break;
    case 29: task1();                      task4();    break;
    case 30: task1();            task3();              break;
    case 31: task1();  task2();                        break;
    case 32: task1();            task3();              break;
    case 33: task1();                      task4();    break;
    case 34: task1();            task3();              break;
    case 35: task1();  task2();                        break;
    case 36: task1();            task3();              break;
    case 37: task1();                                  break;
    case 38: task1();            task3();              break;
    case 39: task1();                      task4();    break;
    case 40: task1();            task3();              break;
    case 41: task1();  task2();                        break;
    case 42: task1();            task3();              break;
    case 43: task1();                      task4();    break;
    case 44: task1();            task3();              break;
    case 45: task1();  task2();                        break;
    case 46: task1();            task3();              break;
    case 47: task1();                                  break;
    case 48: task1();            task3();              break;
    case 49: task1();                      task4();  task5();   ;  break;
  }
  frameCounter++;

}


void task1()
{
  monitor.jobStarted(1);
  digitalWrite(t1_out, HIGH);
  delayMicroseconds(200);
  digitalWrite(t1_out, LOW);
  delayMicroseconds(50);
  digitalWrite(t1_out, HIGH);
  delayMicroseconds(30);  
  digitalWrite(t1_out, LOW);
  monitor.jobEnded(1);
}


void task2()
{
  monitor.jobStarted(2);
  //f1_read = pulseIn(f1_in, HIGH);
  //f1 = 1000000 / (f1_read);
  while (digitalRead(f1_in) == LOW);
  t1 = micros();
  while (digitalRead(f1_in) == HIGH);
  t2 = micros();
  f1_read = (t2 - t1)*0.000001;
  f1 = 1/(f1_read*2);
  //delay(3);
  monitor.jobEnded(2);
}

void task3()
{
  monitor.jobStarted(3);
  //f2_read = pulseIn(f2_in, HIGH);
  //f2 = 1000000 / (f2_read);
  while (digitalRead(f2_in) == LOW);
  t3 = micros();
  while (digitalRead(f2_in) == HIGH);
  t4 = micros();
  f2_read = (t4 - t3)*0.000001;
  f2 = 1/(f2_read*2);
  //delay(2);
  monitor.jobEnded(3);
}


void task4()
{
  monitor.jobStarted(4);
  potval = analogRead(potPin);
  cal_val = (3.3*potval)/4095;
  a1 = a2;
  a2 = a3;
  a3 = a4;
  a4 = cal_val;
  ana_avg = (a1 + a2 + a3 + a4)/4;
  half_max = 3.3/2;
  if (ana_avg > half_max)  {digitalWrite(ERROR_LED, HIGH);}
  else {digitalWrite(ERROR_LED, LOW);}
  monitor.jobEnded(4);
}


void task5()
{
  monitor.jobStarted(5);
  f1_1 = 0;
  f2_1 = 0;
  f1_1 = ((f1 - 333)*99)/(1000 - 333);
  f2_1 = ((f2 - 500)*99)/(1000 - 500);

  if(f1_1<=0){f1_1 = 0;}
  else if(f1_1 > 99){f1_1 = 99;}
  else{f1_1 = f1_1;}

  if(f2_1<=0){f2_1 = 0;}
  else if(f2_1 > 99){f2_1 = 99;}
  else{f2_1 = f2_1;}
  Serial.printf("%d, %d\n",f1_1, f2_1);
  monitor.jobEnded(5);
}


