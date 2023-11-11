select substr(imie1,1,1),length(imie1),substr(nazwisko,1,1),length(nazwisko) from osoby;
select imie1, replace(replace(plec, 'M', 'Mezczyzna'), 'K', 'Kobieta') as plec from osoby;