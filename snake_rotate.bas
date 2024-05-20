$regfile = "m8def.dat"
$crystal = 8000000

Config Portb = Output
PortB = &B01010101

Do
   Rotate PORTB, Left
   'Waitms 200
Loop
End