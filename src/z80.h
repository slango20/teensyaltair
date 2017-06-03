#ifndef __Z80_H
#define __Z80_H
#include <stdint.h>
class Z80 { //this is a dummy class that does all the heavy lifting for processing, but you are responsible for IO
    private:
    //main and alternate GP registers
    bool alt; //are the alt registers in use?
    char accumulator1;
    char flags1;
    char accumulator2;
    char flags2;
    char reg1[8]; // AF, BC, DE, and HL.
    char reg2[8]; // alternate registers

    char IV; //special purpose registers
    char refresh; //only here to make things happy, never actually used
    uint16_t IX; //these are all addresses, so 16 bit
    uint16_t IY;
    uint16_t SP;
    uint16_t PC;
    bool iff; //IRQ flip flop
    bool iff2; //backup
    void prefix_cb();
    void prefix_ed();
    void prefix_dd();
    void prefix_fd();
    void prefix_ddcb();
    void prefix_fdcb();
    public:
    Z80(){}
    void reset();
    void reset(uint16_t); //vectored reset, just nice to have
    void resetv(uint16_t);
    void irq(char);
    void execute(); 
    virtual char read(uint16_t); //the user impliments all the IO functions in a child class. execute calls these
    virtual void write(uint16_t, char);
    virtual char ioread(uint16_t);
    virtual void iowrite(uint16_t, char);
};
#endif //__Z80_H
