$regfile = "m8def.dat"
$crystal = 8000000
$baud = 9600

dim I as byte

I = 243
do
print "bascom"
wait 2
print "wartosc w dec: ";I
wait 2
print "wartosc w hex: ";hex(I)
wait 2
print "wartosc w bin: ";bin(I)
print ""
wait 5
loop
end