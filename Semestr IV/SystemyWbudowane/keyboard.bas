$regfile = "m8def.dat"
$crystal = 8000000

config pinb.0 = Input
config pinb.1 = Input
config pinb.2 = Output
config pinb.3 = Output
config lcd = 16*2
config timer0 = timer, prescale = 1024

on timer0 mult_kl

dim temp1 as byte
dim temp2 as byte
dim Przycisk as byte
dim I as byte

W1 alias pinb.0
W2 alias pinb.1
Kol1 alias portb.2
Kol2 alias portb.3

enable interrupts
enable timer0
load timer0,200

set portb.0
set portb.1
set Kol1
set Kol2

Do
   Cls
   lcd przycisk
   waitms 100
Loop
End


mult_kl:
   Load timer0,200
   For i=1 to 2
      if i = 1 then
         reset kol1
      else
         set kol1
         reset kol2
      end if

      if w1= 0 or w2 = 0 then
         temp1 = pinb and &B00000011
         exit for
      else
         temp1 = 0
      end if
   next i

   if temp2 = temp1 then
      przycisk = temp1
      if i = 2 then
         przycisk = przycisk + 2
      end if
   else
      temp2 = temp1
   end if
   set kol1
   set kol2
return