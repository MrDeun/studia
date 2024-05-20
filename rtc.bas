$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config clock = soft
config date = mdy, separator = /

enable interrupts

Date$ = "08/22/04"
Time$ = "23:59:00"

do
   cls
   lcd time$
   lowerline
   lcd date$
   waitms 100
loop
end