#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"


Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);
void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
BBCar car(pin5, pin6, servo_ticker);

int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   }
}
void parking(Arguments *in, Reply *out) {
    int d1 = in->getArg<int>();
    int d2 = in->getArg<int>();
    const char *dir = in->getArg<const char*>();
    if (strcmp(dir, "east") == 0) {
        float t1 = 1000 * (d2 - 3.8) / 19.5;
        float t2 = 1000 * (d1 - 9.3) / 19.5;
        car.goStraight(-100);
        ThisThread::sleep_for(t1);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.turn(-100, -0.48);
        ThisThread::sleep_for(2000ms);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.goStraight(-100);
        ThisThread::sleep_for(t2);
        car.stop();
        ThisThread::sleep_for(1000ms);
    }    
    /*car.goStraight(-100);
    ThisThread::sleep_for(1000ms);
    car.stop();
    ThisThread::sleep_for(1000ms);*/
    else if (strcmp(dir, "west") == 0) {
        float tt1 = 1000 * (d2 - 3) / 19.5;
        float tt2 = 1000 * (d1 - 8) / 19.5;
        car.goStraight(-100);
        ThisThread::sleep_for(tt1);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.turn(-100, 0.227);
        ThisThread::sleep_for(2000ms);
        car.stop();
        ThisThread::sleep_for(1000ms);
        car.goStraight(-100);
        ThisThread::sleep_for(tt2);
        car.stop();
        ThisThread::sleep_for(1000ms);
    }
    return;
}