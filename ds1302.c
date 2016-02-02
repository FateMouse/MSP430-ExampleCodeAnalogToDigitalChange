/*Mcu: msp430 ds1302
  Date:2011.07.09
  POWERED By YuanMingjin
*/

#define DAT_H P1OUT|=BIT1
#define DAT_L P1OUT&=~BIT1
#define CLK_H P1OUT|=BIT0
#define CLK_L P1OUT&=~BIT0
#define RST_H P2OUT|=BIT6
#define RST_L P2OUT&=~BIT6

uchar  time[7]={11,1,10,3,23,59,0};//year week month day hour minute second
uchar write_add[7]={0x8c,0x8a,0x88,0x86,0x84,0x82,0x80};
uchar  read_add[7]={0x8c+1,0x8a+1,0x88+1,0x86+1,0x84+1,0x82+1,0x80+1};
void write_byte(uchar dat)
{
        uchar i;
        for(i=0;i<8;i++)
        {
                CLK_L;
                DAT_L;
                if(dat&BIT0)DAT_H;
                dat>>=1;
                CLK_H;
        }
}
void write(uchar add,uchar dat)
{
        RST_L;
        _NOP();
        CLK_L;
        _NOP();
        RST_H;
        _NOP();
        write_byte(add);
        write_byte(dat);
        RST_L;
        _NOP();
        DAT_H;
        CLK_H;
}
uchar read(uchar add)
{
        uchar i,v;
        RST_L;
        _NOP();
        RST_L;
        _NOP();
        RST_H;
        _NOP();
        write_byte(add);
        for(i=0;i<8;i++)
        {
                P1DIR&=~BIT1;
                v>>=1;
                CLK_L;
                if((P1IN&BIT1)==BIT1)
                v|=0x80;
                CLK_H;
        }
        P1DIR=0xff;
        return v;
}
void set_rtc(void)
{
        uchar i,j;
        for(i=0;i<7;i++)
        {
                j=time[i]/10;
                time[i]=time[i]%10;
                time[i]=time[i]+j*16;
        }
        write(0x8e,0x00);
        for(i=0;i<7;i++)
        {
                write(write_add[i],time[i]);
        }
        write(0x8e,0x80);
}
void read_rtc(void)
{
        char i;
        for(i=0;i<7;i++)
        {
                time[i]=read(read_add[i]);
        }
}
