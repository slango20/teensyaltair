// HARDWARE CONFIGURATION, define pins that go to things

#define DATA_LEDS (char[] ){ 1,2 } // 8 LEDS
#define ADDR_LEDS (char[]){ 1,2 } // 16
#define STATUS_LEDS (char[]){ 1,2 } //10
#define SWITCHBANK (char[]){ 1,2 } //16 switch bank, right to left from the front (a/d0 is first)
#define SWITCHES (char[]){ 1,2 } //8 lower switches and alt functions (specify alt as second if it has one, use struct comment below for order)
#define WAIT_LED (char[]){ 1,2 } //1 LED
#define HLDA_LED (char[]){ 1,2 } //1 LED

/*
typedef struct Switch {
    char runstate:2;
    bool step:1;
    char examine:2; //these 2 have "next" alt functions
    char deposit:2;
    char reset:2; //also CLI
    char protect:2; //unprotect
    bool aux1:1;
    bool aux2:1; //should this be reset?
} union struct { int switchbar:13 } SwitchByte;
*/
