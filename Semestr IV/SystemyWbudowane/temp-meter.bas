$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config 1wire = portb.0

declare sub odcz_temp
dim Temperatura(2) as byte

deflcdchar 0,7,5,7,32,32,32,32,32

Do
   call odcz_temp
   cls
   if Temperatura(2) = 0 then
      lcd "Temp: ";Temperatura(1);Chr(0);"C"
   Else
      lcd "Temp: -";Temperatura(1);Chr(0);"C"
   end if
loop
end

sub odcz_temp

   1wreset
   1wwrite &hcc
   1wwrite &h44
   waitms 750

   1wreset
   1wwrite &hcc
   1wwrite &hbe
   Temperatura(1) = 1wread(2)
   1wreset
   if err = 1 then
      cls
      lcd "brak ukladu"
      do
      loop
   end if
   if Temperatura(2) > 0 Then
    Temperatura(1) = 256 - Temperatura(1)
   end if
   Temperatura(1) = Temperatura(1)/2
end sub
