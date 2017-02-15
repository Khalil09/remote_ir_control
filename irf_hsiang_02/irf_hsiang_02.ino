int RECV_PIN = 11;
int SENSOR_A = 10;
int SENSOR_B = 9;
int RALAY_1 = 8;
int RALAY_2 = 7;
float armazenavalor;
bool A;
bool B;
bool C = false;
bool changeA, changeB;
bool pass;
bool direcao = 0;  // 0 = abre 1 = fecha
bool ligado = false;  //  FALSE = desligado TRUE = ligado

void setup() {
  Serial.begin(9600);  
  pinMode(RECV_PIN, INPUT);
  pinMode(SENSOR_A, INPUT);
  pinMode(SENSOR_B, INPUT);
  pinMode(RALAY_1, OUTPUT);
  pinMode(RALAY_2, OUTPUT);
  changeB = digitalRead(RECV_PIN);
}

void loop() {
  
  A = digitalRead(SENSOR_A);    // aberto
  B = digitalRead(SENSOR_B);    // fechado
  changeA = digitalRead(RECV_PIN);
  
  if(changeA != changeB){
    C = true;
    Serial.println("Valor de C = " + C);
  }
  if(!A && !B){
    pass = false;
    if(C && ligado)
      set_dir("PARAR");
    else if(C && !ligado)
      set_dir("SEGUIR");
    
  } else {
    if(!pass) set_dir("PARAR");
    else if((A || B) && C) set_dir("SEGUIR");
    pass = true;
    Serial.println(pass);
  }
  C = false;
  changeB = changeA;
  delay(300);
}

void set_dir(String dir){
  if(dir == "PARAR"){
    digitalWrite(RALAY_1, LOW);
    digitalWrite(RALAY_2, LOW);
    ligado = false;
    direcao = !direcao;
  } else if(dir == "SEGUIR"){
    if(direcao){
      digitalWrite(RALAY_1, HIGH);
      digitalWrite(RALAY_2, LOW);
      ligado = true;
      direcao = 1;
    } else {
      digitalWrite(RALAY_1, LOW);
      digitalWrite(RALAY_2, HIGH);
      ligado = true;
      direcao = false;
    }
   }
}

