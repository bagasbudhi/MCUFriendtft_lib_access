//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
//AVR   pin |PD7|PD6|PD5|PD4|PD3|PD2|PB1|PB0| |PC0|PC1|PC2|PC3|PC4|
#define RD_PORT CMSDK_GPIO0->DATAOUT
#define RD_PIN  0
#define WR_PORT CMSDK_GPIO0->DATAOUT
#define WR_PIN  1
#define CD_PORT CMSDK_GPIO0->DATAOUT
#define CD_PIN  2
#define CS_PORT CMSDK_GPIO0->DATAOUT
#define CS_PIN  3
#define RESET_PORT CMSDK_GPIO0->DATAOUT
#define RESET_PIN  4

#define BMASK         0x03              //more intuitive style for mixed Ports
#define DMASK         0xFC              //does exactly the same as previous
#define write_8(x)    { CMSDK_GPIO9->DATAOUT = (CMSDK_GPIO9->DATAOUT & ~BMASK) | ((x) & BMASK); CMSDK_GPIO8->DATAOUT = (CMSDK_GPIO8->DATAOUT & ~DMASK) | ((x) & DMASK); }
#define read_8()      ( (CMSDK_GPIO9->DATA & BMASK) | (CMSDK_GPIO8->DATA & DMASK) )
#define setWriteDir() { 9->OUTENSET |=  BMASK; DDRD |=  DMASK; }
#define setReadDir()  { 9->OUTENCLR |=  BMASK; DDRD &= ~DMASK; }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

