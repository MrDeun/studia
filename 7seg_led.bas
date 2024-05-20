$regfile = "m8def.dat"
$crystal = 8000000

config portb = output

declare sub wysw7seg(byval C as byte)

DIM i as byte
dim kod_cyf as byte

Kropka alias Portb.7
DO
   Toggle Kropka
   For I = 0 to 15
      call Wysw7Seg(i)
      waitms 500
   next i
loop
end

sub wysw7seg(byval C as Byte)
   if c < 16 then
      Kod_cyf = lookup(c,kody7seg)
      kod_cyf.7 = kropka
      portb = kod_cyf
   else
      portd = portb and &b10000000
   end if
end sub

kody7seg:
data &b00111111,&b00000110,&b01011011,&b01001111,&b01100110,
data &b01101101,&b01111101,&b00000111,&b01111111,&b01101111,&b01110111,
data &b01111100,&b00111001,&b01011110,&b01111001,&b01110001