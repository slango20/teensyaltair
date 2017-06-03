#ifndef __S100_DEBUG_H
#define __S100_DEBUG_H
#include "s100-card.h"
#include <stdint.h>

//debugging virtcard simply used for printf debugging of the emulators internal state
//TODO: add a simple form of emulated state debugging using dma_action as a chance to Serial.read if available

class S100_debug : public S100_card {
    virtual void reset_action(){
        Serial.println("Virtcards reset");
    }
    virtual void slave_clr_action(){
        Serial.println("Slave virtcards cleared");
    }
    virtual char fetch_action(uint16_t addr){ //TODO: fully virtualize bus control signals
        Serial.printf("Bus fetch at %#4x\n",addr); //unfortunately virtcards can't snoop a bus result for now due to the way the bus works (as of version 0.1 read results can only be seen by the master)
    }
    virtual void store_action(uint16_t addr,char data){
        Serial.printf("Bus store at %#4x with %#3x\n", addr,data);
    }
    virtual void halt_action(){
        Serial.println("Master asserted HALT");
    }
    virtual char in_action(uint16_t addr){
        Serial.printf("IO fetch from %#4x\n",addr);
    }
    virtual void out_action(uint16_t addr,char data){
        Serial.printf("IO store to %#4x of %#3x\n",addr,data);
    }
    virtual void err_action(){
        Serial.println("What the hell just happened?");
    }
    virtual void phantom_action(bool state){
        Serial.printf("Phantom triggered with state of %s\n", state ? "true" : "false" );
    }
    virtual void vi_action(char data){
        Serial.printf("Vectored IRQ of type %#3x\n",data);
    }
    virtual void irq_action(char data){
        Serial.printf("IRQ with bus data of %#3x\n",data);
    }

};
#endif //__S100_DEBUG_H
