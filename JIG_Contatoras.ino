/////////////////////////////////////////////////////////////////////////////////////
//                        JIG de teste de contatoras e FAN                        //
// Versão 0.1                                                                     //
// Criado em: 20/03/2023                                                          //
// Última edição: 21/03/2023                                                      //
// Propósito: Receber comandos via porta serial para atuar nas saídas ou realizar //
// leituras das portas digitais/analógicas, informando os valores via serial.     //
//                                                                                //
// Gravar em ESP32 WROOM sob placa NodeMCU-32S                                    //
// Autor: Juno Higgeti                                                            //
////////////////////////////////////////////////////////////////////////////////////
String recebido;

float percent = 0;
long a = 0;
int status_ =0;
bool state = 0;
int valor = 0;
// Configuração dos canais PWM
const int resolution = 12;
const int freq = 5000;

const int ledChannel1  = 1;   const int pwmpin1 = 23;		//Canal de saída 1 ligada ao terminal 23
const int ledChannel2 = 2;    const int pwmpin2 = 22;		//Canal de saída 2 ligada ao terminal 22
const int ledChannel3 = 3;    const int pwmpin3 = 21;
const int ledChannel4 = 4;    const int pwmpin4 = 19;
const int ledChannel5 = 5;    const int pwmpin5 = 18;
const int ledChannel6 = 6;    const int pwmpin6 = 5;
const int ledChannel7 = 7;    const int pwmpin7 = 17;
const int ledChannel8 = 8;    const int pwmpin8 = 16;
const int ledChannel9 = 9;    const int pwmpin9 = 4;
const int ledChannel10  = 10;  const int pwmpin10 = 2;
const int ledChannel11  = 11; const int pwmpin11 = 15;

// Canais de entrada
const int input1 = 36;
const int input2 = 39;
const int input3 = 34;
const int input4 = 35;
const int input5 = 32;
const int input6 = 33;
const int input7 = 25;
const int input8 = 26;
const int input9 = 27;
const int input10 = 14;
const int input11 = 12;
const int input12 = 13;




void setup() {
  // Inicializa porta serial à 115200 bits por segundo:
  Serial.begin(115200);
  //Configura as saídas com frequencia e resolução
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);
  ledcSetup(ledChannel5, freq, resolution);
  ledcSetup(ledChannel6, freq, resolution);
  ledcSetup(ledChannel7, freq, resolution);
  ledcSetup(ledChannel8, freq, resolution);
  ledcSetup(ledChannel9, freq, resolution);
  ledcSetup(ledChannel10, freq, resolution);
  ledcSetup(ledChannel11, freq, resolution);
  //Configura cada saída em cada canal
  ledcAttachPin(pwmpin1, ledChannel1);
  ledcAttachPin(pwmpin2, ledChannel2);
  ledcAttachPin(pwmpin3, ledChannel3);
  ledcAttachPin(pwmpin4, ledChannel4);
  ledcAttachPin(pwmpin5, ledChannel5);
  ledcAttachPin(pwmpin6, ledChannel6);
  ledcAttachPin(pwmpin7, ledChannel7);
  ledcAttachPin(pwmpin8, ledChannel8);
  ledcAttachPin(pwmpin9, ledChannel9);  
  ledcAttachPin(pwmpin10, ledChannel10);
  ledcAttachPin(pwmpin11, ledChannel11);
  //Configura a resolução de entrada analógica para 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
 
 
  //ledcWrite(ledChannel1, status_);
 if (Serial.available()>0) { 
  
  recebido = Serial.readStringUntil('\n');
if (recebido.startsWith("BMS;")){
     recebido.remove(0,4);
      //a = recebido.toInt();
                int ind1 = recebido.indexOf(';');
                int ind2 = recebido.indexOf(';', ind1 + 1);
                String part1 = recebido.substring(0, ind1);
                String part2 = recebido.substring(ind1 + 1, ind2);
                float a_float = float(part2.toInt());
                percent = a_float/10000.00;
                if(percent > 1){percent = 1.0;}
                if(percent <0) {percent = 0.0;}
                status_ = (4095 * percent);
                int ledch = part1.toInt();
    //Serial.print("Porcentagem: \t");
                Serial.print("Canal: ");
                Serial.print(ledch);
                Serial.print(" DutyCicle(%): ");
                Serial.println(percent*100);
                ledcWrite(ledch, 4095);
                delay(100);
                ledcWrite(ledch, status_);


     
   }

if (recebido.startsWith("PWM;")){
     recebido.remove(0,4);
      //a = recebido.toInt();
                int ind1 = recebido.indexOf(';');
                int ind2 = recebido.indexOf(';', ind1 + 1);
                String part1 = recebido.substring(0, ind1);
                String part2 = recebido.substring(ind1 + 1, ind2);
                float a_float = float(part2.toInt());
                percent = a_float/10000.00;
                if(percent > 1){percent = 1.0;}
                if(percent <0) {percent = 0.0;}
                status_ = (4095 * percent);
                int ledch = part1.toInt();
    //Serial.print("Porcentagem: \t");
                Serial.print("Canal: ");
                Serial.print(ledch);
                Serial.print(" DutyCicle(%): ");
                Serial.println(percent*100);
                ledcWrite(ledch, status_);


     
   }






   

 if (recebido.startsWith("DOUT;")){
     recebido.remove(0,5);
      //a = recebido.toInt();
                int ind1 = recebido.indexOf(';');
                int ind2 = recebido.indexOf(';', ind1 + 1);
                String part1 = recebido.substring(0, ind1);
                String part2 = recebido.substring(ind1 + 1, ind2);
                if(part2 == "HIGH"){status_ = HIGH;}
                if(part2 == "LOW"){status_ = LOW;}
                //status_ = (4096 * percent);
                int ledch = part1.toInt();
    //Serial.print("Porcentagem: \t");
                Serial.print("Canal: ");
                Serial.print(ledch);
                Serial.print(" Nível: ");
                Serial.println(status_);
                int _status_;
                if(status_){_status_ = 4095;}
                if(!status_){_status_ = 0;}
                ledcWrite(ledch, _status_);
   }
    
if (recebido.startsWith("OFF;")){
      Serial.println(recebido);
          recebido.remove(0,4);
          int ind1 = recebido.indexOf(';');
          int ind2 = recebido.indexOf(';', ind1 + 1);
          String part1 = recebido.substring(0, ind1);
          String part2 = recebido.substring(ind1 + 1, ind2);

          Serial.print(part1);
          Serial.print("\t");
          Serial.println(part2);
          status_ = part2.toInt();
          for (int ledch=0; ledch <16; ledch++){
          ledcWrite(ledch, 0);
          }

    }

if (recebido.startsWith("CORRENTE;")){
      Serial.println(recebido);
          recebido.remove(0,9);
          int ind1 = recebido.indexOf(';');
          int ind2 = recebido.indexOf(';', ind1 + 1);
          int ind3 = recebido.indexOf(';', ind2 + 1);
          String part1 = recebido.substring(0, ind1);
          String part2 = recebido.substring(ind1 + 1, ind2);
          String part3 = recebido.substring(ind2 + 1, ind3);

          Serial.print(part1);
          Serial.print("\t");
          Serial.print(part2);
          Serial.print("\t");
          Serial.println(part3);
          status_ = part3.toInt();
          ledcWrite(ledChannel1, status_);

    }

if (recebido.startsWith("AIN;")){
      Serial.println(recebido);
          recebido.remove(0,4);
          int ind1 = recebido.indexOf(';');
          int ind2 = recebido.indexOf(';', ind1 + 1);
          int ind3 = recebido.indexOf(';', ind2 + 1);
          String part1 = recebido.substring(0, ind1);
          String part2 = recebido.substring(ind1 + 1, ind2);
          String part3 = recebido.substring(ind2 + 1, ind3);

          //Serial.print(part1);
          //Serial.print("\t");
          //Serial.print(part2);
          //Serial.print("\t");
          //Serial.println(part3);
          int pino = 0;
          if(part1== "input1"){pino = 36;}
          if(part1=="input2"){pino = 39;}
          if(part1=="input3"){pino = 34;}
          if(part1=="input4"){pino = 35;}
          if(part1=="input5"){pino = 32;}
          if(part1=="input6"){pino = 33;}
          if(part1=="input7"){pino = 25;}
          if(part1=="input8"){pino = 26;}
          if(part1=="input9"){pino = 27;}
          if(part1=="input10"){pino = 14;}
          if(part1=="input11"){pino = 12;}
          if(part1=="input12"){pino = 13;}
    
          pinMode(pino, INPUT);
          float tensao = (analogRead(pino) * (3.3/4096));
          Serial.println(tensao);

    }

if (recebido.startsWith("DIN;")){
      Serial.println(recebido);
          recebido.remove(0,4);
          int ind1 = recebido.indexOf(';');
          int ind2 = recebido.indexOf(';', ind1 + 1);
          //int ind3 = recebido.indexOf(';', ind2 + 1);
          String part1 = recebido.substring(0, ind1);
          String part2 = recebido.substring(ind1 + 1, ind2);
          //String part3 = recebido.substring(ind2 + 1, ind3);

          //Serial.print(part1);
          //Serial.print("\t");
          //Serial.print(part2);
          //Serial.print("\t");
          //Serial.println(part3);
          int pino = 0;
          if(part1== "input1"){pino = 36;}
          if(part1=="input2"){pino = 39;}
          if(part1=="input3"){pino = 34;}
          if(part1=="input4"){pino = 35;}
          if(part1=="input5"){pino = 32;}
          if(part1=="input6"){pino = 33;}
          if(part1=="input7"){pino = 25;}
          if(part1=="input8"){pino = 26;}
          if(part1=="input9"){pino = 27;}
          if(part1=="input10"){pino = 14;}
          if(part1=="input11"){pino = 12;}
          if(part1=="input12"){pino = 13;}

          
          
          pinMode(pino, INPUT);
          Serial.println(digitalRead(pino));

    }
    
if (recebido.startsWith("HANDSHAKE;")){
      char message_[] = "========================================";
      Serial.println("");
      for(int i=0; i<strlen(message_); i++)
      {
        Serial.print(message_[i]);
        delay(10);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
      char message[] = "        JIG de Teste de contatoras";
      Serial.println("");
      for(int i=0; i<strlen(message); i++)
      {
        Serial.print(message[i]);
        delay(20);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
      Serial.println("");
      char message2[] = "                 Versão: 0.1";
        for(int i=0; i<strlen(message2); i++)
      {
        Serial.print(message2[i]);
        delay(10);
        state = !state;
                if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
       char  message3[] = "                 Sistema OK";
        for(int i=0; i<strlen(message3); i++)
      {
        Serial.print(message3[i]);
        delay(10);
        state = !state;
                if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
         Serial.println("");
         char _message_[] = "========================================";
      for(int i=0; i<strlen(_message_); i++)
      {
        Serial.print(_message_[i]);
        delay(15);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_1[] = "           _____ _______ _______      __"; ///////////////////////
      for(int i=0; i<strlen(_message_1); i++)
      {
        Serial.print(_message_1[i]);
        delay(2);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_2[] = "     /\\   |  __ \\__   __|_   _\\ \\    / /"; ///////////////////////
      for(int i=0; i<strlen(_message_2); i++)
      {
        Serial.print(_message_2[i]);
        delay(2);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_3[] = "    /  \\  | |__) | | |    | |  \\ \\  / / "; ///////////////////////
      for(int i=0; i<strlen(_message_3); i++)
      {
        Serial.print(_message_3[i]);
        delay(2);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_4[] = "   / /\\ \\ |  ___/  | |    | |   \\ \\/ /  "; ///////////////////////
      for(int i=0; i<strlen(_message_4); i++)
      {
        Serial.print(_message_4[i]);
        delay(2);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_5[] = "  / ____ \\| |      | |   _| |_   \\  /   "; ///////////////////////
      for(int i=0; i<strlen(_message_5); i++)
      {
        Serial.print(_message_5[i]);
        delay(2);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
        Serial.println("");
         char _message_6[] = " /_/    \\_\\_|      |_|  |_____|   \\/    "; ///////////////////////
      for(int i=0; i<strlen(_message_6); i++)
      {
        Serial.print(_message_6[i]);
        delay(10);
        state = !state;
        if(state){valor = 4095;}
        if (!state){valor = 1000;}
        //ledcWrite(ledChannel1, valor);
        }
          Serial.println("");
          /*ledcWrite(ledChannel1, 4096);
                    delay(200);
          ledcWrite(ledChannel1, 1000);
                    delay(200);
          ledcWrite(ledChannel1, 4096);
                    delay(200);
          ledcWrite(ledChannel1, 1000);
          delay(200);
          ledcWrite(ledChannel1, 4096);
                    delay(200);
          ledcWrite(ledChannel1, 0);
          */
    }
 }
 //
 }
