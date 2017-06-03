#include "s100-card.h"
#include "s100-cpu.h"
#include "s100-video.h"
#include "s100-serial.h"
#include "s100-rom.h"
#include "s100-ram.h"
#include "s100-tape.h"
#include "s100-debug.h"

extern S100_card cards[3] = { //add the contructors of various cards here
    S100_CPU(),
    S100_ram(),
    S100_debug(),
};
