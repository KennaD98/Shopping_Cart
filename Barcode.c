#include <MKL25Z4.h>
#include <stdio.h>
#include "Barcode_Driver.h"

//Defining inputs
#define Capture                 (5)  //on port A this is the input the switch
#define MASK(x) (1UL << (x))

//#define write               (9)
void Delay(volatile unsigned int time_del);
void Run_Barcode_Driver(void);
uint8_t i,data;
uint8_t Barcode[15];

int main (void ) {

SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;  //Enable Clock

PORTA->PCR[Capture] &= ~PORT_PCR_MUX_MASK; //clear bits in PORTA 5
PORTA->PCR[Capture] |= PORT_PCR_MUX(1);  //set GPIO pin

    PTA->PDDR &= ~MASK(Capture); //Declaring button for capture state as INPUT

}
void Run_Barcode_Driver(void){  //in your original file youre using this line
    while(1) { //infinite loop  always loop

         if ((PTA->PDIR & MASK(Capture))){ //if the capture button is not pressed then the barcode is not working
               Barcode[i]= 0;   //barcode is not reading
             }
              else {
                    for ( i = 0; i < 15; i++ ) {
											   if ((data!=0x0A)){ //  it reads up to 10 char if not 10 then we increment until we read 10
												 Barcode[i]=data;  //data is the value barcode is reading. it is reading 10 numbers
												 i++;  //increment the index
												 }
												 else if((data==0x0A) &&(i<=15)) {  //if it has read 10 but not 15 values
                                Barcode[i]='\0';   //barcode is not done yet
                                memset(Barcode,'\0',15);  //till it reaches 15
                                Barcode[i]=data;  //data is the value barcode is reading. it is reading 15 numbers
																i = 0;
                          }
												}
												for ( i = 0; i > 15; i++ ) {											
													 Barcode[i]= 0;   //barcode is not reading
												 }
                     }
									 }
								 }      

        void Delay(volatile unsigned int time_del){ //delay function
    while (time_del--){
        ;
    }
}

