z//..................librerias......................................................................................
#include <xc.h>

//....................conf_fusibles................................................................................
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define _XTAL_FREQ	4000000		// Definicion del valor del cristal

//..............variables globales y prototipos de funcion.........................................................
unsigned char A=0;
unsigned int x=0;
int res_0=0,res_1=0;

void conf_puertos(void);
void conf_ADC(void);
//.........PWM.................
void conf_puertos(void);
void conf_PWM(void);
void duty_1(unsigned char dc);
unsigned int conv_ADC(unsigned char canal);

//..............codigo principal................................................................
void main(void) {
    
    //.........................conf perifericos.................................................
    conf_puertos();
    conf_ADC();
//.......CONF PWM ............
    conf_puertos();
    conf_PWM();
    duty_1(99);
    //.........................bucle.............................................................
    while(1)
    {
        
       res_0=conv_ADC(0);
       LATD=res_0>>2;
       LATC=res_0<<6;
       __delay_ms(2000);

       res_1=conv_ADC(1);
       LATD=res_1>>2;
       LATC=res_1<<6;
       __delay_ms(2000);

             
    }
    
 }

//......................funciones............................................................
void conf_puertos(void){
    
    TRISB=0xFF;         // puerto B de entrada
    LATB=0;             // limpiar puerto B
    PORTB=0;            // limpiar puerto B
    
    TRISD=0x00;         // puerto D de salida
    LATD=0;             // limpia puerto D
    PORTD=0;            // limpia puerto D
    
    TRISC=0x00;         // puerto C de salida
    LATC=0;             // limpia puerto C
    PORTC=0;            // limpia puerto C
    
    TRISE=0x07;
    LATE=0;
    PORTE=0;
      
}
void conf_ADC(void){
    ADCON0=0b00000001;
    ADCON1=0b00000010;
}


void conf_PWM(void){
     PR2=166;
    CCPR1L=100;
    CCPR2L=100;
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
    CCP1CON|=lamda;
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
        
        return temp; //kevin
    }
}

