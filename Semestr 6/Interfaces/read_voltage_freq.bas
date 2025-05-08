$regfile = "m8def.dat"
$crystal = 8000000

$baud = 9600

config lcd = 16*2
config portd.0 = Input
config Pinb.1 = Input
config pinb.2 = Input

config PINB.4 = output
config Pinb.5 = output

button1 alias Pinb.2
button2 alias PINB.1



dim I as byte
dim iteration as byte
dim readChar as String*1
dim Buffer as String*12

set Portb.1
set PORTb.2

Print ":MEAS:VPP? CHAN1";Chr(10);
cls
 Lcd "RIGOL Measure"
Do
 Debounce button1, 0, Press1, Sub
 Debounce button2, 0, Press2, Sub
Loop
end

Press1:
   Reset portb.4
   cls
   Print ":MEAS:VPP? CHAN1";Chr(10);
   Do
      I = Ischarwaiting()
   Loop until I = 1
   For I = 0 to 12
      readChar = inkey()
      if readChar = Chr(10) then
      else
      lcd readChar
      end if
   Next I

   lcd "mV"
   wait 1
   Set Portb.4
   Buffer = ""
Return
Press2:
   Reset portb.5
   cls
   Print ":MEAS:FREQ? CHAN1";Chr(10);
  Do
      I = Ischarwaiting()
   Loop until I = 1
   For I = 0 to 12
      readChar = inkey()
      if readChar = Chr(10) then
      else
      lcd readChar
      end if
   Next I
   lcd "Hz"
   wait 1
   Buffer = ""
   Set PORTB.5
Return