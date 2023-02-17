//Defining the pins for buttons and LEDs

int BP1 = 26; // pin 4 assigned to switch 1
int BP2 = 27; // pin 6 assigned to switch 2
int LED1 = 33;//  pin 1 will be as signal A or LED 1
int LED2 = 35;// pin 3 will be as signal B or LED 2
int E1 = 0;// declaring a variable to read from switch 1 initially set as LOW
int E2 = 0;// declaring a variable to read from switch 2 initially set as LOW

// calculating parameters for first 5 letters of my surname 'BHAVA'
int a = 200;// First letter 'a'& width of 1st pulse
int r = 400;// This the max value after generating C pulses used in mode for generating waveform
int b = 800;// parameter 'b' calculated as second letter*100 = 1*100 = 100
int c = 5; // Number of pulses in the block
int d = 2500;// Spaces btw the pulse blocks
// mode is calculated as rem(fifth letter/4) + 1 = rem(1/4) + 1 = 2. Hence we use mode 2

void setup() {
  // put your setup code here, to run once:
  pinMode(BP1, INPUT); // BP1 is an input component
  pinMode(BP2, INPUT); // BP2 is an input component
  pinMode(LED1, OUTPUT);// LED1 emits light used as output signal to study waveforms
  pinMode(LED2, OUTPUT);// LED2 to set as output component 
  Serial.begin(9600);

}

// Loop to check the inputs and perform operations 
void loop() {
  // put your main code here, to run repeatedly:
  E1 = digitalRead(sw1); // Collect the E1 to know if its at LOW or High state
  E2 = digitalRead(sw2); // summon the E2 of the second button
  
  if(E1 == HIGH)         // using if else to 
  {
    digitalWrite(LED1, LOW);  // This part of the code creates the blank signal
    digitalWrite(LED2, LOW);

  }

  else{

    if(E2 == LOW)  // This is part of the code used to generate the pulses
    {
      digitalWrite(LED1, HIGH);
      delay(50);
      digitalWrite(LED2, LOW);

      for(int i =0;i<c;i++)  // For loop is used to generate required no.of pulses
      {
        digitalWrite(LED1, HIGH);
        delay(a);
        digitalWrite(LED1, LOW);
        delay(b);
        a = a+50;
      }
      digitalWrite(LED1, LOW);
      delay(d);  // After each cyle we give a delay of 'd' before next cyle starts
    }

    else  // This part of the code runs if switch2 is pressed
    {
      digitalWrite(LED2, HIGH);  //After each cyle we give a delay of 'd' before next cyle starts
      delay(50);
      digitalWrite(LED2, LOW);

      for(int i =0; i<c;i++){   // this for loop used to generate required no.of pulses in the inverted form

        digitalWrite(LED1, HIGH);
        delay(r);
        digitalWrite(LED1, LOW);
        delay(b);
        r = r-50;
      }

      digitalWrite(LED1, LOW);
      delay(d);


    }

  }

}
