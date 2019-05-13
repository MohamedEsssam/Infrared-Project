#include <reg51.h>
 
 
 sbit infraredSignal = P3^7;
 sbit infraredOutputSignal = P3^3;
 sbit Led = P2^0;
 sbit SW = P3^2;
 
 unsigned char overflow = 0;
 
 /* Timer 0 Interrupt (to load Timer 1 with 38KHZ )*/
 void generateSignal_Timer0(void) interrupt 1{// timerInterrupt 0
	 /*load Timer 1 with 38KHZ */
	 TL1=0xFA;
	 TH1=0xFF;
	 infraredSignal =1;
	 overflow++;
	 /*Start Timer 1 and Intrrupt Timer 1*/
	 TR1 = 1;
 }
 /* Timer 1 Interrupt (For generte 38KHZ signl in on mode 600us and off for 20ms)*/
 void generateSignal38KHZ_Timer1(void) interrupt 3{// timerInterrupt 1
	 /* Enter the off mode  */
		if(overflow==50){
		TF1=0;
		TL0 = 0x00;
		TH0 = 0x70;
		infraredSignal=0;
		TR0=1;
		overflow=0;
		}
		/*Enter the on mode*/
		else{		
		overflow++;	
		TF1 = 0; 
		infraredSignal =~ infraredSignal;			
		TL1=0xFA;
    TH1=0xFF;
		TR1 = 1;
		}}
 
/* external Interrupt 0(For Push button)*/
	void pushButton(void) interrupt 0{
		TL0 = 0x00;
		TH0 = 0x70;
		/*for Call Timer Interrupt 0  */
		TR0 = 1;
		infraredSignal=0;	
	}
	/*Intialize the input and output prephral*/
	void Intialize(){
	 Led = 0;
	 SW= 1; 
	 infraredOutputSignal = 1;
	 infraredSignal = 0;
	}
 int main(){
	 /*Enable the interrupt set EA,EX0,EX1,ET1,ET0*/
	 IE = 0x8F;
	 /*Enable timer 0 in mode 1 and timer 1 in mode 1*/
	 TMOD=0x19;
	 
	 Intialize();
	 /*Enable Timer 0*/
	 TR0=1;
	 
	 while(1){
		/*Set Led if return ouput = 1 and clear Led if return output = 0 */ 
	 Led = infraredOutputSignal;
	 }
	 
 }
