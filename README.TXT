License: GNU GPLv3 (see LICENSE.txt for details)

IMPORTANT:
THIS WILL NOT RUN YET. It may compile and "start," but some *essential* virtcards are not completely implimented yet (such as the front panel and CPU)

This is an emulator for the altair 8800 bus with a Z80 CPU for the teensy 3.5 and 3.6.
The bus implimentation is currently incomplete, as the results of a read can only be seen
by the current bus "master" (the virtcard that called bus.read())

Future plans on migrating to a global bus that actually behaves more like a bus are in the works.
a read() will only push the address to the bus and set the control signal telling the card addr
is stable and will return when all cards have been called (the phy virtcard will wait until a response or
a timeout before touching the virt bus and returning).

As it stands now with the "abstract" bus model, DMA between virtcards can occur "instantaniously,"
regardless of CPU state.

There is a special tweak made to the vZ80 used by the CPU virtcard, when the device first powers up, it resets to a vector address at 0xFFFE.
This can be utilized by the ROM card to provide an "autostart" monitor until the user manually resets the machine (all resets afterward reset
to PC=0x0000 regardless, although you can modify the 0xFFFE in s100-cpu.c to whatever vector you want)

TODO: use a define or a jumper to enable/disable vectored startup

When specifying the array of virtcards in cards.h, the first one is always the primary bus master, and if multiple cards would respond to the read
the first one will win. (soon to be the last, due to iterating over the virtual bus on strobe cycles) Maybe add a check and assert error* and/or return bitwise OR of both datum?
Writes with multiple cards reacting are fine (as in a real altair) due to only one thing asserting lines on the bus.

The debug card uses the teensy Serial1 to print debug messages such as whenever the bus is poked for a write.
Due to the way the bus is currently implimented, a read is impossible to sniff.
loading/dumping stuff via x/ymodem is on the TODO list for later (preferably with a "host initiates" type protocol so that the computer can be ready)

The virtcards completely implimented are:
* debug
* z80-cpu^1

1: The CPU *card* is implimented pretty completely, but the actual Z80 is not

The virtcards partially implimented are:
* front panel. The panel code is "complete," but more research on how it was connected to the altair is required (did it poke the bus? was it connected to the CPU? etc.)
if kill the bit is enough indication, I'd guess it's an IO port card (if so, wonderful. easy refactor)

The virtcards not started yet are:
* video
* floppy
* tape (both cassete and DECTape, with real passthrough using teensy DSP and DAC/ADC)
* disk
* up to 1M RAM (using 4 4k interchangable pages set via IO address 0x0000-0x0003 (pages 1-255, set to 0 to disable for memory mapped IO overlap)
CAUTION: a page can be mapped to more than one slot at once! 0x0000 is ALWAYS page 0, so there are at most 5 pages of RAM enabled at any given time.
the map should default to a flat 20k starting at 0x0000 (pages 0-4)

* 4k ROM
* 1k NVRAM (implimented using RTC RAM, EEPROM, or SD on the teensy)
* serial (maybe an internal modem as well using the teensy's DSP and an external line transciever?)
* parallel (should be simple, load a byte to IO and assert strobe until device responds, and the inverse)
* pretty much anything not listed above
