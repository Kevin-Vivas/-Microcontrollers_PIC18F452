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
unsigned int lec=0;
unsigned int conv_ADC(unsigned char canal);
unsigned char A=0;
unsigned char SEN_DE=0, SEN_MED=0,SEN_IZQ=0;

int res_0=0,res_1=0;
float volt=0;



void conf_puertos(void);
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);  
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);


void conf_ADC(void);


void conf_PWM(void);
void duty_1(unsigned char dc);
void duty_2(unsigned char dc);

//..............codigo principal................................................................

void main(void) {

    //.........................conf perifericos.................................................
    conf_puertos();
	
	 
    conf_PWM();
    

    ini_LCD(); //inicializa la LCD
    
    write_LCD(sprintf(buffer,"MOTORES Y ")); 
        
    ins_LCD(192);
    
    write_LCD(sprintf(buffer,"SENSORES"));
    
    __delay_ms(2000);
    ins_LCD(1);
    conf_ADC();

    //.........................bucle.............................................................
    while (1)
    {
        ins_LCD(1);
       write_LCD(sprintf(buffer,"GIRO DERECHA"));
       
       
       
        duty_1(80);
        duty_2(80);
        __delay_ms(2000);
   
        duty_1(90);
        duty_2(90);
        __delay_ms(2000);
        
        ins_LCD(1);
       write_LCD(sprintf(buffer,""));
         duty_1(40);
        duty_2(40);
        __delay_ms(2000);
        
        ins_LCD(1);
        write_LCD(sprintf(buffer,"CAMBIO DE GIRO"));
        LATB=0XF0;
        duty_1(00);
        duty_2(00);
        __delay_ms(2000);

        duty_1(80);
        duty_2(80);
        __delay_ms(2000);
        duty_1(90);
        duty_2(90);
        __delay_ms(2000);

        duty_1(40);
        duty_2(40);
        __delay_ms(2000);
        LATB=0X0F;
         duty_1(00);
        duty_2(00);
        __delay_ms(2000);
   //.........................SEN_DE................................................................
      while(1) {
        ins_LCD(128);
       lec=conv_ADC(0);
       volt=lec*0.0048;
	   write_LCD(sprintf(buffer,"SEN_DE:  %2f",volt));
       ins_LCD(192);
       
if(volt<3.0)
    {

        SEN_DE=0;
    }

    else
        {

          SEN_DE=1;  
        }
    write_LCD(sprintf(buffer,"ESTADO:  %d",SEN_DE));
    

   __delay_ms(1500);
    ins_LCD(1);
//...............................SEN_IZQ.................................................................
    ins_LCD(128);
    lec=conv_ADC(1);
    volt=lec*0.0048;
	write_LCD(sprintf(buffer,"SEN_IZQ:  %2f",volt));
    ins_LCD(192);
       
         if(volt<3.0)
    {

        SEN_IZQ=0;
        
    }

    else
        {

          SEN_IZQ=1;
           
        }

    write_LCD(sprintf(buffer,"ESTADO:  %d",SEN_IZQ));
   __delay_ms(1500);
    ins_LCD(1);
//............................................SEN_MED............................................................................
    ins_LCD(128);
    lec=conv_ADC(2);
    volt=lec*0.0048;
	write_LCD(sprintf(buffer,"SEN_MED:  %2f",volt));
    ins_LCD(192);
		

         if(volt<3.0)
    {

        SEN_MED=0;
        
    }

    else
        {

          SEN_MED=1;  
        }
    write_LCD(sprintf(buffer,"ESTADO:  %d",SEN_MED));
   __delay_ms(1500);
   ins_LCD(1);
      }
       
       
        
  
    }

}
//......................funciones............................................................

void conf_puertos(void) {

    TRISD = 0x00; // puerto D de salida
    LATD = 0; // limpia puerto D
    PORTD = 0; // limpia puerto D

    
    
	TRISA=0xff;
    LATA=0;
    PORTA=0;
   
    TRISE = 0x00; // puerto E de salida
    LATE = 0x00; // Limpia puerto 
    PORTE = 0x00; // Limpia puerto
    ADCON1 = 0x06; //Puerto E digital

	TRISC=0x00;         // puerto C de salida
    LATC=0;             // limpia puerto C
    PORTC=0;            // limpia puerto C

    TRISB=0x00;         // puerto B de salida
    LATB=0;             // limpia puerto B
    PORTB=0;            // limpia puerto B
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

void conf_ADC(void){
    ADCON0=0b00000001;
    ADCON1=0b00000010;
}
unsigned int conv_ADC(unsigned char canal){
    unsigned int temp=0;
    
    if(canal>7){
        return 0;
    }else{
        canal<<=3;
        ADCON0&=0xC7;
        ADCON0|=canal;
        __delay_us(50);
        GO=1;
        while(GO==1){}
        ADRESL>>=6;
        temp=ADRESH;
        temp<<=2;
        temp|=ADRESL;
        
        return temp;
    }
}
void conf_PWM(void){
     PR2=124;
    CCPR1L=0;
    CCPR2L=0;
    T2CON=0b00000101;
    CCP1CON=0b00001100;
    CCP2CON=0b00001100;
}


void duty_1(unsigned char dc){
    unsigned int lamda=0;
    
    lamda=dc;
    lamda*=5;
    CCPR1L=lamda>>2;
    lamda<<=4;
    lamda&=0x30;
    CCP1CON&=0xCF;
    CCP1CON|=lamda;;
}

void duty_2(unsigned char dc){
    unsigned int lamda=0;
    
    lamda=dc;
    lamda*=5;
    CCPR2L=lamda>>2;
    lamda<<=4;
    lamda&=0x30;
    CCP2CON&=0xCF;
    CCP2CON|=lamda;
}