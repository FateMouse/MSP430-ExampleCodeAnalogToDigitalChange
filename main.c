#include<msp430x14x.h>
 
#include"lcd1602.h"
 
#define uint unsigned int
 

main()
 
{
 
  unsigned int result,result1;
 
  WDTCTL = WDTPW|WDTHOLD;//�رտ��Ź�
 


  /*--ADC initialization---*/
 
  P6SEL|=0X01;
 
  ADC12CTL0 = ADC12ON+SHT0_15+MSC;
 
  ADC12CTL1 = SHP+CONSEQ_1;//
 
  ADC12MCTL1=INCH_1;
 
  ADC12CTL0 |= ENC;//ת���� ��
 

  lcd_init();
 
  while(1)
 
  {
 
      ADC12CTL0 |= ADC12SC;//��ʼת��
 
      lcd_xy(0,0);
 
      Print("The ADC12 Value:");
 
      while(0==(ADC12IFG&BIT0));//�ȴ�ת�����
 
      _NOP();
 
      result=ADC12MEM0;    //ת�ƽ��
 
      result1=ADC12MEM1;
 
      lcd_xy(0,1);
 
      Print("AD0:");
 
      lcd_w(1,result/1000+'0');
 
      lcd_w(1,result/100%10+'0');
 
      lcd_w(1,result/10%10+'0');
 
      lcd_w(1,result%10+'0');
 
      lcd_xy(8,1);
 
      Print("AD1:");
 
      lcd_w(1,result1/1000+'0');
 
      lcd_w(1,result1/100%10+'0');
 
      lcd_w(1,result1/10%10+'0');
 
      lcd_w(1,result1%10+'0');
 
  }
 
}