$regfile = "m8def.dat"
$crystal = 8000000

config pinb.1 = input
config lcd = 16 * 2
config 1wire = portb.0




declare sub odcz_temp(czujnik as byte)
declare sub Zapisz_id



dim Temperatura(2) as byte
Dim Id(8) as byte
dim I as byte
dim J as byte
dim K as byte
dim liczba_ukl as byte


S1 alias Pinb.1
deflcdchar 0,7,5,7,32,32,32,32,32

set portb.1
cls

Liczba_ukl = 1wirecount()

If S1 = 0 Then
   lcd "Lib ukladow: " ; Liczba_ukl

   if Liczba_ukl > 0 Then
   Id(1) = 1wsearchfirst()
   For I = 1 To 8
      Writeeeprom Id(i), I
   Next I
End If
   If Liczba_ukl > 1 then
   Id(1) = 1wsearchnext()
   J = 0
   for I = 9 To 16
      Incr J
      Writeeeprom Id(j),I
   Next I
End If
Lowerline
lcd "Prog ok"
Do
Loop
End If

Do
   Home
   For K=1 To Liczba_ukl
      Call Odcz_temp(K)
      if Temperatura(2) = 0 Then
         lcd "Temp" ; K ; ":" ; Temperatura(1) ; chr(0) ; "C"
      else
         lcd "Temp" ; K ; ": -" ; Temperatura(1) ; chr(0) ; "C"
      end if
      Lowerline
      Next K
Loop

End

Sub odcz_temp(czujnik As Byte)
   If Czujnik = 1 then
    For I = 1 To 8
      readeeprom Id(i),I
    Next I
   End if
   If Czujnik = 2 then
    J = 0
    For I = 9 To 16
      Incr J
      readeeprom Id(j),I
    Next I
   End if

   1wreset
   Call Zapisz_id
   1wwrite &H44
   waitms 750
   1wreset
   Call Zapisz_id
   1wwrite &HBE
   Temperatura(1) = 1wread(2)
   1wreset
   If Err = 1 Then
      Cls
      Lcd "Brak ukladu"
      Do
      Loop
   End if
   If Temperatura(2) > 0 then
      Temperatura(1) = 256 - Temperatura(1)
   End if
   if Czujnik = 2 then
      'Temperatura (1) = 16
   end if
   Temperatura(1) = Temperatura(1) /2
End Sub

Sub Zapisz_id
   1wwrite &H55
   For I = 1 to 8
      1wwrite Id(i)
   Next I
End Sub




