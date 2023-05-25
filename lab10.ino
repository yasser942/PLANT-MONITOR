#include <dht.h>
#include <LiquidCrystal_I2C.h>
#define DHT11_PIN 7
LiquidCrystal_I2C lcd(0x3f, 16, 2);
dht DHT;
int TEMPERATURE_MIN = 30;
int TEMPERATURE_MAX = 35;
int HUMIDITY_MIN = 30;
int HUMIDITY_MAX = 40;
int LIGHT_MIN = 200;
int LIGHT_MAX = 700;
int temperature = 0;
int humidity = 0;
int light_sensor = 0;
bool warning_flag = false;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  light_sensor = analogRead(A2);
  int data = DHT.read11(DHT11_PIN);
  temperature = DHT.temperature;
  humidity = DHT.humidity;
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Light Level: ");
  Serial.println(light_sensor);
  if (temperature <= TEMPERATURE_MIN)
    print_warning("TEMP", "LOW");
  else if (temperature >= TEMPERATURE_MAX)
    print_warning("TEMP", "HIGH");
  if (humidity <= HUMIDITY_MIN)
    print_warning("HUMI", "LOW");
  else if (humidity >= HUMIDITY_MAX)
    print_warning("HUMI", "HIGH");
  if (light_sensor <= LIGHT_MIN)
    print_warning("LIGH", "LOW");
  else if (light_sensor >= LIGHT_MAX)
    print_warning("LIGH", "HIGH");
  if (!warning_flag) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.setCursor(5, 0);
    lcd.print("H:");
    lcd.print(humidity);
    lcd.setCursor(10, 0);
    lcd.print("L:");
    lcd.print(light_sensor);
    lcd.setCursor(0, 1);
    lcd.print("STATUS:  OPTIMAL");
    delay(2500);
  }
  warning_flag=false;
}
void print_warning(String warning_type, String warning_level) {
  warning_flag = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(warning_type);
  lcd.print(" IS TOO ");
  lcd.print(warning_level);
  lcd.setCursor(0, 1);
  if (warning_type == "TEMP") {
    if (warning_level == "HIGH") {
      lcd.print("TMAX:");
      lcd.print(TEMPERATURE_MAX);
    } else if (warning_level == "LOW") {
      lcd.print("TMIN:");
      lcd.print(TEMPERATURE_MIN);
    }
    lcd.print(" TCUR:");
    lcd.print(temperature);
  } else if (warning_type == "HUMI") {
    if (warning_level == "HIGH") {
      lcd.print("HMAX:");
      lcd.print(HUMIDITY_MAX);
    } else if (warning_level == "LOW") {
      lcd.print("HMIN:");
      lcd.print(HUMIDITY_MIN);
    }
    lcd.print(" HCUR:");
    lcd.print(humidity);
  } else if (warning_type == "LIGH") {
    if (warning_level == "HIGH") {
      lcd.print("LMAX:");
      lcd.print(LIGHT_MAX);
    } else if (warning_level == "LOW") {
      lcd.print("LMIN:");
      lcd.print(LIGHT_MIN);
    }
    lcd.print("LCUR:");
    lcd.print(light_sensor);
  }
  delay(2500);
}
