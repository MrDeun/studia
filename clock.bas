$regfile = "m8def.dat"
$crystal = 8000000

config pinb.1 = input
config pinb.2 = input
config lcd = 16*2
config timer1 = timer, prescale=256

declare sub wysw_czas
on timer1 odmierz_1s

dim sekundy as byte
dim minuty as byte
dim godziny as byte
dim nowa_w as byte
dim wart_bcd as byte

s1 alias pinb.2
s2 alias pinb.1

enable interrupts
enable timer1
counter1 = 34286
set nowa_w
set portb.1
set portb.2

Do
   call wysw_czas
   if s1 = 0 then
      waitms 25
      if s1 = 0 then
         incr minuty
         sekundy = 0
         if minuty = 60 then
            minuty = 0
         end if
         set nowa_w
         call wysw_czas
         waitms 200
      endif
   endif
   if s2 = 0 then
      waitms 25
      if s2 = 0 then
         incr godziny
         if godziny = 24 then
            godziny = 0
         end if
         set nowa_w
         call wysw_czas
         waitms 200
      endif
   endif
Loop
End

sub wysw_czas
   if nowa_w = 1 then
      cls
      wart_bcd = Makebcd(godziny)
      Lcd Bcd(wart_bcd) ; ":"
      wart_bcd = Makebcd(minuty)
      Lcd Bcd(wart_bcd) ; ":"
      wart_bcd = Makebcd(sekundy)
      Lcd Bcd(wart_bcd)
      reset nowa_w
   end if
end sub

Odmierz_1s:
   Counter1 = Counter1 + 34286
   Incr Sekundy
   Set Nowa_w
   if sekundy = 60 then
      sekundy = 0
      incr minuty
      if minuty = 60 then
         minuty = 0
         incr godziny
         if godziny = 24 then
            godziny =0
         end if
      end if
   end if
return