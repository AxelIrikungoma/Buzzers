/*
 * Quiz Buzzer project, inspired from the trivia game "Génies en Herbe" in Burundi.
 * A game (or match) is constituted of two teams, each composed of 4 players.
 * One player can answer a question for the team. When the question is not answered
 * correctly, the other members of the team are blocked from trying to answer the same
 * question.
 */


#include <CD74HC4067.h>
#include <ezButton.h>
#include <millisDelay.h>

               // s0 s1 s2 s3
CD74HC4067 my_mux(2, 3, 4, 5);  // creating a new CD74HC4067 object with its four control pins
const int common_pin = 6; // select a pin to share with the 16 channels of the CD74HC4067

ezButton correct(8); // button which, when pressed, indicates the given answer is correct or a new
                    // question is about to be asked (all the teams have the opportunity to respond)
                        
ezButton incorrect(9); // button which, when pressed, indicates the given answer is incorrect

millisDelay timer; // creating an object which will make the use of the millis
                  // function easier (the millis function helps set up a timer)
                  
ezButton time_button(11); // button which, when pressed, activates a countdown

const int buzzer = 10; // variable for producing sound

bool team1_turn(true);
bool team2_turn(true);

void setup(){
   pinMode(buzzer, OUTPUT);
}

void loop(){
  
  pinMode(common_pin, INPUT);

  if (team1_turn == 1){
  for (int i=0; i< 4; i++){
    answer_process(i, team1_turn, team2_turn);
   } 
  }
   
  if (team2_turn == 1){
  for (int i=4; i< 8; i++){
    answer_process(i, team2_turn, team1_turn);
  }
 }

  correct.loop();
  if ((!team1_turn and !team2_turn) || correct.isPressed() == HIGH){  //all teams can respond
  team1_turn = true;
  team2_turn = true;
 }
}

  void answer_process(int i, bool& team1_turn, bool& team2_turn){
    my_mux.channel(i+8);
    if (digitalRead(common_pin) == HIGH){ // if a player presses the button
       pinMode(common_pin, OUTPUT);
       digitalWrite(common_pin, HIGH);
       my_mux.channel(i);
       tone(buzzer, 700);
       delay(500);
       noTone(buzzer);
       while (digitalRead(common_pin) == HIGH){ // while the LED is still on
          correct.loop();
          if (correct.isPressed()){ // all teams can respond now
            digitalWrite(common_pin, LOW);
            team1_turn = true;
            team2_turn = true;
            timer.finish();
          }
           incorrect.loop();
           if (incorrect.isPressed()){
            digitalWrite(common_pin, LOW);
            team1_turn = false;  // only the other team can respond
            timer.finish();
          }
          time_button.loop();
          if (time_button.isPressed()){
             timer.start(5000);
          }
          if (timer.justFinished()){
            digitalWrite(common_pin, LOW);
            team1_turn = false;
          }
       }
     }
   } 
     
