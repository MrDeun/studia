--zadanie 1 - dane osobowe osob urodzonych przed 1987 i posiadaja aktualna pensje i uporzadkowac wedlug plci
select o.* from osoby o, pensje p
    where 
        o.id = p.id_osoby and
        o.data_ur < to_date(1987,'yyyy')
        and (p.do is null or p.do > sysdate)
    order by o.plec
--zadanie 2 - wyswietlic srednia ilosc dni pracy osob zatrudnionych na wydziale fizyki
with zatrud_info as 
(
select z.* from ZATRUDNIENIA z, wydzialy w 
    where w.id = z.id_wydzialy
    and w.nazwa like 'fiz%'
)

select avg( o.do - o.od ) from zatrud_info o;
--zadanie 3 - wyswietlic srednia pensje mezczyzn nieposiadajacy aktualnej pensji
select avg(sysdate - od)  from zatrud_info
    from osoby o, pensje p
    where p.id_osoby = o.id
    and o.plec = 'M'
    and (sysdate > p.do)
--zadanie 4 - wyswietlic dane wydzialu posiadajacego najmniej pracownikow
with liczba_pracownikow as (
select w.id,count(*) as pracownicy
    from wydzialy w, osoby o, ZATRUDNIENIA z
    where 
        z.ID_WYDZIALY = w.id
        and o.id = z.ID_OSOBY
    group by w.id
)

select w.* from WYDZIALY w, liczba_pracownikow prac
    where w.id = prac.id
    and prac.pracownicy = (
        select min(pracownicy) from liczba_pracownikow
    ) and rownum = 1
--zadanie 5 - najmlodzsza osoba na wydziale fizyki
with osoby_fizyka as 
(
    select o.* from osoby o, ZATRUDNIENIA z, WYDZIALY w
        where o.id = z.ID_OSOBY
            and z.ID_WYDZIALY = w.ID
            and w.nazwa like 'fiz%' 
)

select * from osoby_fizyka
where data_ur = (select min(data_ur) from osoby_fizyka)

--zadanie 6 - dane osoby ktora zmienila umowe o prace

with osoba_zmiana AS
(
    select id_osoby, count(*)
        from ZATRUDNIENIA 
        group by id_osoby
        having count(*) > 1
)

select o.* from osoby o, osoba_zmiana oz
    where o.id = oz.id_osoby;

--zadanie 7 - trzy osoby o najkrotszych nazwiskach

select * from OSOBY
order by length(nazwisko)
fetch first 3 rows only;

--zadanie 8 - najstarsza kobieta z kazdego wydzialu
  with kobiety as
    (
        select o.*, w.nazwa from osoby o, ZATRUDNIENIA z, wydzialy w
        where o.plec = 'K'
            and o.id = z.ID_OSOBY
            and w.id = z.id_wydzialy
    )

    select * from kobiety
    where nazwa like 'mat%'
    and data_ur = (
        select min(data_ur)
        from kobiety
        where nazwa like 'mat%'
    )

UNION ALL

    select * from kobiety
    where nazwa like 'fiz%'
    and data_ur = (
        select min(data_ur)
        from kobiety
        where nazwa like 'fiz%'
    )

UNION ALL

    select * from kobiety
    where nazwa like 'bio%'
    and data_ur = (
        select min(data_ur)
        from kobiety
        where nazwa like 'bio%'
    )

UNION ALL

    select * from kobiety
    where nazwa like 'info%'
    and data_ur = (
        select min(data_ur)
        from kobiety
        where nazwa like 'info%'
    )

--zadanie 9 - na ktorym wydziale pracuje obecnie najmniej mezczyzn

--zadanie 10 - roznica miedzy najdluzsza a najkrotszej pracujaca osoba
with aktualne_zatrudnienia as
 (
     select * from ZATRUDNIENIA 
        where do is null 
         or sysdate < do
 )

select ( (max(od) - min(od)) / 365 ) as roznica_w_latach from aktualne_zatrudnienia   


--zadanie 11 - osoby ktore zostaly zatrudnione po urodzinach najstarszego szefa

--zadanie 12 - w ktorym miesiacu rozwiazano umowy z najwieksza iloscia osob

with contract_ends_month as 
(
    select  from zatrudnienia z 
)
