--1) Wypisac datę urodzenia dla kazdej osoby
select data_ur from osoby

--2) Wypisac jedynie rok urodzenia
select extract(year from data_ur) as data_ur from osoby

--3) Wybrać dane osób urodzonych przez rokiem 1980
select * from osoby where extract(year from data_ur)<1980

--4) W wyniku zapytania otrzymujemy	|imie i nazwisko | roznica dlugosci |\
select imie1||' '||nazwisko as "imie i nazwisko",abs(length(imie1)-length(nazwisko)) from osoby;

--5) id osob ktorych sa obecnie zatrudnione
select id_osoby from pensje where do>sysdate or do is null;

--7) wartosci obecnie wyplacanych pensji
select pensja from pensje where do>=sysdate or do is not null

--8) Zliczyc liczbe osob w tabeli osoby
select count(*) as ilosc from osoby;

--9) Zliczyc liczbe wpisow dla kazdej osoby z tabeli pensje
select id_osoby,count(*) from pensje group by id_osoby

--10) uporzadkowac wynik wg liczby wystapien
select id_osoby,count(*) from pensje group by id_osoby order by count(*)

--11 wybrac srednia pensje dla osob => 1 wpisem i pensjach
select id_osoby,avg(pensja) from pensje group by id_osoby having count(*)>1;
---11b uporzadkowac malejaco
select id_osoby,avg(pensja) from pensje group by id_osoby having count(*)>1 order by id_osoby desc;
--12) Dla kazdej osoby wypisac srednia pensje i maks pensja
select id_osoby,max(pensja),avg(pensja) from pensje group by id_osoby order by id_osoby;
--13) id_osob wraz ze srednia pensja dla aktualnie wyplacanych pensji, pogrupowane wh sredniej jedynie dla osob zarabiajacych srednio > 2000
select id_osoby,avg(pensja) from pensje where do>=sysdate or do is not null group by id_osoby having avg(pensja)>2000;
--DOM) Dla kazdej osoby podac kiedy miala 18 lat.