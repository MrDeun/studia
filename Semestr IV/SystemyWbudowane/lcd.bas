$regfile = "m8def.dat"
$crystal = 8000000

config lcd = 16 * 2
config portc = output
dim I as byte
dim d as byte
dim H as byte
Deflcdchar 7,21,21,10,10,21,21,10,10' replace [x] with number (0-7)
do
   for h = 0 to 1
      for d = 0 to 15
         for i = 0 to 15
            if i = d then
               lcd chr(7)
            else
               lcd "x"
            end if
         next
      waitms 500
      next
      lowerline
   next
   cls
   home upper
loop
end