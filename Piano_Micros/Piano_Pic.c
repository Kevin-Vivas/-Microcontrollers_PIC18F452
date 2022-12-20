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
float FRECUENCIA=0;
unsigned char buffer[40];
unsigned int num = 65530;

void conf_puertos(void);
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

//..............codigo principal................................................................

void main(void) {

    //.........................conf perifericos.................................................
    conf_puertos();
    ini_LCD(); //inicializa la LCD

    write_LCD(sprintf(buffer, "PIANO ELECTRICO"));

    ins_LCD(192);

    write_LCD(sprintf(buffer,"SE COMO BETOVEN"));

    __delay_ms(2000);
    ins_LCD(1);
    //.........................bucle.............................................................
    while (1) {


 if (RB0==0) {
            ins_LCD(1);
            FRECUENCIA=261.63;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:DO4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB0==0)        {
            LATC = 0b00000000;

            __delay_us(1912);

            LATC = 0b00010000;
            __delay_us(1898);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            
           
            

            
        }
        
        
        if (RB1==0) {
            ins_LCD(1);
            FRECUENCIA=293.66;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:RE4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB1==0)        {
            LATC = 0b00000000;

            __delay_us(1704);

            LATC = 0b00010000;
            __delay_us(1689);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
        
        
        
        if (RB2==0) {
            ins_LCD(1);
            FRECUENCIA=329.63;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:MI4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB2==0)        {
            LATC = 0b00000000;

            __delay_us(1515);

            LATC = 0b00010000;
            __delay_us(1507);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
        
        
        
        
        if (RB3==0) {
            ins_LCD(1);
            FRECUENCIA=349.23;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:FA4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB3==0)        {
            LATC = 0b00000000;

            __delay_us(1434);

            LATC = 0b00010000;
            __delay_us(1418);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }

        if (RB4==0) {
            ins_LCD(1);
            FRECUENCIA=392.00;
            write_LCD(sprintf(buffer, "NOTAMUSICAL:SOL4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB4==0)        {
            LATC = 0b00000000;

            __delay_us(1275.5113);

            LATC = 0b00010000;
            __delay_us(1265.51023);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
        
        
        if (RB5==0) {
            ins_LCD(1);
            FRECUENCIA=440.00;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:LA4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB5==0)        {
            LATC = 0b00000000;

            __delay_us(1125.3636);

            LATC = 0b00010000;
            __delay_us(1136.3636);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
        
        
        
        if (RB6==0) {
            ins_LCD(1);
            FRECUENCIA=493.88;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:SI4"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB6==0)        {
            LATC = 0b00000000;

            __delay_us(1001);

            LATC = 0b00010000;
            __delay_us(1012.3916);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
        
        
        
        
        if (RB7==0) {
            ins_LCD(1);
            FRECUENCIA=523.25;
            write_LCD(sprintf(buffer, "NOTA MUSICAL:DO5"));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "FREC:%.2fHZ",FRECUENCIA));
            
            while(RB7==0)        {
            LATC = 0b00000000;

            __delay_us(944.5661);

            LATC = 0b00010000;
            __delay_us(955.5661);
            }
            
            
        }
        
        
        else  {
            
            ins_LCD(1);
            write_LCD(sprintf(buffer, ""));
           
            

            
        }
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

    TRISC = 0X00;
    LATC = 0;
    PORTC = 0;

    TRISB = 0xFF;
    LATD = 0;
    PORTB = 0;
    RBPU = 0;
}

//...................ini_LCD....................................

void ini_LCD(void) {
    __delay_ms(20); // delay 20 ms
    bus = 0x30; // VALOR DE INICIALIZACION
    enable();

    __delay_ms(5); // delay 5 ms
    bus = 0x30; // VALOR DE INICIALIZACION
    enable();

    __delay_ms(1); // delay 1 ms
    bus = 0x30; // VALOR DE INICIALIZACION
    enable();

    bus = 0b00111000; // Function set 8 bits - 2 lineas - 5*8
    enable();

    bus = 0b00001000; // display off
    enable();

    bus = 0b00000001; // display clear
    enable();

    bus = 0b00000110; // entry mode set - incrementa la posicion del cursor
    enable();

    bus = 0b00001110; // display on/off control - LCD on - cursor on - blink off
    enable();


}

//...................enable....................................

void enable(void) {
    EN = 1; // enable en alto
    __delay_ms(1);
    EN = 0; // enable en bajo
}

//...................dato....................................

void dato_LCD(unsigned char dato) {
    RS = 1; //RS en 1 (envia dato)
    bus = dato; //dato a publicar 
    enable();
    __delay_ms(2); //tiempo de ejecucion
}

//...................instruccion..................................

void ins_LCD(unsigned char dato) {
    RS = 0; //RS en 0 (envia instruccion)
    bus = dato; //dato a publicar 
    enable();
    __delay_ms(2); //tiempo de ejecucion
}

void write_LCD(unsigned char tam) {

    unsigned char i;

    for (i = 0; i < tam; i++) {
        dato_LCD(buffer[i]);
    }
}
