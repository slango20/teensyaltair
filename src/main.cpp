#include "hardware.h"
#include "main.h"
#include "s100.h"
#include "cards.h"
#include "frontpanel.h"
#include "z80.h"
//Serial1 is the debug console, allowing the emulator to display it's internal state
void setup() {
    bus.init(cards, sizeof(cards));
    bus.reset(); //intended to reset physical cards if I actually get that working, the virtcards already start in a consistent state.
    bus.start(); //kick control to cards[0];

}

void loop() { //never hit, only implimented because a prototype is declared outside of my control


}







