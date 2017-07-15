//#/////////  JOTA: mira los niveles en el pin 2 y ajus te del generador de señal.
//#void setup(){
//#  pinMode(3, INPUT_PULLUP);
//#  pinMode(13, OUTPUT);
//#  Serial.begin(115200);   
//#}
//#
//#void loop(){
//#while(digitalRead(3)==1){
//#  Serial.println("1");
//#  digitalWrite(13, HIGH);
//#}

//#while(digitalRead(3)==0){
//#  Serial.println(".");
//#  digitalWrite(13, LOW);
//#}
//#delay(50);
//#}

long ms=0;

void setup(){
   Serial.begin(115200);
    pinMode(3, INPUT); 
    delay(2000);
}
void loop(){
    while(digitalRead(3)==0);
    while(digitalRead(3)==1);
    long ms= millis();
    while(digitalRead(3)==0); 
    long m=millis();
    long quinientos=m-ms; 
    Serial.println(quinientos);
}
