 #include <reg51.h>
 
 void generate38K();
 
 sbit IRsig = P3^7;
 sbit inraredOutput = P3^3;
 sbit Led = P2^0;

/*timerInterrupt 0*/  
void GenInfraRed(void) interrupt 1{ 
	/*flag to do on 600us and off 20ms*/
	static unsigned flag = 0 ;
	/*off for 20ms*/
	if(flag == 0){
		IRsig = 1;
		TF0 = 0;
		TL0 = 0x00;
		TH0 = 0x70;
		 
		TF1 = 0;
	/*set flag for on 600us*/ 		 
		flag = 1;
}  
	/*0n for 600 us*/
	 else{
		IRsig = 0;
		TL0=0xAE;
		TH0=0xFB;
		flag = 0; 
	 }
 }

 /* timerInterrupt 1 */
void generate38K(void) interrupt 3{ 
	 
	 IRsig =~ IRsig;
	 TF1 = 0;  
	 TR1 = 1;
	}
/*externalInterrupt 1*/ 
void obstacleDetected(void) interrupt 2{ 
		
		Led = inraredOutput;
}
	
	
 int main(){
	 /*intializiton*/
	 IRsig = 0;
	 Led = 0;
	 
	 IE = 0x8F;
	 TMOD=0x19;
	 
	 /*timerInterrupt 0 for 600 micro sec*/
	 TL0=0xAE;
	 TH0=0xFB;
	 TR0 = 1; /* anded with P3.2 value of button*/
	 
	 /*timerInterrupt 1 for 38KHZ*/
	 TL1=0xE8;
	 TH1=0xFF;
	 TR1 = 1;
	 
	 while(1);
 }
