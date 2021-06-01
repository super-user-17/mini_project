#include<LiquidCrystal.h>
#include<Wire.h>

#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ir1 = 8;
int ir2 = 9;
int pump = 7;
int ctr_1 = 0, ctr_2 = 0;
int buzzer = 6, bolt1 = 10, bolt2 = 13;

boolean state_1 = true, state_2 = true ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(bolt1, OUTPUT);
  pinMode(bolt2, OUTPUT);
  digitalWrite(bolt1, LOW);
  digitalWrite(bolt2, LOW);
  digitalWrite(pump, LOW);
  lcd.begin(16, 2);
  mlx.begin();

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("COVID FIGHTER");
  lcd.setCursor(2, 2);
  lcd.print("By- KAUSHAL");

}

void loop() {
  // put your main code here, to run repeatedly:

  while (mlx.readObjectTempF() > 100)
  {
    digitalWrite(bolt2, HIGH);
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("HIGH TEMP");
    lcd.setCursor(5, 2);
    lcd.print(mlx.readObjectTempF());
    lcd.print(" F");
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }

  if (ctr_2 > ctr_1) {
    digitalWrite(bolt1, HIGH);

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("SANITIZE");
    lcd.setCursor(4, 2);
    lcd.print("YOURSELF");

    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }

  if ((digitalRead(ir1) && state_1))
  {
    ctr_1++;
    state_1 = false;
    digitalWrite(pump, HIGH);
    delay(400);
    digitalWrite(pump, LOW);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("GO TO");
    lcd.setCursor(4, 9);
    lcd.print("Entry 2");
    delay(1000);
    Serial.print("Count_1: ");
    Serial.println(ctr_1);
    //delay(100);
  }


  if (!digitalRead(ir1)) {
    state_1 = true;
    delay(100);
    digitalWrite(pump, LOW);
  }

  if ((digitalRead(ir2) && state_2))
  {
    ctr_2++;

    lcd.clear();
    if (ctr_2 > 3)
    {
      lcd.setCursor(3, 0);
      lcd.print("NO  ENTRY");
      lcd.setCursor(1, 2);
      lcd.print("LIMIT REACHED");
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
    }
    else
    {
      lcd.setCursor(3, 0);
      lcd.print("BODY TEMP");
      lcd.setCursor(4, 2);
      float temp = mlx.readObjectTempF();
      delay(500);
      lcd.print(temp);
      lcd.print(" F");
      state_2 = false;
      //digitalWrite(5,HIGH);
      //delay(1000);
      //Serial.print("Count_2: ");
      //
      //Serial.println(ctr_2);
      //delay(100);
    }
  }


  if (!digitalRead(ir2)) {
    state_2 = true;
    delay(100);
    //digitalWrite(5,LOW);
  }

}
