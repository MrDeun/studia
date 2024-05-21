$regfile = "m8def.dat"
$crystal = 8000000

Config Pind.0 = Output
waitms 100
Do Portd.0
waitms 100
Reset portd.0

loop
end