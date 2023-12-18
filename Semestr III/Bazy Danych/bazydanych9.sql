--1) Najstarsza osoba z wydziału na którym średnia pensja jest minimalna
select avg(pensja) from wydzialy,pensje group by wydzialy
--2) Dane osób zatrudnionych na wydziale którego szejem jest najmniej zarabiająca osoba spośród szefów
--3) Dane osób zatrudnionych po 30 tych urodzinach szefa
--4) wyświetlić 2-gą co do wielkości pensję używając with as select
with no_top as (select * from pensje where pensja < max(pensja) )
 select * from no_top