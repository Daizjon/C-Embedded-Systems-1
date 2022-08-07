#include <MKL25Z4.H>
#include <stdio.h>
#include <time.h>

#define MASK(x) (1UL << (x))

// define Debug status bits
#define DBG_ISR_POS (0)
#define DBG_MAIN_POS (1)

#define DEBUG_PORT PTB
//define switches
#define SW_POS1 (6) //anything swpos is swpos1
#define SW_POS2 (7) //switch 2
#define SW_POS3 (4) //switch 3 for portd

// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D

#define READ_SWITCHES  (PTD->PDIR)  //for polling prob ptd




//function prototypes
void init_RGB_LEDs(void);//fine
void control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);
void toggle_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);
extern void init_switch(void);
//count declaration
extern volatile unsigned count;
void delay( volatile unsigned int number_of_seconds);
void init_debug_signals(void);
void PORTD_IRQHandler(void);
extern volatile unsigned red;
extern volatile unsigned int green;
extern volatile unsigned blue;
extern volatile unsigned temp;

volatile unsigned count=1;
volatile unsigned red =1;
volatile unsigned green =0;
volatile unsigned blue =0;
volatile unsigned temp =0;


void delay(volatile unsigned int time_del){
	while (time_del--) {
		;
	}
}

void init_switch(void) { //might be good except for enable interupts
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK ;///* enable clock for port D */| SIM_SCGC5_PORTA_MASK;; /* enable clock for port A */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	PORTD->PCR[SW_POS1] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK; //sw1 //interrupt falling edge
	PORTD->PCR[SW_POS2] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK; //sw2 //interrupt falling edge
	PORTD->PCR[SW_POS3] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a); //sw3 //interrupt falling edge
	
	/* Set port D switch bit to inputs */
	PTD->PDDR &= ~MASK(SW_POS1);
	PTD->PDDR &= ~MASK(SW_POS2);
	PTD->PDDR &= ~MASK(SW_POS3); 

	/* Enable Interrupts */
	//NVIC_SetPriority(PORTD_IRQn, 128); // 0, 64, 128 or 192
	//NVIC_ClearPendingIRQ(PORTD_IRQn); 
//	NVIC_EnableIRQ(PORTD_IRQn);
	
	NVIC_SetPriority(PORTD_IRQn, 0); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);
}

void init_RGB_LEDs(void) {//fine
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;;
	
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);          
	
	// Set ports to outputs
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
	
	control_RGB_LEDs(1, 1, 1);//eh
	control_RGB_LEDs(0, 0, 0);
}

void control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on) {//eh
	if (red_on) {
			PTB->PCOR = MASK(RED_LED_POS);
	} else {
			PTB->PSOR = MASK(RED_LED_POS); 
	}
	if (green_on) {
			PTB->PCOR = MASK(GREEN_LED_POS);
	}	else {
			PTB->PSOR = MASK(GREEN_LED_POS); 
	} 
	if (blue_on) {
			PTD->PCOR = MASK(BLUE_LED_POS);
	}	else {
			PTD->PSOR = MASK(BLUE_LED_POS); 
	}
}	

void toggle_RGB_LEDs(unsigned int red_tog, unsigned int green_tog, unsigned int blue_tog) {
	if (red_tog) {
			PTB->PTOR = MASK(RED_LED_POS);
	} 
	if (green_tog) {
			PTB->PTOR = MASK(GREEN_LED_POS);
	} 
	if (blue_tog) {
			PTD->PTOR = MASK(BLUE_LED_POS);
	}	
}	

void init_debug_signals(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK; /* enable clock for port B */

	/* Select GPIO for pins connected to debug signals*/
	PORTB->PCR[DBG_ISR_POS] |= PORT_PCR_MUX(1);	
	PORTB->PCR[DBG_MAIN_POS] |= PORT_PCR_MUX(1);	
	
	/* Set bits to outputs */
	PTB->PDDR |= MASK(DBG_ISR_POS) | MASK(DBG_MAIN_POS); 
	
	/* Clear output signals initially */
	PTB->PCOR |= MASK(DBG_ISR_POS) | MASK(DBG_MAIN_POS);
}

void PORTD_IRQHandler(void) {  
	DEBUG_PORT->PSOR = MASK(DBG_ISR_POS);
	// clear pending interrupts
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	//NVIC_ClearPendingIRQ(PORTA_IRQn);
\
	
	if ((PORTD->ISFR & MASK(SW_POS3))) {
		PORTD->ISFR = 0x88888888;
	}
	// clear status flags 
	PORTD->ISFR = 0xffffffff;
	DEBUG_PORT->PCOR = MASK(DBG_ISR_POS);
}


int main (void) {
	
	init_switch();
	init_RGB_LEDs();
	init_debug_signals();
	__enable_irq();
	unsigned switch_code;
	 int mem;
	
	while (1) {
		  DEBUG_PORT->PTOR = MASK(DBG_MAIN_POS);
			control_RGB_LEDs(count&1, count&2, count&4); 
	
	while (1) {
		switch_code = ~READ_SWITCHES; 
		if (switch_code & MASK(SW_POS1)) {
			count++;
			control_RGB_LEDs(count&1, count&2, count&4);
		} else if (switch_code & MASK(SW_POS2)) {
			control_RGB_LEDs(0, 0, 0);
			unsigned int countcopy = count;
			count =0;
			PORTD->ISFR = 0xffffffff;
			delay(rand() %9000000 + 3000000); // wait between 1-3 seconds 
			control_RGB_LEDs(countcopy&1,countcopy&2,countcopy&4); //turn back on specified led
			do {
		count++;
			
		} while( PORTD->ISFR != (PORTD->ISFR & MASK(SW_POS3)) );
		mem = count; //save count to memory 
	
			delay(15000000); //wait 5 seconds
		
		} 
   		else {
			count=count;
		}
		//control_RGB_LEDs(count&1, count&2, count&4);
	}
}
}