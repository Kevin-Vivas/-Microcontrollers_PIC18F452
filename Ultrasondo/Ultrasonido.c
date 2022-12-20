//..................librerias......................................................................................
#include <xc.h>
#include <stdio.h>

//....................conf_fusibles................................................................................
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define _XTAL_FREQ 4000000
#define EN RE2
#define RS RE0
#define bus LATD

//..............variables globales y prototipos de funcion.........................................................

unsigned char buffer[40];
unsigned int distancia = 0 ,distancia1 = 0 , distancia2 = 0 ;

void conf_puertos(void);
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);  
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

void conf_TIMER0(void);
unsigned int ultrasonido(void);
unsigned int ultrasonido1(void);
unsigned int ultrasonido2(void);

//..............codigo principal................................................................

void main(void) {

    //.........................conf perifericos.................................................
    conf_puertos();
	conf_TIMER0();
    ini_LCD(); //inicializa la LCD
    
    write_LCD(sprintf(buffer,"5 para todos")); 
        
    ins_LCD(192);
    
    write_LCD(sprintf(buffer,"Se la creyeron"));
    
    __delay_ms(2000);
    

    //.........................bucle.............................................................
    while (1) {
        ins_LCD(1);
         write_LCD(sprintf(buffer,"Ultrasonido DE:"));

        ins_LCD(192);
		distancia = ultrasonido();
		write_LCD(sprintf(buffer,"%3u",distancia));
     
		__delay_ms(3000);
        
		 ins_LCD(1);
         write_LCD(sprintf(buffer,"Ultrasonido MED:"));
		ins_LCD(192);
		distancia1 = ultrasonido1();
		write_LCD(sprintf(buffer,"%3u",distancia1));
		__delay_ms(3000);

		ins_LCD(1);
         write_LCD(sprintf(buffer,"Ultrasonido IZ:"));
		ins_LCD(192);
		distancia2 = ultrasonido2();
		write_LCD(sprintf(buffer,"%3u",distancia2));
		__delay_ms(3000);


    }
}

//......................funciones............................................................

void conf_puertos(void) {

    TRISD = 0x00; // puerto D de salida
    LATD = 0; // limpia puerto D
    PORTD = 0; // limpia puerto D

    TRISE = 0x00; // puerto E de salida
    LATE = 0x00; // Limpia puerto 
    PORTE = 0x00; // Limpia puerto
    ADCON1 = 0x06; //Puerto E digital

	TRISB = 0b00101010;	//pares salida impares entrada para sensores
	LATB = 0;
	PORTB = 0; 
}

//...................ini_LCD....................................
void ini_LCD (void)
{
	__delay_ms(20);     // delay 20 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	__delay_ms(5);		// delay 5 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	__delay_ms(1);		// delay 1 ms
	bus=0x30;			// VALOR DE INICIALIZACION
	enable();

	bus=0b00111000;	// Function set 8 bits - 2 lineas - 5*8
	enable();

	bus=0b00001000;	// display off
	enable();

	bus=0b00000001;	// display clear
	enable();

	bus=0b00000110;	// entry mode set - incrementa la posicion del cursor
	enable();

	bus=0b00001110;	// display on/off control - LCD on - cursor on - blink off
	enable();
    
    
}

//...................enable....................................
void enable (void)
{
	EN=1;	// enable en alto
	__delay_ms(1);
	EN=0;	// enable en bajo
}

//...................dato....................................
void dato_LCD(unsigned char dato)
{
	RS=1;	//RS en 1 (envia dato)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(2);		//tiempo de ejecucion
}

//...................instruccion..................................
void ins_LCD(unsigned char dato)
{
	RS=0;	//RS en 0 (envia instruccion)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(2);		//tiempo de ejecucion
}
void write_LCD(unsigned char tam){
    
    unsigned char i;
    
    for(i=0;i<tam;i++){
        dato_LCD(buffer[i]);
    }
}

void conf_TIMER0(void){
	T0CON = 0b00001000; //apagado, 16 bits, reloj interno, no preescaler
			
}

unsigned int ultrasonido(void){
	unsigned int timerValue=0;
	unsigned char timerLow=0;

	TMR0H = 0;
	TMR0L = 0;

	RB0 = 1;
	__delay_us(10);
	RB0 = 0;
	
    while(RB1 == 0);
    TMR0ON = 1;
	while(RB1 == 1);
	TMR0ON = 0;

	timerLow = TMR0L;
	timerValue = TMR0H;

	timerValue = (timerValue<<8)+timerLow;
	timerValue /= 58;

	return timerValue;
}

unsigned int ultrasonido1(void){
	unsigned int timerValue=0;
	unsigned char timerLow=0;

	TMR0H = 0;
	TMR0L = 0;

	RB2 = 1;
	__delay_us(10);
	RB2 = 0;
	
    while(RB3 == 0);
    TMR0ON = 1;
	while(RB3 == 1);
	TMR0ON = 0;

	timerLow = TMR0L;
	timerValue = TMR0H;

	timerValue = (timerValue<<8)+timerLow;
	timerValue /= 58;

	return timerValue;
}

unsigned int ultrasonido2(void){
	unsigned int timerValue=0;
	unsigned char timerLow=0;
    
	TMR0H = 0;
	TMR0L = 0;
	RB4 = 1;
	__delay_us(10);
	RB4 = 0;
	
    while(RB5 == 0);
    TMR0ON = 1;
	while(RB5 == 1);
	TMR0ON = 0;

	timerLow = TMR0L;
	timerValue = TMR0H;

	timerValue = (timerValue<<8)+timerLow;
	timerValue /= 58;

	return timerValue;
}