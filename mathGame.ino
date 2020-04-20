#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

int a ;
int b ;
int answer ;
int answers[] = {0,0,0};

int buttonState[] = {0,0,0};

int ButtonPin1 = 10;
int ButtonPin2 = 11;
int ButtonPin3 = 12;

int level = 20;

bool gotAnswer = false; 
bool showQuestion = true; 

void setup(){ 
  lcd.begin(16, 2);                  // Задаем размерность экрана

  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки
  lcd.print("****************");       // Выводим текст
  lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
  lcd.print("-Math challenge-");         // Выводим текст

  pinMode(ButtonPin1, INPUT);
  pinMode(ButtonPin2, INPUT);
  pinMode(ButtonPin3, INPUT);


// init first question
  randomSeed(analogRead(0));
  a = random(level);
  b = random(level);

  answer = random(2);
  for (int i = 0; i < 3; i++) {
    answers[i]=random(a+b);
    if (i==answer){
      answers[i] = a+b;  
    }
  }

  delay(1000);
}

void loop(){

  if (gotAnswer == true) {
    gotAnswer = false;
    
    a = random(level);
    b = random(level);

    answer = random(2);
    for (int i = 0; i < 3; i++) {
      answers[i]=random(a+b);
      if (i==answer){
        answers[i] = a+b;  
      }
    }
  }
  
  if (showQuestion == true) {
    lcd.begin(16, 2);                  // Задаем размерность экрана

    displayText(String(a)+"+"+String(b)+"=?", 0);
    displayText("1)"+String(answers[0])+" 2)"+String(answers[1])+" 3)"+String(answers[2]), 1);

    showQuestion = false;
  }

  buttonState[0] = digitalRead(ButtonPin1);
  buttonState[1] = digitalRead(ButtonPin2);
  buttonState[2] = digitalRead(ButtonPin3);

  for (int i = 0; i < 3; i++) {    
    if (buttonState[i] == HIGH and answer == i) {
      lcd.begin(16, 2);                  // Задаем размерность экрана

      displayText(String(a)+"+"+String(b)+"="+String(answers[i]), 0);
      displayText("CORRECT! ^_^", 1);

      showQuestion = true;
      gotAnswer = true;
      delay(5000); 
    } 

    if (buttonState[i] == HIGH and answer != i) {
      lcd.begin(16, 2);                  // Задаем размерность экрана
  
      displayText(">_<", 0);
      displayText("WRONG!", 1);

      showQuestion = true;
      gotAnswer = false;
      delay(1000);     
    }
  }    
}

int displayText(String text, int line) {
  lcd.setCursor(0, line);             
  lcd.print("                ");       // Выводим текст
  lcd.setCursor(0, line);              // Устанавливаем курсор в начало 1 строки
  lcd.print(text);       // Выводим текст

  return 1;
}
