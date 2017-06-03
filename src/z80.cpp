#include "z80.h"
#include <stdint.h>


    void Z80::prefix_cb(){
    
    }
    void Z80::prefix_ed(){

    }
    void Z80::prefix_dd(){
    
    }
    void Z80::prefix_fd(){

    }
    void Z80::prefix_ddcb(){ //these are called from the relivant prefix function
    
    }
    void Z80::prefix_fdcb(){

    }
    void Z80::resetv(uint16_t addr){ //only called during startup to easily facilitate ROM cards without using phantom of 0000h or a shitload of NOPs
         this->reset(); // this entire function is ONLY here for faster startup. it will never be used in actual operation
         uint16_t vector;
         vector = this->read(addr);
         vector = (this->read(addr+1)<<8); //set high byte
         this->PC = vector;
    }
    void Z80::reset(){
        this->reset(0x0000); //call with default vector of 0
    }
    void Z80::reset(uint16_t vector){
        this->PC = vector;
        this->accumulator1 = 0;
        this->accumulator2 = 0;
        this->alt = false;
        this->flags1 = 0; //FIXME: set the flags to their proper values
        this->flags2 = 0;
        for (int i = 0; i<8; i++){
            reg1[i] = 0;
            reg2[i] = 0; //wipe the slate clean
        }
        this->SP = 0;
        this->IX = 0;
        this->IY = 0;
        this->IV = 0;
        this->refresh = 0;
        this->iff = false; //disable IRQ on reset
        this->iff2 = false; //sent to parity flag after NMI returns and programmer calls "LD A, I/R"
    }
    void Z80::irq(char data){ //FIXME: impliment this
        return;
    }
    void Z80::execute(){
        char instruction = this->read(this->PC); //PC is current instruction on z80
        this->refresh = (this->refresh+1)&0x7F; //something MAY use this to store a boolean or as a counter, so impliment it
        switch (instruction) {
            //prefix bytes
            case 0xCB : prefix_cb(); break;
            case 0xED : prefix_ed(); break;
            case 0xDD : prefix_dd(); break;
            case 0xFD : prefix_fd(); break; //16-bit prefixes are handled within these

            //unprefixed instructions
            case 0x00 : break; //NOP
            case 0x08 :{ uint16_t a = ((uint16_t*) this->reg1)[0]; ((uint16_t*) this->reg1)[0] = ((uint16_t*) this->reg2)[0]; ((uint16_t*) this->reg2)[0] = a;} break; //EX AF AF'
            case 0x10 :{ if (alt) {this->reg2[2]--;if((0x40&this->flags2)>>6){break;}} else {this->reg1[2]--;if((0x40&this->flags1)>>6){break;}}} //DJNZ, relative
            case 0x18 :{ signed char o = this->read(PC+1); PC = (PC+2)+o ;}break; //RJMP, above falls through if nz
            case 0x20 :{ char a ;if(alt){a = this->flags2;} else { a = this->flags1;}if(!((0x40&a)>>6)){signed char o = this->read(PC+1); PC = (PC+2)+o; }} break; //RJNZ
            case 0x28 :{ char a ;if(alt){a = this->flags2;} else { a = this->flags1;}if((0x40&a)>>6){signed char o = this->read(PC+1); PC = (PC+2)+o; }} break; //RJZ
            case 0x30 :{ char a ;if(alt){a = this->flags2;} else { a = this->flags1;}if(!(0x1&a)){signed char o = this->read(PC+1); PC = (PC+2)+o; }} break; //RJNC
            case 0x38 :{ char a ;if(alt){a = this->flags2;} else { a = this->flags1;}if(0x1&a){signed char o = this->read(PC+1); PC = (PC+2)+o; }} break; //RJC
        }
    }

