//..................librerias......................................................................................
#include <xc.h>
#include <stdio.h>

//....................conf_fusibles................................................................................
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)

#define diametro 70
#define minimo 4
#define maximo 35
#define busqueda 0
#define ataque 1
#define defensa 2
#define rangoPiso 220

#define _XTAL_FREQ 4000000
#define EN RE2
#define RS RE0
#define bus LATD



//..............variables globales y prototipos de funcion.........................................................

unsigned char buffer[40]; //Variables LCD
unsigned int num = 65530; //Variables LCD
unsigned char estado = 0;
unsigned char A = 0, sensorDerecha = 0, sensorIzquierda = 0, sensorAdelante = 0, IN1 = 0, IN2 = 0, IN3 = 0, IN4 = 0;
unsigned int ultrasonidoCentro = 0, ultrasonidoDerecha = 0, ultrasonidoIzquierda = 0;


// variables ADC
unsigned int lec = 0;
int res_0 = 0, res_1 = 0, res_2 = 0; // Vvariables ADC
float vol = 0;

void conf_puertos(void); //Fubciones LCD
void ini_LCD(void); //Fubciones LCD
void enable(void); //Fubciones LCD
//......................................FuncionesMotores ....................................
void GiroDerecha(void);
void GiroIzquierda(void);
void Adelante(void);
void Parar(void);
void GiroBusqueda(void);
void GiroAtras(void);
//...................LCD............................................
void dato_LCD(unsigned char dato); //Fubciones LCD
void ins_LCD(unsigned char dato); //Fubciones LCD
void write_LCD(unsigned char tam); //Fubciones LCD

void conf_ADC(void); // Fubciones ADC
unsigned int conv_ADC(unsigned char canal); // Fubciones ADC


void conf_PWM(void); //PWM
void duty_1(unsigned char dc); //PWM
void duty_2(unsigned char dc); //PWM

void conf_TIMER0(void); //Ultrasonido
unsigned int ultrasonido0(void); //Ultrasonido
unsigned int ultrasonido1(void); //Ultrasonido
unsigned int ultrasonido2(void); //Ultrasonido

//Funciones SensorPiso
unsigned char SensorDerecha(void); // Sensor piso
unsigned char SensorIzquierda(void); // Sensor piso
unsigned char SensorAdelante(void);

//..............codigo principal................................................................

void main(void) {
    //.........................conf perifericos.................................................
    conf_puertos();
    conf_PWM();
    conf_TIMER0();

    ini_LCD(); //inicializa la LCD

    write_LCD(sprintf(buffer,"BY ORDER OF THE ")); 
        
    ins_LCD(192);
    
    write_LCD(sprintf(buffer,"PEAKY BLINDER"));
    __delay_ms(5000);
     ins_LCD(1);

    conf_ADC();


    //.........................bucle.............................................................
    while (1) {

             


            




/*
   
           sensorAtras = SensorAtras();
            sensorDerecha = SensorDerecha();
            sensorIzquierda = SensorIzquierda();

             ins_LCD(192);
            write_LCD(sprintf(buffer, "pd:%1u pi:%1u pa:%1u", sensorDerecha, sensorIzquierda, sensorAtras));
            

            if(sensorAtras==1 && sensorDerecha==0 && sensorIzquierda==0)
                {
                
                GiroDerecha();
                __delay_ms(500);
                GiroAtras();
                __delay_ms(2000);
                
                
                
                
                }
                
               



                if(sensorDerecha==1  && sensorAtras==0 &&  sensorIzquierda==0)
                {
                
                GiroIzquierda();
                __delay_ms(900);
                GiroAtras();
                __delay_ms(1000);
                
                
                
                }
                
                

                 if(sensorIzquierda==1 && sensorDerecha==0 && sensorAtras==0)
                {
                
                GiroDerecha();
                __delay_ms(900);
                GiroAtras();
                __delay_ms(1000);
                
                
                
                }


                if(sensorIzquierda==1 && sensorDerecha==1 && sensorAtras==0)
                {
                
                Adelante();
                
                
                
                
                }
                
              */
        



/*
        
                ultrasonidoCentro = ultrasonido0();
                ultrasonidoDerecha = ultrasonido1();
                ultrasonidoIzquierda = ultrasonido2();

                ins_LCD(128);
                write_LCD(sprintf(buffer, "ui%2u uc%2u ud%2u", ultrasonidoIzquierda, ultrasonidoCentro, ultrasonidoDerecha));
        
                if(ultrasonidoCentro < ultrasonidoDerecha && ultrasonidoCentro < ultrasonidoIzquierda){

                    ins_LCD(192);
                    write_LCD(sprintf(buffer,"Adelante        "));
                    Adelante();

                }else{
             
                    ins_LCD(192);
                    write_LCD(sprintf(buffer,"izquierda        "));
                    GiroIzquierda();

                }
               */
        

        
           /*
            ultrasonidoCentro = ultrasonido0();
            ultrasonidoDerecha = ultrasonido1();
            ultrasonidoIzquierda = ultrasonido2();
            sensorAtras = SensorAtras();
            sensorDerecha = SensorDerecha();
            sensorIzquierda = SensorIzquierda();

            ins_LCD(128);
            write_LCD(sprintf(buffer, "ui%2u uc%2u ud%2u", ultrasonidoIzquierda, ultrasonidoCentro, ultrasonidoDerecha));
            
            ins_LCD(192);
            write_LCD(sprintf(buffer, "pd:%1u pi:%1u pa:%1u", sensorDerecha, sensorIzquierda, sensorAtras));
    

          
            if (sensorDerecha || sensorAtras || sensorIzquierda) {

                ins_LCD(192);
                write_LCD(sprintf(buffer,"Parar           "));
                Parar();
                //break;

            }

            if (ultrasonidoCentro < ultrasonidoDerecha && ultrasonidoCentro < ultrasonidoIzquierda) {

                ins_LCD(192);
                write_LCD(sprintf(buffer,"Adelante        "));
                Adelante();
                __delay_ms(2000);
                //break;

            }
            else if (ultrasonidoDerecha < ultrasonidoIzquierda) {

                ins_LCD(192);
                write_LCD(sprintf(buffer,"Derecha         "));

                GiroDerecha();

            } else {

                ins_LCD(192);
                write_LCD(sprintf(buffer,"Izquierda       "));
                GiroIzquierda();
            }

*/
        //..................Busqueda......................................................................
            

        while (estado == busqueda) {
            
            
            
           
                
            
            
            ultrasonidoCentro = ultrasonido0();
            ultrasonidoDerecha = ultrasonido1();
            ultrasonidoIzquierda = ultrasonido2();
            sensorAdelante = SensorAdelante();
            sensorDerecha = SensorDerecha();
            sensorIzquierda = SensorIzquierda();

            
            ins_LCD(128);
            write_LCD(sprintf(buffer, "ud%2u uc%2u ui%2u ",ultrasonidoDerecha,ultrasonidoCentro,ultrasonidoIzquierda));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "pd:%1u pi:%1u pa:%1u", sensorDerecha, sensorIzquierda, sensorAdelante));
            
            
           
            
            
            if (sensorDerecha || sensorAdelante || sensorIzquierda) {

                
                Parar();

                
                estado = defensa;    
                
                
                
                break;

            }

            if ((ultrasonidoCentro < ultrasonidoDerecha) && (ultrasonidoCentro < ultrasonidoIzquierda)) {

                
                
                Parar();
               
                estado = ataque;
                
                
                break;

            }

            if(ultrasonidoDerecha < ultrasonidoIzquierda)

                {
                   //ins_LCD(192);
                   //write_LCD(sprintf(buffer,"Derecha                                         ")); 
                   GiroDerecha();

                }
             else if (ultrasonidoDerecha > ultrasonidoIzquierda) 
            {

                
                //ins_LCD(192);
                //write_LCD(sprintf(buffer,"Izquierda                                              "));
                GiroIzquierda();
                        
                

            } 
            
            else 
            
            {
                //ins_LCD(192);
                //write_LCD(sprintf(buffer,"Derecha                                         ")); 
                GiroBusqueda();
                
                
                
    
            }
            
            
        }

        
        

        //************************ATAQUE*******************************************************
        
        while (estado == ataque)
        {

           
            Adelante();
            

            ultrasonidoCentro = ultrasonido0();
            
            sensorAdelante = SensorAdelante();
            sensorDerecha = SensorDerecha();
            sensorIzquierda = SensorIzquierda();

            ins_LCD(128);
            write_LCD(sprintf(buffer, "ud%2u uc%2u ui%2u ",ultrasonidoDerecha,ultrasonidoCentro,ultrasonidoIzquierda));
            ins_LCD(192);
            write_LCD(sprintf(buffer, "pd:%1u pi:%1u pa:%1u", sensorDerecha, sensorIzquierda, sensorAdelante));

           
            

            

            if (sensorAdelante || sensorDerecha || sensorIzquierda) {
                Parar();
                estado=defensa;
                break;

            }

            

            

            if (ultrasonidoCentro > maximo) {
                Parar();
                estado=busqueda;
                break;

            }

            

         }  
         
      
//********************************************defensa*********************************************
          
            while (estado == defensa) {

                
                
        
            sensorAdelante = SensorAdelante();
            sensorDerecha = SensorDerecha();
            sensorIzquierda = SensorIzquierda();

            
            ins_LCD(192);
            write_LCD(sprintf(buffer, "pd:%1u pi:%1u pa:%1u", sensorDerecha, sensorIzquierda, sensorAdelante));

         if(sensorAdelante==1 && sensorDerecha==0 && sensorIzquierda==0)
                {


                GiroAtras();
                __delay_ms(1000);
                GiroDerecha();
                __delay_ms(500);
                
                break;
                
                
                
                }
                
               



                if(sensorDerecha==1  && sensorAdelante==0 &&  sensorIzquierda==0)
                {
                
                GiroIzquierda();
                __delay_ms(900);
                GiroAtras();
                __delay_ms(1000);
                break;
                
                
                }
                
                

                 if(sensorIzquierda==1 && sensorDerecha==0 && sensorAdelante==0)
                {
                
                GiroDerecha();
                __delay_ms(500);
                GiroAtras();
                __delay_ms(1000);
                break;
                
                
                }


                if(sensorIzquierda==1 && sensorDerecha==1 && sensorAdelante==0)
                {
                
                Adelante();
                __delay_ms(1000);
                  break;
                
            }

              if (sensorAdelante==1 && sensorIzquierda==1 && sensorDerecha==0 )
            {
                Adelante();
                __delay_ms(1000);
                GiroIzquierda();
                __delay_ms(800);
                Adelante();
                __delay_ms(800);
                break;
            }



             if (sensorAdelante==1 && sensorIzquierda==0 && sensorDerecha==1 )
            {
                Adelante();
                __delay_ms(1000);
                GiroDerecha();
                __delay_ms(700);
                Adelante();
                __delay_ms(700);
                break;
            }

               if (sensorIzquierda==0 && sensorDerecha==0 && sensorAdelante==0)
            {
                Parar();
                estado = busqueda;
                break;
            }


            
/*
            if(sensorAtras==1 )
                {
                
                GiroDerecha();
                __delay_ms(500);
                GiroAtras();
                __delay_ms(2000);
                
                
                
                }
                
                else
                {
                Parar();
                estado = busqueda;
                break;
                }



                if(sensorDerecha==1 )
                {
                
                GiroIzquierda();
                __delay_ms(700);
                GiroAtras();
                __delay_ms(1000);
                
                
                
                }
                
                else
                {
                Parar();
                estado = busqueda;
                break;
                }

                 if(sensorIzquierda==1 )
                {
                
                GiroDerecha();
                __delay_ms(700);
                GiroAtras();
                __delay_ms(1000);
                
                
                
                }
                
                else
                {
                Parar();
                estado = busqueda;
                break;
                }

                
                
        
       
            if(sensorAtras== 0 && sensorDerecha==0 && sensorIzquierda==0)
                {
                ins_LCD(192);
                write_LCD(sprintf(buffer, "DEFENSA Paro           "));
                Parar();
                estado = busqueda;
                break;
                
                }

            

            if (sensorDerecha==1 && sensorIzquierda==0 && sensorAtras==0)
            {
            ins_LCD(192);
             write_LCD(sprintf(buffer,"Izquierda                                              "));
             GiroIzquierda();
             
            }

            if  (sensorIzquierda==1 && sensorDerecha==0  && sensorAtras==0)
            {
            ins_LCD(192);
            write_LCD(sprintf(buffer,"Derecha                                         "));
             GiroDerecha();
        
            }

            if (sensorAtras==1 && sensorDerecha==0 && sensorIzquierda==0 )
            {
            ins_LCD(192);
            write_LCD(sprintf(buffer,"Fuera                                         "));
            GiroDerecha();
            
            }

            if (sensorAtras==1 && sensorIzquierda==1 && sensorDerecha==0 )
            {
            ins_LCD(192);
            write_LCD(sprintf(buffer,"RUTINA DERE                                      "));
            GiroDerecha();
            
            }


            if (sensorDerecha==1 && sensorIzquierda==1 && sensorAtras==0)
            {
            ins_LCD(192);
            write_LCD(sprintf(buffer,"RUT ATRAS                                        "));
            Adelante();
            }

            if (sensorAtras==1 && sensorDerecha==1 && sensorIzquierda==0)
            {
            ins_LCD(192);
            write_LCD(sprintf(buffer,"RUT IZQ                                        "));
            GiroAtras();
            }

            
            

           
            
            

            else
            {
                estado=defensa;
            }
            
*/
            
           
            
    
            
            
            

            
            




            
                
            
            
                
                 
            }
        
            
            
        
            }
            
            
        }

        
        


    



//...............................Funciones............................................................

void conf_puertos(void) {



    TRISD = 0x00; // puerto D de salida
    LATD = 0; // limpia puerto D
    PORTD = 0; // limpia puerto D

    TRISE = 0x00; // puerto E de salida
    LATE = 0x00; // Limpia puerto 
    PORTE = 0x00; // Limpia puerto
    ADCON1 = 0x06; //Puerto E digital

    TRISB = 0b00101010; //pares salida impares entrada para sensores   
    LATB = 0; // limpia puerto B
    PORTB = 0; // limpia puerto B

    TRISC = 0X00; //Puerto C de salida
    LATC = 0; //Limpia puerto C
    PORTC = 0; //Limpia puerto C

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

    bus = 0b00001100; // display on/off control - LCD on - cursor on - blink off
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

void conf_ADC(void) {
    ADCON0 = 0b00000001;
    ADCON1 = 0b00000010;
}

unsigned int conv_ADC(unsigned char canal) {
    unsigned int temp = 0;

    if (canal > 7) {
        return 0;
    } else {
        canal <<= 3;
        ADCON0&=0xC7;
        ADCON0 |= canal;
        __delay_us(50);

        GO = 1;
        while (GO == 1) {
        }
        temp = ADRESH;
        temp <<= 2;
        temp |= ADRESL >> 6;

        return temp;

    }
}

void conf_PWM(void) {
    PR2 = 124;
    CCPR1L = 0;
    CCPR2L = 0;
    T2CON = 0b00000101;
    CCP1CON = 0b00001100;
    CCP2CON = 0b00001100;
}
//...........................Motores.............................................

void GiroDerecha(void) {

    LATC = 0b00110000;
    duty_1(40);
    duty_2(20);



}

void GiroBusqueda(void) 
{

    LATC = 0b00101000;
    duty_1(40);
    duty_2(0);
}

void GiroIzquierda(void) {

    LATC = 0b01001000;
    duty_1(40);
    duty_2(20);



}

void Adelante(void) 

{

    LATC = 0b00101000;
    duty_1(60);
    duty_2(60);

}
void GiroAtras(void)

{
     LATC = 0b01010000;
    duty_1(40);
    duty_2(40);
}

void Parar(void) {

    conf_PWM();
    LATC = 0b001111000;
    duty_1(50);
    duty_2(50);

}

void duty_1(unsigned char dc) {
    unsigned int lamda = 0;

    lamda = dc;
    lamda *= 5;
    CCPR1L = lamda >> 2;
    lamda <<= 4;
    lamda &= 0x30;
    CCP1CON &= 0xCF;
    CCP1CON |= lamda;
}

void duty_2(unsigned char dc) {
    unsigned int lamda = 0;

    lamda = dc;
    lamda *= 5;
    CCPR2L = lamda >> 2;
    lamda <<= 4;
    lamda &= 0x30;
    CCP2CON &= 0xCF;
    CCP2CON |= lamda;
}

void conf_TIMER0(void) {
    T0CON = 0b00001000; //apagado, 16 bits, reloj interno, no preescaler
}

unsigned int ultrasonido0(void) {
    unsigned int timerValue = 0;
    unsigned char timerLow = 0;

    TMR0H = 0;
    TMR0L = 0;

    RB0 = 1;
    __delay_us(10);
    RB0 = 0;

    while (RB1 == 0);
    TMR0ON = 1;
    while (RB1 == 1);
    TMR0ON = 0;

    timerLow = TMR0L;
    timerValue = TMR0H;

    timerValue = (timerValue << 8) + timerLow;
    timerValue /= 58;


    
 if (timerValue > 70)
    {
        timerValue = 70;
    }
    
    if (timerLow < 4)
    {
        timerLow = minimo;
    }
 

    return timerValue;
}

unsigned int ultrasonido1(void) {
    unsigned int timerValue = 0;
    unsigned char timerLow = 0;

    TMR0H = 0;
    TMR0L = 0;

    RB2 = 1;
    __delay_us(10);
    RB2 = 0;

    while (RB3 == 0);
    TMR0ON = 1;
    while (RB3 == 1);
    TMR0ON = 0;

    timerLow = TMR0L;
    timerValue = TMR0H;

    timerValue = (timerValue << 8) + timerLow;
    timerValue /= 58;


    
 if (timerValue > 70)
    {
        timerValue = 70;
    }
    
    if (timerLow < 4)
    {
        timerLow = minimo;
    }
 

    return timerValue;
}

unsigned int ultrasonido2(void) {
    unsigned int timerValue = 0;
    unsigned char timerLow = 0;

    TMR0H = 0;
    TMR0L = 0;

    RB4 = 1;
    __delay_us(10);
    RB4 = 0;

    while (RB5 == 0);
    TMR0ON = 1;
    while (RB5 == 1);
    TMR0ON = 0;

    timerLow = TMR0L;
    timerValue = TMR0H;

    timerValue = (timerValue << 8) + timerLow;
    timerValue /= 58;


    
 if (timerValue > 70)
    {
        timerValue = 70;
    }
    
    if (timerLow < 4)
    {
        timerLow = minimo;
    }
 

    return timerValue;
}

//Sensor de Piso 

unsigned char SensorDerecha(void) {

    lec = conv_ADC(0);
    vol = lec * 0.0048;
    if (lec < rangoPiso) {
        sensorDerecha = 1;
    } else {
        sensorDerecha = 0;
    }

}

unsigned char SensorIzquierda(void) {

    lec = conv_ADC(2);
    vol = lec * 0.0048;
    if (lec < rangoPiso) {
        sensorIzquierda = 1;
    } else {
        sensorIzquierda = 0;
    }
}

unsigned char SensorAdelante(void) {

    lec = conv_ADC(1);
    vol = lec * 0.0048;
    if (lec < rangoPiso) {
        sensorAdelante = 1;
    } else {
        sensorAdelante = 0;
    }
}