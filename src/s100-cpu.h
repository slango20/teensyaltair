#ifndef __S100_CPU_H
#define __S100_CPU_H
#include "s100-card.h"
#include "s100.h"
#include "z80.h"

class S100_CPU : public S100_card, public Z80 { //links Z80's IO to the S100 IO
    private:
    bool halt;
    public:
    char read(uint16_t addr){
        return bus.fetch(addr);
    }
    char ioread(uint16_t addr){
        return bus.iofetch(addr);
    }
    void iowrite(uint16_t addr, char data){
        bus.iostore(addr,data);
    }
    void write(uint16_t addr, char data){
        bus.store(addr,data);
    }
    void reset_action(){
        this->halt = false;
        this->reset();
    }
    void halt_action(){
        this->halt = true;
    }
    void vi_action(char data){
        //this is only ever fired by an IRQ controller, so no check
        this->irq(data); //vectored IRQ TODO: figure this out
    }
    void irq_action(char data){
    //check a "jumper" for whether an IRQ controller is present
        this->irq(data);
    }
    void cycle(); //eternally loops. TODO: allow bus master to yeild to another card as master
    virtual void start(){
        card_start();
    }
    void card_start(){ //called on startup, loops over cycle()
        Serial.printf("CPU card starting...");
        this->resetv(0xFFFE); //reset Z80's PC to a value at FFFE (16-bit)
        while(true){
            this->cycle();
        }
    }
} ;
#endif //__S100_CPU_H
