#include <Wire.h>
#include <stdlib.h>       // calloc
#include <stdarg.h>       // va_*
#include <string.h>       // strlen, strcpy

#define SLAVE_ADDRESS 0x04
#define RELAY1 9

char number[1024];
char letter;
int count = 0;
int x;
char wrd[32];

void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}

void loop() {
    delay(100);
}

void receiveData(int byteCount){
    while(Wire.available()) {
       letter = (char) Wire.read();      
       if(letter == '\n')
       {
          Serial.print("data received: ");
          for(x = 0; x <= count; x++)
          {
            Serial.print(number[x]);
            wrd[x] = number[x];
          }
          Serial.println("");
          memset(number, 0, sizeof(number));
          count = 0;
       }else{
         number[count] = letter;
         count++;
       }
    }
}

// callback for sending data
void sendData(){
    //Serial.print("data sent: ");
    //for(x = 0; x <= sizeof(wrd); x++)
    //{
      //Serial.println((int)wrd[x]);
    //}
    //Serial.println("");
    wrd[sizeof(wrd) + 1] = '\n';
    Wire.write(wrd);
    //Wire.write("TESTE");
    memset(wrd, 0, sizeof(wrd));
}
