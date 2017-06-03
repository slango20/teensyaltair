#ifndef __S100_RAM_H
#define __S100_RAM_H
#include "s100-card.h"
#include <stdint.h>

class S100_ram : public S100_card { //note: more than 1 of these will cause conflicts on the bus

    const static char maxpage = 31; //128k, half the teensy's RAM
    char slotlinks[5] = { 0,1,2,3,4 }; //default flat 20k of RAM
    const static int pagesize = 4096;
    virtual uint16_t minaddr() { return 0x0000; }
    virtual uint16_t maxaddr() { return 0x5000; }//this is really maxaddr+1 due to >=
    virtual uint16_t minio() { return 0x0000; }
    virtual uint16_t maxio() { return 0x0004; }//again, +1
    char mem[pagesize*(maxpage+1)]; //TODO: malloc individual pages on first use and use char*[]?
    virtual char read_action(uint16_t addr){
        char segment = (char)(addr/4096); //hopefully compilers don't start rounding instead of truncating
        uint16_t off = (uint16_t)(addr%4096);
        return mem[(pagesize*slotlinks[segment])+off];
    }
    virtual void write_action(uint16_t addr, char data){
        char segment = (char)(addr/4096);
        uint16_t off = (uint16_t)(addr%4096);
        mem[(pagesize*slotlinks[segment])+off] = data;
    }
    virtual char in_action(uint16_t addr){
        return slotlinks[addr+1];
    }
    virtual void out_action(uint16_t addr,char data){
        slotlinks[addr+1] = data; //make sure 0-segment isn't remapped.
    }


};
#endif //S100_RAM_H
