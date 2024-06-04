$regfile = "m8def.dat"
$crystal = 8000000
$baud = 19200


Dim Krk as Byte
Dim Address as Word
Dim Adrl as Byte, Adrh as Byte
Dim Vl as Byte


print "BASMON Version 1.01"

Do
   Krk = Waitkey()
   If Krk = "T" then
      Print Chr(13)
   Elseif Krk = "W" then
      Address = Waitkey()
      Vl = waitkey()
      Out Address, vl
      Print Chr(13)
   Elseif Krk = "R" then
      Address = waitkey()
      Vl = Inp(Address)
   Elseif Krk = "o" then
      Adrl = waitkey()
      adrh = waitkey()
      Vl = Waitkey()
      Address = Adrh * 256
      Address = Address + Adrl
      Out Address, Vl
      Print Chr(13)
   Elseif Krk = "?" then
      Print "?"
   End if

Loop