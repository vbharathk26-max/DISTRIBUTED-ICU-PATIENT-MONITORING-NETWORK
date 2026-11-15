#include <LPC21xx.h>

/*---------delay---------*/

void delay_ms(unsigned char ms)
 {
 T0PR=15000-1;
 T0PC=0;
 T0TC=0;
 T0TCR=1;
 while(T0TC<ms);
 T0TCR=0;
 }
 
 
 /* ------uart0_init------ */
 
void uart0_init(unsigned int baud)
{
	unsigned int result=0, pclk;
		
	if(VPBDIV==0x0)
		pclk=15000000;

	else if (VPBDIV==0x01)
		pclk=60000000;

	else if (VPBDIV==0x02)
		pclk=30000000;

	result=pclk/(16*baud);
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=0x03;
}



/*------ uart0_tx ------  */

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}



/*------ uart0_rx ------  */

#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
	while(RDR==0);
	return U0RBR;
}


/* ------uart0_tx_string ------  */

void uart0_tx_string(char *ptr)
{
	while(*ptr!=0)
	{
		uart0_tx(*ptr);
		ptr++;
	}
}


/*------ uart0_intger------  */

void uart0_integer(int num)
{
	int a[10],i=0;
	if(num==0)
	{
		uart0_tx('0');
		return;
	}
	if(num<0)
	{
		num=-num;
		uart0_tx('-');
	}
	while(num>0)
	{
		a[i]=num%10+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
}


 
