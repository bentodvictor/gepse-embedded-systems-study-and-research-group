 int ledPin = 13;        // pino do led 
 int intencidade = 0;    // variavel que recebe a intencidade de brilho do LED
 int var = 0; 

 void setup()
 { 
    pinMode(ledPin, OUTPUT);     // configura pino 13 como saída
    Serial.begin(9600);          // inicializa a porta serial
    Serial.println("Digete um numero de 0 a 1000 para controlar o brilho do LED: ");
 }

 void loop()
 {
    char aux [] = {' ', ' ', ' ', ' '};     //recebe até 4 bytes (1000)
    if (Serial.available() > 0) {           // informa se tem bits para serem lidos na porta serial
        Serial.readBytes(aux, 4);           // Lê os 4 caracteres 
    }
   
    intencidade = atoi(aux);        // Coverte char pra int
   
    if (intencidade >= 0 && intencidade <= 1000){   // ve se numero digitado esta entre 0 e 1000
        var = map(intencidade, 0, 1000, 0, 255);    // faz o mapeamento entre as escalas
        analogWrite(ledPin, var);                   // aciona led com o valor lido  
        delay(2500);
    }else{
    }
    
    intencidade = 0;   // reset no valor da intencidade
 }