const int TIME_PRESSED = 500; // INTERVALO EM QUE O BOTAO FICA PRESSIONADO

int IRF_PIN = 10; // PINO DE ESTADO DO RALAY DO IRF
int RALAY_DOWN = 9; // PINO DO RALAY DO BOTAO DE DECIDA
int RALAY_UP = 8; // PINO DO RALAY DO BOTAO DE SUBIDA
bool C = false;
bool changeA, changeB;
int direcao_down = 0;  // 0 = abre 1 = fecha
int direcao_up = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IRF_PIN, INPUT);
  pinMode(RALAY_DOWN, OUTPUT);
  pinMode(RALAY_UP, OUTPUT);
  
  changeB = digitalRead(IRF_PIN);
  digitalWrite(RALAY_DOWN, HIGH);
  digitalWrite(RALAY_UP, HIGH);
}

void loop() {
  Serial.println(digitalRead(IRF_PIN));
  changeA = digitalRead(IRF_PIN);
  
  if(changeA != changeB){
    C = true;
    Serial.print("Valor de C = ");
    Serial.println(C);
  }

  if(C && direcao_down >= 0){
    digitalWrite(RALAY_DOWN, LOW);
    delay(TIME_PRESSED);
    digitalWrite(RALAY_DOWN, HIGH);
    Serial.print("DESCENDO");
    direcao_down++;
    if(direcao_down == 2) direcao_down = -1;
    
  } else if(C && direcao_up >= 0){
    digitalWrite(RALAY_UP, LOW);
    delay(TIME_PRESSED);
    digitalWrite(RALAY_UP, HIGH);
    Serial.print("SUBINDO");
    direcao_up++;
    if(direcao_up == 2){
      direcao_down = 0;
      direcao_up = 0;
    }
  }
  
  C = false;
  changeB = changeA;
  delay(100);
}

