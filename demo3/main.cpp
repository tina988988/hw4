#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Thread t;
char record[18];
int coun = 0;
float tx, tz, ry;
int save = 5;
int i = 0;
float tx1, tz1, ry1;
int ok = 0;
int t1;

//void turn();

/*void turn() {
    printf("hello");
    if(tz1 < 0) tz1 = -tz1;
    t1 = 1000*abs(tz1);/// 3);
    //float tt = t1;
    if (ry1 - 180 >= 0 && ok == 0) {
        car.turn(20, 0.5-((360-ry1)/10)*0.2);
        ThisThread::sleep_for(4000ms); 
        car.stop();
        ThisThread::sleep_for(1000ms);
        ok++;
        }    
    else if(ry1 - 180 < 0 && ok == 0) {
        //t1 = 1000 * (tz1 * 2 / 3 / );
        //if(tz1 < 0) tz1 = -tz1;
        //t1 = tz1;
          //  printf("time %f", t1);
        car.goStraight(20);
        ThisThread::sleep_for(t1);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.turn(20, -(0.5-((ry1)/10)*0.2));
        ThisThread::sleep_for(2800ms);
        car.stop();
        ThisThread::sleep_for(1000ms);
            //car.turn(20, -(0.5-((ry1)/10)*0.2));
            //ThisThread::sleep_for(2800ms);
            //car.stop();
            //hisThread::sleep_for(1000ms);
        //car.goStraight(20);
        //ThisThread::sleep_for(tt);
        car.stop();
        ThisThread::sleep_for(1000ms);
        ok++;
    }
}
*/
void go() {
    while(1) {
        //printf("hello");
        if (record[0] == '+') {
            i++;
            tx = (int(record[5]) - 48) * 0.01 + (int(record[4]) - 48) * 0.1 + ((int(record[2])) - 48);
            if (record[1] == '-') tx =  -tx; 
            tz = (int(record[11]) - 48) * 0.01 + (int(record[10]) - 48) * 0.1+ (int(record[7]) - 48) * 10 + ((int(record[8])) - 48);
            if (record[6] == '-') tz = -tz;
            ry = (int(record[17]) - 48) * 0.01 + (int(record[16]) - 48) * 0.1+ (int(record[12]) - 48) * 100 + (int(record[13]) - 48) * 10 + ((int(record[14])) - 48); 
            //printf("%d, %d\n", x1, x2); 
        }
        //printf("%f, %f, %f", tx, tz, ry);
       // printf("%f, %f, %f", tx1, tz1, ry1);
        //printf("safe %d", i);
        if(i == save) {
            tx1 = tx;
            tz1 = tz;
            ry1 = ry;
            //printf("%f, %f, %f", tx1, tz1, ry1);
           // print
          // turn();
        
        }
        //if(tz1 < 0) tz1 = -tz1;
    t1 = 1000*abs(tz1);/// 3);
    //float tt = t1;
    if (ry1 - 180 >= 0 && ok == 0) {
        car.turn(20, 0.5-((360-ry1)/10)*0.2);
        ThisThread::sleep_for(3000ms); 
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.turn(20, -(0.5-((360-ry1)/10)*0.2));
        ThisThread::sleep_for(3000ms); 
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.goStraight(20);
        ThisThread::sleep_for(t1);
        car.stop();
        ThisThread::sleep_for(1000ms);
        ok++;
        }    
    printf("time %f", t1);    
    else if(ry1 - 180 < 0 && ok == 0) {
        //t1 = 1000 * (tz1 * 2 / 3 / );
        //if(tz1 < 0) tz1 = -tz1;
        //t1 = tz1;
          //  printf("time %f", t1);
       
        car.turn(20, -(0.5-((ry1)/10)*0.2));
        ThisThread::sleep_for(2800ms);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.turn(20, (0.5-((ry1)/10)*0.2));
        //ThisThread::sleep_for(2800ms);
        ThisThread::sleep_for(2800ms);   
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.goStraight(20);
        ThisThread::sleep_for(t1);
        car.stop();
        ThisThread::sleep_for(1000ms);
        ok++;
    }
        
       // printf("time %f", tt);
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
            if(coun < 17) {
                record[coun] = recv[0];
                //printf("%c", record[coun]);
                coun++;
            }
            else if (coun == 17) {
                record[coun] = recv[0];
                //printf("%c", record[coun]);
                coun = 0;
            }
      }
   }
}