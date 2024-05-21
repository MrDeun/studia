
$regfile = "m8def.dat"
$crystal = 8000000

Config PinB.0 = Output

do
'waitms 50
Toggle PORTB.0
loop
End