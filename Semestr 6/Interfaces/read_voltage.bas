$regfile = "m8def.dat"
$crystal = 8000000

$baud = 9600

config lcd = 16*2
config portd.0 = Input

dim I as byte
dim iteration as byte
dim Buffer as String*1
Print ":MEAS:VPP? CHAN1";Chr(10);
Do
iteration = 0
Print ":MEAS:VPP? CHAN1";Chr(10);
Do
   I = Ischarwaiting()
Loop until I = 1
For iteration = 0 to 12
   Buffer = Inkey()
   if Buffer = Chr(10) then
   else
        lcd Buffer
   end if
   next iteration
wait 1
cls
Loop
end