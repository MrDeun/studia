--Prosze wypisac dane z dwoch tablic: osoby i pensje w jednym zapytaniu select
select * from union(osoby,pensje)
-- Wybrac nazwisko i wysokosc pensji dla kazdej osoby.
select o.nazwisko, p.pensja from osoby o, pensje p where o.id=p.id_osoby
-- Dane osób wraz z wartością pensji dla osób o id = {1,2,5,8}
select o.*,p.pensja from osoby o, pensje p where o.id=p.id_osoby and o.id in (1,2,5,8)
--Imie, nazwisko wraz z AKTUALNA pensja
select o.imie1,o.nazwisko,p.pensja 
from osoby o,pensje p 
where p.do>=sysdate or p.do is not null and o.id=p.id_osoby;
--Osoby aktualnie zatrudnione
select o.* 
from osoby o, zatrudnienia z 
where o.id=z.id_osoby and
(z.do>sysdate or z.do is null)
--osoby aktualnie zatrudnione z wartoscia aktulanej pensji
select o.*, z.do, p.pensja 
from osoby o, pensje p, zatrudnienia z
where
	(o.id=z.id_osoby and o.id=p.id_osoby) 
	and (z.do>sysdate or z.do is null)
	and (p.do>sysdate or p.do is null);
	
--Dane osoby zatrudnionych na wydziale fizyki
select o.* 
from osoby o, wydzialy w
where
	lower(w.nazwa) like 'fiz%'
	and o.id = id.osoby
	and z.id_wydzialy = w.id;
	
-- Nazwisko szefow wydzialu
select o.nazwisko 
from osoby o, wydzialy w
where
	o.id=w.szef;
-- osoby + wartosci pensji dla osob zarabiacych [2000,3500]
select o.*, p.pensja
from osoby o, pensje p
where
	o.id = p.id_osoby
	and (p.pensja >= 2000 and p.pensja <= 3500);
-- wiek kazdej osoby w latach
select floor((sysdate-data_ur)/365) from osoby o;
-- dlugosc zatrudnienia aktualnego

--DO DOMU: srednia liczba dni pracy aktualnych pracowników na poszczególnych wydzialach