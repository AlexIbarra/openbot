#ifndef GPIOACCESS_H
#define GPIOACCESS_H


 // Access from ARM Running Linux
#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
 

 
void setup_io();
void set_input_gpio(int g);
void set_output_gpio(int g);
void write_gpio(int g);
void clear_gpio(int g);
int read_gpio(int g);

#endif /* GPIOACCESS_H */

