#include "hardware.h"
#include "frontpanel.h"
#include "Arduino.h"

extern char front_readdata(){
    char dat = 0;
    for (int i = 0; i<8; i++){
        dat = (digitalRead(SWITCHBANK[i]) << i)|dat;
    }
    return dat;
}
extern void front_writedata(char dat){
    for (int i = 0; i<8; i++){
        digitalWrite(DATA_LEDS[i],dat>>1);
    }
}
extern void front_writestatus(status dat){
    uint16_t dat1 = *(uint16_t *)&dat ;
    for (int i = 0; i<10; i++){
        digitalWrite(STATUS_LEDS[i],(dat1>>1)&0x1);
    }
}
extern uint16_t front_readaddr(){ //same as data but all 16 pins
    uint16_t dat = 0;
    for (int i = 0; i<16; i++){
        dat |= (digitalRead(SWITCHBANK[i])<<i);
    }
    return dat;
}
extern Switch* front_readswitch(){
    uint16_t dat = 0;
    for (int i = 0; i<14;i++){
        dat |= (digitalRead(SWITCHES[i])<<i); //pack the data
    }
    return (Switch *)&dat;
}
extern void front_writeaddr(uint16_t dat){
    for (int i = 0; i<16; i++){
        digitalWrite(ADDR_LEDS[i],(dat>>i)&0x1);
    }
}

