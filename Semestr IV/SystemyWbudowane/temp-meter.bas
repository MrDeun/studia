$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config 1wire = portb.0

declare sub odcz_temp
dim TemperaturaC(2) as byte
dim TemperaturaK(2) as integer

deflcdchar 0,7,5,7,32,32,32,32,32

Do
   call odcz_temp
   cls
   if TemperaturaC(2) = 0 then
      lcd "Temp: ";TemperaturaC(1);Chr(0);"C"
      lowerline
      lcd "Temp: ";TemperaturaK(1);chr(0);"K"
   Else
      lcd "Temp: -";TemperaturaC(1);Chr(0);"C"
      lowerline
      lcd "Temp: ";TemperaturaK(1)-TemperaturaC(1);chr(0);"K"
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
   TemperaturaC(1) = 1wread(2)
   1wreset
   if err = 1 then
      cls
      lcd "brak ukladu"
      do
      loop
   end if
   if TemperaturaC(2) > 0 Then
    TemperaturaC(1) = 256 - TemperaturaC(1)
   end if
   TemperaturaC(1) = TemperaturaC(1)/2
   TemperaturaK(1) = TemperaturaC(1) + 273
end sub
