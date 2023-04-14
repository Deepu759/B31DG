// Define ARDUINO_RUNNING_CORE based on whether FreeRTOS is running on a single core or dual core processor
#if defined(CONFIG_FREERTOS_UNICORE)
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>     // Include the Semaphore header file
#include <freertos/task.h>

SemaphoreHandle_t sem;       // Define a Semaphore handle

int out1 = 3;          // Initialize variable for output pin of task 1
int freq1 = 17;        // Initialize input pin for function 1 of task 1
float k1;              // Declare variable for storing the result of function 1 of task 1
int k1_1;              // Declare variable for storing the first derivative of function 1 of task 1
float f1_read;         // Declare variable for storing the value read from analog input for function 1 of task 1
unsigned long d1;      // Declare variables for storing time values for task 1
unsigned long d2;      // Declare variables for storing time values for task 1
int f2_in = 8;         // Initialize input pin for function 2 of task 2
float k2;              // Declare variable for storing the result of function 2 of task 2
int freq2_1;           // Declare variable for storing the first derivative of function 2 of task 2
float f2_read;         // Declare variable for storing the value read from analog input for function 2 of task 2
unsigned long out3;      // Declare variables for storing time values for task 2
unsigned long out4;      // Declare variables for storing time values for task 2
int potPin = 6;          // Initialize input pin for potentiometer
int ERROR_LED = 4;       // Initialize pin for error LED
float potval;          // Declare variable for storing the value read from potentiometer
float cal_val =0;      // measure the voltage from 0v to 3.3v

// Define structure for storing analog data
typedef struct {
  float x1;             // value from potentiometer
  float x2;             // value from potentiometer
  float x3;
  float x4;             // frequent value from potentiometer
} AnalogData;
AnalogData analogData;
float ana_avg;         // Initialize variable for storing average of analog data
float half_max;        // Initialize variable for storing half of maximum value of analog data
bool ledState = LOW;     // Initialize state of LED
QueueHandle_t q1, q2;     // Declare two queues for communication between tasks
int BUTTON_PIN = 18;        // Initialize input pin for button
int LED_PIN = 3;            //LED connected to pin 3 for the purpose of debouncing LED
bool buttonState;           // Initialize variables for storing button state
bool lastButtonState;       // Initialize variables for storing button state
uint8_t event;
bool ledOn = false;        // Initialize state of LED


void task1(void *pvParameters) {
  while(1)
  {
    digitalWrite(out1, HIGH);
    delayMicroseconds(200);
    digitalWrite(out1, LOW);
    delayMicroseconds(50);
    digitalWrite(out1, HIGH);
    delayMicroseconds(30);  
    digitalWrite(out1, LOW);
    vTaskDelay(pdMS_TO_TICKS(4)); // Use pdMS_TO_TICKS macro to convert the delay time to ticks
  }  
}

void task2(void *pvParameters) {
  while(1)
  {
    if(xSemaphoreTake(sem, portMAX_DELAY) == pdTRUE) { // Use xSemaphoreTake function to acquire the Semaphore
      while (digitalRead(f1_in) == LOW);
      d1 = micros();
      while (digitalRead(f1_in) == HIGH);
      d2 = micros();
      f1_read = (t2 - t1)*0.000001; 
      k1 = 1/(f1_read*2);

      xSemaphoreGive(sem); // Use xSemaphoreGive function to release the Semaphore
    }
    vTaskDelay(pdMS_TO_TICKS(20)); // Use pdMS_TO_TICKS macro to convert the delay time to ticks
  }  
}

void task3(void *pvParameters) {
  while(1)
  {
    if(xSemaphoreTake(sem, portMAX_DELAY) == pdTRUE) { // Use xSemaphoreTake function to acquire the Semaphore
      while (digitalRead(freq2) == LOW);
      d3 = micros();
      while (digitalRead(freq2) == HIGH);
      d4 = micros();
      f2_read = (t4 - t3)*0.000001;
      k2 = 1/(f2_read*2);

      xSemaphoreGive(sem); // Use xSemaphoreGive function to release the Semaphore
    }
    vTaskDelay(pdMS_TO_TICKS(8)); // Use pdMS_TO_TICKS macro to convert the delay time to ticks
  } 
}
void task4(void *pvParameters) {  //task 4 involves reading analogue data from a potentiometer and using that data to calculate how much an LED should light.
  half_max = 3.3 / 2;
  analogData.a1 = 0;
  analogData.a2 = 0;
  analogData.a3 = 0;
  analogData.a4 = 0;
  
  while(1) {
    potval = analogRead(potPin);
    cal_val = (3.3 * potval) / 4095;
    xSemaphoreTake(sem, portMAX_DELAY);
    analogData.a1 = analogData.a2;
    analogData.a2 = analogData.a3;
    analogData.a3 = analogData.a4;
    analogData.a4 = cal_val;
    xSemaphoreGive(sem);

    float ana_avg;
    xSemaphoreTake(sem, portMAX_DELAY);
    ana_avg = (analogData.a1 + analogData.a2 + analogData.a3 + analogData.a4) / 4;
    xSemaphoreGive(sem);

    if (ana_avg > half_max) {
      digitalWrite(ERROR_LED, HIGH);
    } else {
      digitalWrite(ERROR_LED, LOW);
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void task5(void *pvParameters)  // After scaling the frequency values obtained in tasks 2 and 3, we display them in task 5
{
  f1_1 = 0, f2_1 = 0;  
    while(1)
    {     
      f1_1 = ((f1 - 333)*99)/(1000 - 333);
      f2_1 = ((f2 - 500)*99)/(1000 - 500);

      if(f1_1<=0){f1_1 = 0;}
      else if(f1_1 > 99){f1_1 = 99;}
      else{f1_1 = f1_1;}

      if(f2_1<=0){f2_1 = 0;}
      else if(f2_1 > 99){f2_1 = 99;}
      else{f2_1 = f2_1;}

      Serial.printf("%d, %d\n",f1_1, f2_1);
      vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void task6(void* parameter) { // Tasks 6 and 7 are to blink an LED connected to a push button using debouncing
  bool lastButtonState = false;
  while (1) {
    bool buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
      delay(5);
      buttonState = digitalRead(BUTTON_PIN);
    }
    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        uint8_t event = 1;
        xQueueSend(q1, &event, portMAX_DELAY);
      }
    }
    vTaskDelay(pdMS_TO_TICKS(20)); 
  }
}

void task7(void* parameter) {
  uint8_t event;
  while (1) {
    if (xQueueReceive(q1, &event, portMAX_DELAY) == pdPASS) {
      // Toggle the LED state
      ledOn = !ledOn;
      digitalWrite(LED_PIN, ledOn);
    }
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(f1_in, INPUT);
  pinMode(f2_in, INPUT);
  pinMode(t1_out, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  xTaskCreatePinnedToCore(task1, "Task 1", 2048, NULL, 1, NULL, 0);
xTaskCreatePinnedToCore(task2, "Task 2", 2048, NULL, 4, NULL, 1);
xTaskCreatePinnedToCore(task3, "Task 3", 2048, NULL, 4, NULL, 1);
xTaskCreatePinnedToCore(task4, "Task 4", 2048, NULL, 3, NULL, 0);
xTaskCreatePinnedToCore(task5, "Task 5", 2048, NULL, 1, NULL, 1);
xTaskCreatePinnedToCore(task6, "Task 6", 2048, NULL, 2, NULL, 0);
xTaskCreatePinnedToCore(task7, "Task 7", 2048, NULL, 2, NULL, 0);

  sem = xSemaphoreCreateMutex();

  q1 = xQueueCreate(10, sizeof(float));
  q2 = xQueueCreate(10, sizeof(float));
}

void loop() 
{

