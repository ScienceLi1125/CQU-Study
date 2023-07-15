int led_pin = 13;
int detect_pin = 3;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(detect_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int detect_result = digitalRead(detect_pin);
  if (detect_result == HIGH)
    digitalWrite(led_pin, HIGH);
  else
    digitalWrite(led_pin, LOW);
}
