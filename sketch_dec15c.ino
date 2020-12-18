int LED1 = 2;
int swich1 = 3;
int LED2 = 4;
int swich2 = 5;
int go_on = 6;  //a switch for the animator to press when the answer is correct or when he/she wants to ask a new question
int incorrect = 7; // a switch for the animator to press when the answer is incorrect

int player1 = 1;  // player1 belongs to the first team
int player2 = 1;  // player2 belongs to the second team

unsigned long timer_start = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(swich1,INPUT);
  pinMode(swich2, INPUT);
  pinMode(go_on, INPUT);
  pinMode(incorrect, INPUT);

}

void loop() {
  if (player1 == 1){
    if (digitalRead(swich1) == HIGH){
      digitalWrite(LED1, HIGH);
      timer_start = millis();
      while (digitalRead(LED1) == HIGH){
        if (digitalRead(incorrect) == HIGH || (millis()- timer_start) > 5000UL){
          digitalWrite(LED1, LOW);
          player1 = 0;
        }
        if (digitalRead(go_on) == HIGH){
          digitalWrite(LED1, LOW);
          player1 = 1;
          player2 = 1;
     }
    }
   }
  }
  if (player2 == 1){
    if (digitalRead(swich2) == HIGH){
      digitalWrite(LED2, HIGH);
      timer_start = millis();
      while (digitalRead(LED2) == HIGH){ 
        if (digitalRead(incorrect) == HIGH || (millis()- timer_start) > 5000UL){
          digitalWrite(LED2, LOW);
          player2 = 0; //
        }
          if (digitalRead(go_on) == HIGH){
          digitalWrite(LED2, LOW);
          player2 = 1;
          player1 = 1;
        }
      } 
    }
  }
  //code to allow the above two conditionals to restart
 if ((player1 == 0 and player2 == 0) || digitalRead(go_on) == HIGH){
  player1 = 1;
  player2 = 1;
   }
  }
