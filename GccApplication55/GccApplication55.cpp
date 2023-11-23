#include <avr/io.h>
#include <avr/interrupt.h>

int i=0, j=0;
char portStat[3]= {0xEF, 0xDF, 0xBF};
char inputState[3]= {0x01, 0x02, 0x04};
char mass2[3][3]={{0b00000000, 0b00000001, 0b00000010},
				  {0b00000100, 0b00001000, 0b00010000},
				  {0b00100000, 0b01000000, 0b10000000}};		

	ISR(TIMER2_COMP_vect)
	{
		for (i=0; i<3; i++)
		{
			PORTD=portStat[i];
			for (j=0; j<3; j++)
			{
				if (((PIND&inputState[j])==0))
				{
					while((PIND&inputState[j])!=inputState[j]){};
						PORTB=(mass2[i][j]);
				}
			}
		}
	}

int main(void)
{
	PORTD=0xFF;
	DDRD=0xE0;
	
	PORTB=0x00;
	DDRB=0xFF;
	
	ASSR=0x00;
	TCCR2=0x0F;
	TCNT2=0x00;
	OCR2=0xC3;
	
	TIMSK=0x80;
	
    while(1)
    {
        
    }
}