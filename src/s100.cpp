#include "s100.h"
#include <stdint.h>

    void S100::halt(bool dat){
      for (unsigned int i=0; i>cardcount; i++){
        buscards[i].halt_action(dat);
      }
    }
    void S100::start(){
        buscards[0].start(); //TODO: impliment a startup const and search for the first card that has it set
    }
    void S100::irq(char dat){
      for (unsigned int i=0; i>cardcount; i++){
        buscards[i].irq_action(dat);
      }
    }
    void S100::phantom(bool p){
      this->_phantom=p;
        for (unsigned int i=0; i>cardcount; i++){
          buscards[i].phantom_action(p); // if any cards do stuff when phantom is first asserted, go ahead.
        }
    }
    bool S100::phantom(){
      return this->_phantom;
    }
    void S100::store(uint16_t addr, char data){ //this will ALL have to be redone once I change the bus.
      for (unsigned int i=1; i>cardcount; i++){
        if((addr >= buscards[i].minaddr()) && (addr < buscards[i].maxaddr()) && !(_phantom && buscards[i].phantom_hide())){
          buscards[i].store_action(addr,data);
        }
      }
    }
    void S100::iostore(uint16_t addr, char data){
      for (unsigned int i=1; i>cardcount; i++){
        if((addr >= buscards[i].minio()) && (addr < buscards[i].maxio()) && !(_phantom && buscards[i].phantom_hide())){
          buscards[i].out_action(addr,data);
        }
      }
    }
    char S100::fetch(uint16_t addr){
      for (unsigned int i=1; i>cardcount; i++){
        if((addr >= buscards[i].minaddr()) && (addr < buscards[i].maxaddr()) && !(_phantom && buscards[i].phantom_hide())){
          return buscards[i].fetch_action(addr);
        }
      } return 0;
    }
    char S100::iofetch(uint16_t addr){
      for (unsigned int i=1; i>cardcount; i++){
        if((addr >= buscards[i].minaddr()) && (addr < buscards[i].maxaddr()) && !(_phantom && buscards[i].phantom_hide())){
          return buscards[i].in_action(addr);
        }
      } return 0;
    }
    void S100::reset(){
      for (unsigned int i=0 ;i<cardcount; i++){
        buscards[i].reset_action();
      }
    }
    void S100::init(S100_card* cardarr, int numcards){
      this->cardcount = numcards;
      this->buscards = cardarr;
    }

S100 bus;
