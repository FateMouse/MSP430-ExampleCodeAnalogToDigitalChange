#include<msp430x14x.h>
/*一般的1602显示的最多显示80个，那个就是DDRAM
CGROM 就是被预先固化了的，里面有对应的字母和数字编码(160个)直接去就行了
CGRAM就是用户自己定义的图像*/
#define uint  unsigned int
#define uchar unsigned char

#define RW_H P6OUT|=BIT4
#define RW_L P6OUT&=~BIT4
#define RS_H P6OUT|=BIT2
#define RS_L P6OUT&=~BIT2
#define EN_H P6OUT|=BIT3
#define EN_L P6OUT&=~BIT3

#define LDATA P4OUT
uchar  hz[]={
 	 0x04,0x0f,0x12,0x0f,0x0a,0x1f,0x02,0x02,//year
	 0x0f,0x09,0x0f,0x09,0x0f,0x09,0x12,0x11,//month
	 0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00,//day

         0x00,0x07,0x05,0x07,0x05,0x07,0x00,0x00,
         0x02,0x1f,0x02,0x0a,0x02,0x02,0x06,0x00,
	};

void delay1(uint z)
{
    while(z--);
}

void lcd_w(uchar cmd,uchar data)
{
    if(cmd)  RS_H;//data rs=1写数据
    else      RS_L;//rs=0写指令
    RW_L;//rw
    LDATA=data;
    EN_H;//en
    delay1(100);
    EN_L;

}
void lcd_xy(uchar x,uchar y)
{
  if(y==0)lcd_w(0,0x80|x);
  if(y==1)lcd_w(0,0xc0|x);
}
void lcd_init(void)
{
    P6DIR=BIT2|BIT3|BIT4;
    P4DIR=0xff;
    lcd_w(0,0x38);
    lcd_w(0,0x0c);
    lcd_w(0,0x01);
    lcd_w(0,0x06);
}
void Print(uchar *str)
{
    while(*str) lcd_w(1,*str++);
}

void Write_CGRAM(uchar *p)
{
        uchar i,j,k;
        uchar temp=0x40;
        for(j=0;j<8;j++)
        {
                for(i=0;i<8;i++)
                {
                        lcd_w(0,temp+i);
                        lcd_w(1,p[k]);
                        k++;
                }
                temp+=8;
        }
}
void LCD_DisPlay(uchar i,uchar j,uchar ch)
{
         uchar addr;
         if(0==i) addr =0x80+j;
         else addr=0xc0+j;
         lcd_w(0,addr);
         lcd_w(1,ch);
}

