$REGFILE = "m8def.dat"
$crystal = 8000000

config pinb.1 = Output
config pinb.2 = Output

config timer1 = pwm, pwm = 8, Compare A pwm = clear up, compare b pwm = clear down, prescale = 1

Dim I as Byte

Do
   For I = 0 to 255
      Pwm1a = I
      Pwm1b = I
      waitms 4
   Next I
   For I = 255 to 0 step -1
      Pwm1a = I
      Pwm1b = I
      waitms 4
   Next I
Loop
End