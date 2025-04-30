$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config portc = output
dim I as byte
dim d as byte
dim H as byte
Deflcdchar 7,21,21,10,10,21,21,10,10' replace [x] with number (0-7)
do
   lcd "Hello world!"
   waitms 50
   cls
loop
end