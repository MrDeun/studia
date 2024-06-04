$regfile = "m8def.dat"
$crystal = 8000000
$baud = 19200

config 1wire = portb.0
config PORTB.1 = output
declare sub odcz_temp

dim t(2) as byte
dim cmd as byte
dim znak as string * 1
dim tempst as integer
dim tempdz as integer

do
   call odcz_temp
   cmd = inkey()
   if cmd = "G" then
      print tempst ; "." ; tempdz;
      print chr(13);chr(10);
   end if
loop
end

sub odcz_temp
1wreset
1wwrite &hcc
1wwrite &h44
waitms 750
1wreset
1wwrite &h44
waitms 750
1wreset
1wwrite &hcc
1wwrite &hbe
T(1) = 1wread(2)
1wreset

if T(2) > 0 then
   t(1) = 256 - t(1)
   znak = "-"
else
   znak = "+"
end if

tempst = t(1)/2
tempdz = t(1) mod 2
tempdz = 5*tempdz
if t(2) > 0 then
   tempst = 0 - tempst
   reset PORTB.1
else
   set PORTB.1
end if
end sub