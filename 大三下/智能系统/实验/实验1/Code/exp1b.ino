int led_pin = 13;
int detect_pin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  pinMode(detect_pin, INPUT);
  Serial.begin(9600);
  digitalWrite(led_pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int detect_result = digitalRead(detect_pin);
  if (detect_result == HIGH)
    Serial.print("1");
  else
    Serial.print("0");

  char read_result = Serial.read();
  if (read_result == '1')
    digitalWrite(led_pin, HIGH);
  else
    digitalWrite(led_pin, LOW);
}
