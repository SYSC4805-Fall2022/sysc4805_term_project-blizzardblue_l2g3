/*
*In this file, we are testing the movement of the wheels before 
*applying any adjustment to the speed of the motors
*/
//definitions for enable signal and direction

#define WDT_KEY (0xA5)
int PWMsigA = 35;
int dirA = 5;
int PWMsigB = 37;
int dirB = 6;

int delay_time= 2000; // how long should each wheel turn?

//watchdog timer with 4 seconds timeout
int watchdogTimer = 1000;

void watchdogSetup(void) 
{
// do what you want here
}

void setup() {
  Serial.begin(9600);

// Enable watchdog.
  WDT->WDT_MR = WDT_MR_WDD(0xFFF)
                | WDT_MR_WDRPROC
                | WDT_MR_WDRSTEN
                | WDT_MR_WDV(256 * 2);
 //configures pins as outputs
  pinMode(PWMsigA, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(PWMsigB, OUTPUT);
  pinMode(dirB, OUTPUT);

//all pins are off at initialization
digitalWrite(PWMsigA, LOW);     
digitalWrite(dirA,LOW);
digitalWrite(PWMsigB, LOW);     
digitalWrite(dirB,LOW);

uint32_t status = (RSTC->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> 8; // Get status from the last Reset
  Serial.print("RSTTYP = 0b"); Serial.println(status, BIN);  // Should be 0b010 after first watchdog reset

}

void loop() {

//Restart watchdog
  WDT->WDT_CR = WDT_CR_KEY(WDT_KEY)
                | WDT_CR_WDRSTT;

  Serial.println("Enter the main loop : Restart watchdog");
  delay(500);

  while (true)
  {
    Serial.println("the software becomes trapped in a deadlock !");
    delay(500);
    /* If the software becomes trapped in a deadlock,
       watchdog triggers a reset and software restarts with stored values
       in General Purpose Back up Registers*/
  }
Serial.println("Hello");
delay(500);

      moveforwardright();
      movereverseright();

      Serial.println("After...");

      delay(1000);
}

void moveforwardright(){
      //moving in right forward
      Serial.println("Right Forward test");
      digitalWrite(PWMsigA, HIGH);
      delay(delay_time);
      digitalWrite(dirA, HIGH);
      delay(delay_time);
      digitalWrite(PWMsigA, LOW);
      delay(delay_time);
}

void movereverseright(){
      //moving in right reverse  
      Serial.println("Right reverse test");
      digitalWrite(PWMsigA, HIGH);
      delay(delay_time);
      digitalWrite(dirA, LOW);
      delay(delay_time);
      digitalWrite(PWMsigA, LOW);
      delay(delay_time);
}

void moveforwardleft(){
      //moving in left forward
      Serial.println("Left Forward test");
      digitalWrite(PWMsigB, HIGH);
      delay(delay_time);
      digitalWrite(dirA, HIGH);
      delay(delay_time);
      digitalWrite(PWMsigB, LOW);
      delay(delay_time);
}

void movereverseleft(){
      //moving in left reverse  
      Serial.println("Left reverse test");
      digitalWrite(PWMsigB, HIGH);
      delay(delay_time);
      digitalWrite(dirA, LOW);
      delay(delay_time);
      digitalWrite(PWMsigB, LOW);
      delay(delay_time);
}

//infinity loop to hang MCU
//while(1){}
