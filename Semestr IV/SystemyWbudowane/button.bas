$regfile = "m8def.dat"
$crystal = 8000000


config pinc.0 = input
config pinb.0 = output

set portc.0

DO
if Pinc.0 = 0 then
   toggle portb.0
'else
   'reset portb.0
   waitms 200
end if
LOOP
END