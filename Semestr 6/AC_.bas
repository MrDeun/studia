$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config adc = single, prescaler = auto, reference = avcc

dim Wart_ac as Word
dim V as Single
dim wart_nap as String * 3

Start Adc

Do
   Wart_ac = Getadc(1)
   cls
   lcd Wart_ac
   lowerline
   V = Wart_ac * 0.0049
   Wart_nap = Fusing(V,"#.&&")
   Lcd Wart_nap

   waitms 100

Loop
End