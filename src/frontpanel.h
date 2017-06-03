#ifndef __FRONTPANEL_H
#define __FRONTPANEL_H
#include <stdint.h>
#include "s100-card.h"
#include "s100.h"


typedef struct status {
    bool inte:1;
    bool prot:1;
    bool memr:1;
    bool inp:1;
    bool mi:1;
    bool out:1;
    bool hlta:1;
    bool stack:1;
    bool wo:1;
    bool irq:1; //renamed from int due to obvious conflicts
    char pad:6;
} status;

typedef struct Switch {
    char runstate:2;
    bool step:1;
    char examine:2; //these 2 have "next" alt functions
    char deposit:2;
    char reset:2; //also CLI
    char protect:2; //unprotect
    bool aux1:1;
    bool aux2:1; //should this be reset?
    char pad:3; //bump us up to 16 bits
} Switch ;

char front_readdata(); //read 8 switches
void front_writedata(char); //write data LEDS
void front_writestatus(status); //write status LEDS (10 LEDS)
uint16_t front_readaddr(); //read 16 bits from switch bank
Switch* front_readswitch(); //read lower switches
void front_writeaddr(uint16_t); //write current address to address LEDs

class FrontPanel : public S100_card { //FIXME: figure out how this is attached to the damn thing in real life
    private:
    uint16_t nextaddr;
    bool runstate = true;
    public:
    void halt_action(bool dat){
        runstate = dat;
    }
    char readData(){
        return front_readdata();
    }
    Switch* readSwitch(){
        return front_readswitch();
    }
    uint16_t readAddr(){
        return front_readaddr();
    }
    void writeAddr(uint16_t addr){
        front_writeaddr(addr);
    }
    void writeData(char data){
        front_writedata(data);
    }
    void writeStatus(status *stat){
        front_writestatus(*stat);
    }
    void dma_action(){ //used as a CPU independent source of clock ticks
    Switch* bank = this->readSwitch();
    if (bank->reset){
      bus.reset();
    }
    if (bank->runstate==0x2) { 
      bus.halt(true);
      delay(50); //debounce, practically unnoticable delay
    } else if (bank->runstate == 0x1) {
      bus.halt(false);
    }
    if (runstate){
      return; // make sure RAM editing only happens in HALT state
    } else if ( bank->step ){
      return; //FIXME: NYI
    }
    if (bank->examine == 0x1){
      nextaddr=this->readAddr();
      this->writeAddr(nextaddr);
      this->writeData(bus.fetch(nextaddr));
      delay(10);
      return;
    }
    if (bank->examine == 0x2){
      nextaddr++;
      this->writeAddr(nextaddr);
      this->writeData(bus.fetch(nextaddr));
      delay(10);
      return;
    }
    if (bank->deposit == 0x1){ 
      bus.store(nextaddr,this->readData());
      delay(10);
      return;
    }
    if (bank->deposit == 0x2){
      nextaddr++;
      this->writeAddr(nextaddr);
      bus.store(nextaddr,this->readData());
      delay(10);
      return;
    }
    }
} ;

#endif //__FRONTPANEL_H
