int v=0;
int pulsecount=0;
void pass()
{
  pulsecount++;
}

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
 v=analogRead(A0);
 if (v<500)
 
 Serial.print("V : ");
 Serial.println(v,DEC);
 delay(100);
}