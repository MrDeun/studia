select char(ascii(imie1)),length(imie1),char(ascii(nazwisko)),length(nazwisko) from osoby
select replace(plec,'K','Kobieta') as plec || replace(plec,'M','Mezczyzna') as plec from osoby