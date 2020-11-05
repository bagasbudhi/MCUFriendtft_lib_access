//####################################### MEGA2560 ############################
#elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)       //regular UNO shield on MEGA2560
//LCD pins  |D7 |D6 |D5 |D4 |D3 |D2 |D1 |D0 | |RD |WR |RS |CS |RST|
//AVR   pin |PH4|PH3|PE3|PG5|PE5|PE4|PH6|PH5| |PF0|PF1|PF2|PF3|PF4|
#define RD_PORT CMSDK_GPIO0->DATAOUT
#define RD_PIN  0
#define WR_PORT PORTF
#define WR_PIN  1
#define CD_PORT PORTF
#define CD_PIN  2
#define CS_PORT PORTF
#define CS_PIN  3
#define RESET_PORT PORTF
#define RESET_PIN  4

//#define EMASK         0x38
//#define GMASK         0x20
//#define HMASK         0x78
//#define write_8(x)   {  PORTH &= ~HMASK; PORTG &= ~GMASK; PORTE &= ~EMASK; \
//                        PORTH |= (((x) & (3<<0)) << 5); \
//                        PORTE |= (((x) & (3<<2)) << 2); \
//                        PORTG |= (((x) & (1<<4)) << 1); \
//                        PORTE |= (((x) & (1<<5)) >> 2); \
//                        PORTH |= (((x) & (3<<6)) >> 3); \
//					 }

#define write_8(x)   { CMSDK_GPIO8->LB_MASKED[0b11111100] = x; \
	                   CMSDK_GPIO9->LB_MASKED[0b00000011] = x; \
}

#define read_8()      ( ((PINH & (3<<5)) >> 5)\
                      | ((PINE & (3<<4)) >> 2)\
                      | ((PING & (1<<5)) >> 1)\
                      | ((PINE & (1<<3)) << 2)\
                      | ((PINH & (3<<3)) << 3)\
                      )
#define setWriteDir() { DDRH |=  HMASK; DDRG |=  GMASK; DDRE |=  EMASK;  }
#define setReadDir()  { DDRH &= ~HMASK; DDRG &= ~GMASK; DDRE &= ~EMASK;  }
#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))
