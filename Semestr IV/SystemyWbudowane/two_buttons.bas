$regfile = "m8def.dat"
$crystal = 8000000

config pinb.1 = Input
config pinb.2 = input
config pinb.4 = output
config pinb.5 = output

led1 alias portb.5
led2 alias portb.4
S1 alias pinb.2
S2 alias Pinb.1

set portb.1
set portb.2

dim count1 as byte
dim count2 as byte

declare sub print_lcd()

Do
   debounce S1,0,pr1,sub
   debounce S2,0,pr2,sub
Loop
End

pr1:
   Toggle led1
   count1 = count1 + 1
   print_lcd
Return

pr2:
   Toggle led2
   count2 = count2 + 1
   print_lcd
return

sub print_lcd:
   cls
   lcd "1.przycisk: "
   lcd count1
   lowerline
   lcd "2.przycisk: "
   lcd count2
end sub