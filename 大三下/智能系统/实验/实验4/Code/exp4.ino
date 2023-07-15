int ns_led_green_pin = 13;
int ns_led_red_pin = 12;
int we_led_green_pin = 8;
int we_led_red_pin = 7;
int detect_pin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(ns_led_green_pin, OUTPUT);
  pinMode(ns_led_red_pin, OUTPUT);
  pinMode(we_led_green_pin, OUTPUT);
  pinMode(we_led_red_pin, OUTPUT);
  pinMode(detect_pin, INPUT);
  Serial.begin(9600);
  digitalWrite(ns_led_green_pin, LOW);
  digitalWrite(ns_led_red_pin, LOW);
  digitalWrite(we_led_green_pin, LOW);
  digitalWrite(we_led_red_pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int detect_result = digitalRead(detect_pin);
  if (detect_result == HIGH)
    Serial.print("1");
  else
    Serial.print("0");

  char read_result = Serial.read();
  if (read_result == '1') // 1表示南北为绿灯，东西为红灯
  {
    digitalWrite(ns_led_green_pin, HIGH);
    digitalWrite(ns_led_red_pin, LOW);
    digitalWrite(we_led_green_pin, LOW);
    digitalWrite(we_led_red_pin, HIGH);
  }
  else
  {
    digitalWrite(ns_led_green_pin, LOW);
    digitalWrite(ns_led_red_pin, HIGH);
    digitalWrite(we_led_green_pin, HIGH);
    digitalWrite(we_led_red_pin, LOW);
  }
}
