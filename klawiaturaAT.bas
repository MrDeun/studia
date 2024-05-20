$regfile = "m8def.dat"
$crystal = 8000000

Config Keyboard = Pinb.2 , Data = Pinb.3 , Keydata = Keydata
Config Lcdpin = Pin , Db4 = Portc.3 , Db5 = Portc.2 , Db6 = Portc.1 , Db7 = Portc.0 , E = Portc.4 , Rs = Portc.5
Dim Kod_kl As Byte

Cls
Do
 Kod_kl = Getatkbd()
 If Kod_kl > 0 Then
  If Kod_kl > 31 And Kod_kl < 127 Then
   Lcd Chr(kod_kl)
  elseif Kod_kl = 130 then
   lcd "UWAGA"
  End If
  If Kod_kl = 44 Then
   Cls
   end if
   If Kod_kl = 13 Then
   Lowerline
  End If
  End If

Loop

End

Keydata:
       'klawisze normalnie - ma³e litery
Data 0 , 0 , 0 , 0 , 0 , 130 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
Data &H5E , 0 , 0 , 0 , 0 , 0 , 0 , 113 , 49 , 0 , 0 , 0 , 122 ,
Data 115 , 97 , 119 , 50 , 0 , 0 , 99 , 120 , 100 , 101 , 52 ,
Data 51 , 0 , 0 , 32 , 118 , 102 , 116 , 114 , 53 , 0 , 0 , 110 ,
Data 98 , 104 , 103 , 121 , 54 , 7 , 8 , 44 , 109 , 106 , 117 , 55 ,
Data 56 , 0 , 0 , 44 , 107 , 105 , 111 , 48 , 57 , 0 , 0 , 46 , 45 ,
Data 108 , 48 , 112 , 43 , 0 , 0 , 0 , 0 , 0 , 0 , 92 , 0 , 0 , 0 ,
Data 0 , 13 , 0 , 0 , 92 , 0 , 0 , 0 , 60 , 0 , 0 , 0 , 0 , 8 , 0 ,
Data 0 , 49 , 0 , 52 , 55 , 0 , 0 , 0 , 48 , 44 , 50 , 53 , 54 , 56 ,
Data 0 , 0 , 0 , 43 , 51 , 45 , 42 , 57 , 0 , 0
       'klawisze z Shift - du¿e litery
Data 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
Data 0 , 0 , 0 , 0 , 0 , 0 , 81 , 33 , 0 , 0 , 0 , 90 , 83 , 65 ,
Data 87 , 34 , 0 , 0 , 67 , 88 , 68 , 69 , 0 , 35 , 0 , 0 , 32 , 86 ,
Data 70 , 84 , 82 , 37 , 0 , 0 , 78 , 66 , 72 , 71 , 89 , 38 , 0 ,
Data 0 , 76 , 77 , 74 , 85 , 47 , 40 , 0 , 0 , 59 , 75 , 73 , 79 ,
Data 61 , 41 , 0 , 0 , 58 , 95 , 76 , 48 , 80 , 63 , 0 , 0 , 0 , 0 ,
Data 0 , 0 , 96 , 0 , 0 , 0 , 0 , 13 , 94 , 0 , 42 , 0 , 0 , 0 , 62 ,
Data 0 , 0 , 0 , 8 , 0 , 0 , 49 , 0 , 52 , 55 , 0 , 0 , 0 , 0 , 48 ,
Data 44 , 50 , 53 , 54 , 56 , 0 , 0 , 0 , 43 , 51 , 45 , 42, 57 , 0 , 0