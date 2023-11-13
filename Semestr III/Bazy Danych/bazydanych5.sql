--1 srednia liczba dni pracy na kazdym wydziale (?)
select  w.nazwa,
        avg(sysdate-z.od)
    from wydzialy w, zatrudnienia z
    where w.id=z.id_wydzialy and (z.do is null or z.do>sysdate)
    group by w.nazwa
    order by w.nazwa;
--2 Suma dni pracy wszytkich pracowników
select z.id_osoby,
    sum(case
            when z.do<sysdate then (z.do-z.od)
            else (sysdate-z.od)
        end)
    from zatrudnienia z
    group by z.id_osoby;

--3 Srednia pensja dla osob kazdej plci
select o.plec,avg(p.pensja)
    from osoby o, pensje p
    where p.id_osoby=o.id
    group by o.plec
--4 Podac wiek najstarszego szefa
select max(floor((sysdate-o.data_ur)/365)) 
    from osoby o, wydzialy w 
    where w.szef==o.id;
--5 Podac najstarszy wiek osob z poszegolnych wydzialow
select w.nazwa, max(round((sysdate-o.data_ur)/365)) as age
  from osoby o, wydzialy w, zatrudnienia z
  where o.id=z.id_osoby and w.id=z.id_wydzialy
  group by w.nazwa;

--6 Najmniejsze pensje dla osob kazdej plci
select o.plec, min(p.pensja)
    from osoby o, pensje p
    where o.id = p.id_osoby
    group by o.plec


--7 Najdluzszy okres pracy osob kazdej plci 
--  sposrod osob posiadajacych pensje
select o.plec, 
max(case
        when z.do<sysdate then ((z.do-z.od)/365)
        when z.do>sysdate then ((sysdate - z.od)/365)
        when z.do is null then ((sysdate - z.od)/365)
    end)
    from osoby o, zatrudnienia z, pensje p
    where o.id=z.id_osoby and (p.pensja is not null or p.do>sysdate) and o.id=p.id_osoby
    group by o.plec;
