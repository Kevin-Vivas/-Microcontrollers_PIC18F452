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

unsigned char buffer[40];       //Variables LCD
unsigned int num=65530;         //Variables LCD

unsigned char A=0, sensorDerecha=0, sensorIzquierda = 0, sensorAtras=0;              // variables ADC
unsigned int lec = 0;
int res_0=0, res_1=0, res_2=0;  // Vvariables ADC

void conf_puertos(void);            //Fubciones LCD
void ini_LCD(void);                 //Fubciones LCD
void enable(void);                  //Fubciones LCD
void dato_LCD(unsigned char dato);  //Fubciones LCD
void ins_LCD(unsigned char dato);   //Fubciones LCD
void write_LCD(unsigned char tam);  //Fubciones LCD

void conf_ADC(void);                // Fubciones ADC
unsigned int conv_ADC(unsigned char canal); // Fubciones ADC
float vol = 0;
//..............codigo principal................................................................

void main(void) {
    //.........................conf perifericos.................................................
    conf_puertos();
    ini_LCD(); //inicializa la LCD
    
    write_LCD(sprintf(buffer,"RE PROS")); 
        
    ins_LCD(192);
    
    write_LCD(sprintf(buffer,"BUENASSSS"));
    __delay_ms(2000);
    ins_LCD(1);

    conf_ADC();

    //.........................bucle.............................................................
    while (1) {
        
        ins_LCD(128);
        lec = conv_ADC(0); 
        vol= lec*0.0048;
         ins_LCD(1);
        write_LCD(sprintf(buffer,"SENSOR 1 %.d" ,lec));
        
        ins_LCD(192);
        write_LCD(sprintf(buffer,"SENSOR 1 %.2f" ,vol));
        
        if (vol < 2.8)
        {
            sensorIzquierda=0;
        }else{
            sensorIzquierda=1;
        }
        write_LCD(sprintf(buffer,"SI = %d", sensorIzquierda));
        
        __delay_ms(2000);
        ins_LCD(1);
        
        
        lec = conv_ADC(1); 
        vol= lec*0.0048;
        ins_LCD(1);
        write_LCD(sprintf(buffer,"SENSOR 2 %d" ,lec));
        ins_LCD(192);
        write_LCD(sprintf(buffer,"SENSOR 2 %.2f" ,vol));
        if (vol < 2.8)
        {
            sensorDerecha=0;
        }else{
            sensorDerecha=1;
        }
        write_LCD(sprintf(buffer,"S2 = %d", sensorDerecha));
        
        __delay_ms(2000);
        ins_LCD(1);
        
        
        lec = conv_ADC(2); 
        vol= lec*0.0048;
        ins_LCD(1);
        write_LCD(sprintf(buffer,"SENSOR 3 %d" ,lec));
        ins_LCD(192);
        write_LCD(sprintf(buffer,"SENSOR 3 %.2f" ,vol));
        if (vol < 2.8)
        {
            sensorAtras=0;
        }else{
            sensorAtras=1;
        }
        write_LCD(sprintf(buffer,"S3 = %d", sensorAtras));
        
        __delay_ms(2000);
        ins_LCD(1);

        
    }    
}            
                      //......................funciones............................................................

void conf_puertos(void) {
    
   

    TRISD = 0x00;   // puerto D de salida
    LATD = 0;       // limpia puerto D
    PORTD = 0;      // limpia puerto D

    TRISE = 0x00;   // puerto E de salida
    LATE = 0x00;    // Limpia puerto 
    PORTE = 0x00;   // Limpia puerto
    ADCON1 = 0x06;  //Puerto E digital
   
    TRISB = 0xff;   // puerto B de ENTRADA
    LATB = 0;       // limpia puerto B
    PORTB = 0;      // limpia puerto B
    
    TRISC = 0X00;   //Puerto C de salida
    LATC =0;        //Limpia puerto C
    PORTC = 0;      //Limpia puerto C
    RBPU = 0; 
     
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
	RS=1;               //RS en 1 (envia dato)
	bus=dato;			//dato a publicar 
	enable();
	__delay_ms(2);		//tiempo de ejecucion
}

//...................instruccion..................................
void ins_LCD(unsigned char dato)
{
	RS=0;               //RS en 0 (envia instruccion)
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
void conf_ADC(void){
    ADCON0 = 0b00000001;
    ADCON1 = 0b00000010;
}
unsigned int conv_ADC(unsigned char canal){
    unsigned int temp=0;
    
    if(canal>7){
        return 0;
    }else{
        canal<<=3;
        ADCON0 &=0xC7;
        ADCON0 |=canal;
        __delay_us(50);

        GO=1;
        while(GO==1){}
        temp=ADRESH;
        temp<<=2;
        temp|=ADRESL>>6;
        
        return temp;
        
    }
}
