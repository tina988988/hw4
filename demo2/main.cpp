#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
char record[13];
int coun = 0;
Thread t;
int x1, x2;

void go();

void go() {
    while(1) {
        //printf("hello");
        if (record[0] == '+') {
            x1 = (int(record[1]) - 48) * 100 + (int(record[2]) - 48) * 10 + ((int(record[3])) - 48); 
            x2 = (int(record[4]) - 48) * 100 + (int(record[5]) - 48) * 10 + ((int(record[6])) - 48);
            //printf("%d, %d\n", x1, x2); 
        }
        int d = x1 - x2;
        if (d < 0) {
            //turn left
            //1 0.4
            //2 0.35
            car.turn(20, 0.43-0.05*d);
        }
        else if (d > 0) {
        
            car.turn(20, -(0.5-0.05*(-d)));
        }
        else {
            car.goStraight(20);
        }
        if (record[0] == 'N') car.stop();
        //printf("%d, %d\n", x1, x2); 
    }
}

int main(){
   uart.set_baud(9600);
   t.start(go);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            //pc.write(recv, sizeof(recv));
            if(coun < 12) {
                record[coun] = recv[0];
                //printf("%c", record[coun]);
                coun++;
            }
            else if (coun == 12) {
                record[coun] = recv[0];
                //printf("%c", record[coun]);
                coun = 0;
            }
      }
   }
}