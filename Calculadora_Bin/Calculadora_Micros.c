
#include <xc.h>
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)
#define _XTAL_FREQ	4000000





#define TMR2_PRESCALE  8


unsigned char A=0, B=0, S=0, PB=0, DESPL1=7, DESPL2=5, decimal=0;
char i;

void conf_puertos(void);
void BCD (void);


void main(void) {
    
    conf_puertos();
    
    while(1){
        
         PB=PORTB;
        S=PORTB;
        A=PB>>4;
        B=PB&0x0F;
        S=PORTA&0x0F;
        
        switch(S){
            
            case 0:
                
                LATD=A+B;
                break;
            
            case 1:
               
                if ((A-B)<=0){
                    
                    LATD=0;
                }else{
                    LATD=A-B;
                }
                
                break;
                
            case 2:
                
                LATD=A*B;
                break;
            
            case 3:
                
                LATD=A/B;
                break;
                
            case 4:
                
                LATD=A&B;
                break;
                
            case 5:
                
                LATD=A|B;
                break;
                
            case 6:
                
                LATD=A^B;            //XOR
                break;
             
            case 7:
                
                LATD= 0X0F&(~(A&B));        //NAND
                                
                break;
                
            case 8:
              
                LATD= 0X0F&(~(A|B));      //NOR
               
                break;
            
            case 9:
                
                LATD= 0X0F&(~(A^B));        //XNOR
              
                break;
            
            case 10:
                
                 //dplazo 7 izquierda de manera rotativa, sin perder los datos.
                LATD=((PORTB << DESPL1) | (PORTB >> (8*sizeof(char)-DESPL1) ) );
                break;
                
            
            
            case 11:
                
                //dplazo 5 derecha de manera rotativa, sin perder los datos.
                LATD=((PORTB >> DESPL2) | (PORTB << (8*sizeof(char)-DESPL2) ) );
                break;
            
            case 12:
                
                
               if((A-B)<0)
                       {
                           
                           LATD= (B-A)|0X80;
                       }
                       else     
                       
                       {
                          LATD= A-B;  
                       }
                
                break;
            
            case 13:
                
                BCD();
                break;
                
            case 14:
            LATD = 0;
                    LATC= 0b00001000;
                    __delay_us(1911.094);
                    LATC= 0;
                    __delay_us(1815.090);
               
                break;
                
            case 15:
                
               LATD = 0;  
               LATC= 0b00001000;
               __delay_us(1431.721215);
                LATC= 0;
                __delay_us(1333.721);
                       break; 
                       
                break;
                
            default:
                LATD=0;
                break;
              
        }
        
    }
    
    return;
}


void conf_puertos(void){
    
   TRISB=0xFF;
    LATD=0;
    PORTB=0;
    
    TRISA=0xFF;
    LATA=0;
    PORTA=0,
    ADCON1=0x06;
    
    TRISD=0x00;
    LATD=0;
    PORTD=0;  
    
    TRISC= 0X00;
    LATC= 0;
    PORTC= 0;
             
}




void BCD(void){
    
    unsigned char decena,unidad,PB2,t;
    t=(A*B);
    unidad=t%10;
    decena=t/10;
    if((t)>99){
        
        LATD=0;
    }
    else{
        /*PB2=PORTD;
        LATD=decena;
        decena=LATD>>4;*/
        //LATD&0X0F=unidad;
        
      LATD=(decena << 4);
      
      LATD=unidad;
    }
    
}