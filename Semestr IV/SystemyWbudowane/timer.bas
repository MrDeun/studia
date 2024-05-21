$regfile = "m8def.dat"
$crystal = 8000000

Config PINB.0 = Output
config TIMER0 = Timer, Prescale = 256 '1,8,64,256,1024

On Timer0 Odmierz_1s
Dim Licz_8ms as Byte

Enable Interrupts
Enable Timer0
Load Timer0, 250

Do
Loop
End



Odmierz_1s:

Load timer0,62
Incr Licz_8ms
if Licz_8ms = 67 then
Licz_8ms = 0
Toggle PortB.0
end if
return