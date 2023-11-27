--1 Dane osób posiadających najkrótsze nazwisko
select o1.* 
  from osoby o1
  where 
    length(o1.nazwisko) = (select min(length(o2.nazwisko)) from osoby o2);
--2 Dane osobowe szefów oraz wysokość pensji
select o.*, p.pensja 
  from osoby o, pensje p
  where 
    o.id in (select w.szef from wydzialy w)
    and o.id = p.id_osoby
    and p.do is null;


--3 Wydzial o najdluszej nazwie
select w1.* 
  from wydzialy w1
  where
    length(w1.nazwa) = 
      (select max(length(w2.nazwa))from wydzialy w2)
--4 Osoby pracujace na wydziale o najdluzszej nazwie
select o.* 
  from osoby
  where 
    o.id in 
      (select z1.id_osoby 
        from zatrudnienia z1
        where z1.id_wydzialy in
          (select w3.id 
            from wydzialy w3
            where length(w3.nazwa) = 
              (select min(length(w4.nazwa)) from wydzialy w4)))
--5 Wydzial na ktorym suma pensji jest najmniejsza
select w.nazwa
  from wydzialy w, zatrudnienia z, pensje p
  where w.id = z.id_wydzialy and p.id_osoby = z.id_osoby
  group by w.nazwa
  having sum(p.pensja) in
    (select min(sum(p2.pensja)) 
      from pensje p2, zatrudnienia z 
      where p2.id_osoby = z.id_osoby
      group by z.id_wydzialy);
--6 Dla kazdej osoby podac roznicze dlugosci lat pracy liczac od osoby pracujacej najdluzszej