--1 Proszę wybrać jedynie dane z pewnych osób uporządkowanych alfabetycznie wg nazwisk.
--- I fetch first x
--- II zagnieżdzenie
select *
    from (select o.nazwisko
            from osoby o
            order by o.nazwisko)
    where rownum<3;

--2 Osoby zatrudnione na wydziale na ktorym pracuje najwiecej osob

select o.*
  from osoby o, zatrudnienia z2
  where o.id=z2.id_osoby
    and z2.id_wydzialy = (select z1.id_wydzialy
                            from zatrudnienia z1
                            group by z1.id_wydzialy
                            having count(*) in (select max(count(*))
                                        from zatrudnienia z
                                        group by z.id_wydzialy))

--3 dane osob ktore nie otrzymaly podwyzki

select o.*
  from osoby o, pensje p
  where o.id=p.id_osoby
    and p.id_osoby in (select p1.id_osoby
                        from pensje p1
                        group by p1.id_osoby
                        having count(*) in (select min(count(*)) 
                                              from pensje p2
                                              group by p2.id_osoby));
--4 Wybrac wydzial ktor ma najmlodszego szefa

select w.* 
  from wydzialy w, osoby o
  where (sysdate-o.data_ur) = (select min(sysdate-o.data_ur) 
                              from osoby o, wydzialy w
                              where w.szef = o.id)
        and o.id = w.szef;

--5 Najstarsze osoby kazdej plci

select o1.*
  from osoby o1
  where o1.data_ur = (select max(o2.data_ur)
                      from osoby o2
                      where o1.plec = o2.plec);