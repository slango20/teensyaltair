#ifndef __S100_CARD_H
#define __S100_CARD_H
#include <stdint.h>
#include <Arduino.h>

class S100_card { //implimented by all virtual cards (including a real card interface)
    public: //note that virtcards implimenting DMA can read from RAM at any moment, unlike a real altair.
    S100_card() {}
    bool slave = true; //these functions use some funky code golf to have overideable default constants
    virtual bool phantom_hide() { return false; }//is this card COMPLETELY hidden by phantom going high?
    virtual uint16_t minaddr() { return 0xFFFF; }//these can be overriden by the child class
    virtual uint16_t maxaddr() { return 0xFFFF; }//if they are equal, it means the card doesn't do that type of IO (ex: a serial card has no need for RAM bus)
    virtual uint16_t minio() { return 0xFFFF;}
    virtual uint16_t maxio() { return 0xFFFF;}
    virtual void start(){} //only used by CPU cards
    virtual void reset_action(){} //reset the virtcard
    virtual void slave_clr_action(){} //reset all slave cards
    virtual char fetch_action(uint16_t){return 0;} //check phantom state before responding.
    virtual void store_action(uint16_t,char){} // no M1 flag support. none planned.
    virtual void halt_action(bool){} //impliment empty unless virtcard is CPU or otherwise needs to halt
    virtual char in_action(uint16_t){return 0;} //port IO instructions
    virtual void out_action(uint16_t,char){}
    virtual void dma_action(){} //if the virtcard does DMA, do it now. return is DMA line asserted, 0 if none. 
                               //TODO: set the real bus's DMA line when any IO is done from within this function
    virtual void err_action(){} //if something goes wrong and error* is asserted
    virtual void phantom_action(bool){} //can be used for masking ROM out of the memory space for more RAM. called by using "bus.phantom(bool);"
    virtual void vi_action(char){} //used primarily by IRQ controller chips that then muck with irq_action to get "vectors"
    virtual void irq_action(char){} //fires on ALL cards, and the one that fires it can use the char to pass 'inta'
    //TODO: make one of these a proper physical bus interface that calls the relevant functions when triggered.
};
#endif //__S100_CARD_H
