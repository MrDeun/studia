$regfile = "m8def.dat"
$crystal = 8000000

config portb = output
config pind.0 = output
config pind.1 = output
config pind.2 = output
config pind.3 = output
config timer0 = timer, prescale = 256

declare sub pobr_znak(cyfra as byte)
on timer0 mult_wysw
dim A as byte, B as byte, C as byte, d as byte
dim nr_wysw as byte
dim i as byte
w1 alias portd.0
w2 alias portd.1
w3 alias portd.2
w4 alias portd.3

enable interrupts
enable timer0
load timer0, 125

do
   for i=1 to 10
      a = i
      wait 1
      next i
   for i=1 to 10
      b = i
      wait 1
      next i
   for i=1 to 10
      c = i
      wait 1
      next i
   for i=1 to 10
      d = i
      wait 1
      next i
   wait 5
   a = 0:b=0:c=0:d=0
loop
end

sub pobr_znak(cyfra as byte)
   if cyfra < 10 then
      portb = lookup(cyfra,kody7seg)
   else
      portb = 0
   end if
end sub

mult_wysw:
   load timer0,125
   set w1
   set w2
   set w3
   set w4
   select case nr_wysw
   case 0:
      call pobr_znak(a)
      reset w1
   case 1:
      call pobr_znak(b)
      reset w2
   case 2:
      call pobr_znak(c)
      reset w3
   case 3:
      call pobr_znak(d)
      reset w4
   end select
   incr nr_wysw
   if nr_wysw = 4 then
      nr_wysw = 0
   end if
   return

kody7seg:
data &b00111111,&b00000110,&b01011011,&b01001111,&b01100110,
data &b01101101,&b01111101,&b00000111,&b01111111,&b01101111,&b01110111


