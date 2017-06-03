#ifndef __S100_H
#define __S100_H
#include <stdint.h>
#include "s100-card.h"


class S100 { // TODO: change the hooks to standard IO latch control signals (the lines that the CPU strobes to read data) and move bounds checking back to the card
    private:
    unsigned int cardcount;
    S100_card *buscards;
    bool _phantom; //this is literally the only "persistent" bus signal needed.
    public:
    void halt(bool dat);
    void start();
    void irq(char dat);
    void phantom(bool p);
    bool phantom();
    void store(uint16_t addr, char data);
    void iostore(uint16_t addr, char data);
    char fetch(uint16_t addr);
    char iofetch(uint16_t addr);
    void reset();
    void init(S100_card* cardarr, int numcards);
};

extern S100 bus;


#endif //__S100_H
