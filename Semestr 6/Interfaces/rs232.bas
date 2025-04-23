$regfile = "m8def.dat"
$crystal = 8000000

Dim I as Byte

I = 243

Do
   Print "Bascom"
   wait 2
   Print "Wartosc I zapisacana w DEC: "; I
   wait 2
   Print "Wartosc I zapisacana w HEx: "; Hex(I)
   wait 2
   Print "Wartosc I zapisacana w BIN: "; Bin(I)
   wait 2
   Print
   wait 5
Loop
End