$regfile = "m8def.dat"
$crystal = 8000000
$baud = 19200


dim I as byte
dim znak as string * 1

config portb.0 = output

Do
   input "Podaj wartosc I: ",I
   print "Wartosc I wynosi: ";I
   If I = 1 then
      do
         znak = waitkey()
         print "Odebrano znak: " ; znak
         if znak = "o" then
            toggle PORTb.0
         end if
      loop until znak = "k"
   end if
   if I = 2 then
   do
      I = ischarwaiting()
      print "Flaga zawartosci bufora: ";I
      znak = inkey()
      print "w zmiennej znak jest:  ";znak
      waitms 500
   loop until znak = "k"
   endif

loop
end

