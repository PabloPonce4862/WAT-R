#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11  
DHT dht (DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4);

int motor1a = 2;
int motor1b = 9;
int motor2a = 10;
int motor2b = 4;
int rampa = 12;
char estado = 's';


void setup() {
  Serial.flush();
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(rampa, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  delay(2000);
  Serial.println("Sensor DHT11");

  dht.begin();
  lcd.setCursor(0,0);
  lcd.print("Sensor DHT11");
}

void loop() {

  float h = dht.readHumidity();    //Lee la humedad
  float t = dht.readTemperature(); //Lee la temperatura

  //Revisa que los datos obtenidos sean validos, si no lo son(no un numero) algo sale mal!

  if (isnan (t) || isnan (h)) {
    lcd.setCursor(0,0);
    lcd.print("Falla de lectura del DHT");
  }else {
    lcd.setCursor(0,0);
    lcd.print("Humedad: ");
    lcd.print(h);
    lcd.print(" %");
    lcd.setCursor(0,1);
    lcd.print("Temperatura: ");
    lcd.print(t);
    lcd.print(" °C");
  }

  if(Serial.available()>0){
    estado = Serial.read();
  }
  if(estado=='a'){
    digitalWrite(motor1a, HIGH);
    digitalWrite(motor1b, LOW);
    digitalWrite(motor2a, HIGH);
    digitalWrite(motor2b, LOW);
  }
  if(estado=='b'){
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, HIGH);
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, HIGH);
  }
  if(estado=='c'){
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, HIGH);
    digitalWrite(motor2a, HIGH);
    digitalWrite(motor2b, LOW);
  }
  if(estado=='d'){
    digitalWrite(motor1a, HIGH);
    digitalWrite(motor1b, LOW);
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, HIGH);
  }
  if(estado=='e'){
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, LOW);
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, LOW);
  }
  if(estado=='f'){
    digitalWrite(rampa, HIGH);
  }
}
