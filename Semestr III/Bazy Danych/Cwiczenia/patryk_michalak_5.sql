--1)proszę wybrać najstarszą osobę obecnie pracującą
select o.* 
  from osoby o, zatrudnienia z
  where 
    z.id_osoby = o.id
    and ( (z.do is null) or  (sysdate> z.do) )
    and sysdate-o.data_ur in 
      ( select max(sysdate-o2.data_ur) from osoby o2 );
--2)proszę wybrać najmłodszą kobietę z każdego wydziału

select o1.* 
from osoby o1
where o1.data_ur in (select min(o.data_ur) 
                    from osoby o, zatrudnienia z, wydzialy w
                    where 
                      o.id = z.id_osoby 
                      and z.id_wydzialy = w.id
                      and o.plec = 'K'
                    group by w.nazwa)
--3)proszę wybrać drugą co do wielkości pensję
select max(pensja) from (  
  select p2.* 
    from pensje p2
    where ( ( select max(p1.pensja) from pensje p1)  > p2.pensja )
    order by (-p2.pensja))
  
--4)proszę wybrać wydział na którym pracuje najwięcej osób danej płci
select
    count(o.id) AS ilosc, w.nazwa,
    case
      when o.plec = 'K' then 'Kobiety'
      when o.plec = 'M' then 'Mężczyźni'
    end as plec_kolumna
  from osoby o, wydzialy w, zatrudnienia z
  where o.id = z.id_osoby 
    and z.id_wydzialy = w.id
    and (o.plec = 'K' or o.plec = 'M')
  group by w.nazwa, o.plec
  order by ilosc desc, w.nazwa;
--5)proszę wybrać najwyższą pensję wypłacaną na każdym wydziale, osobie aktualnie zatrudnione
select max(p.pensja), w.nazwa 
  from pensje p, wydzialy w, zatrudnienia z
  where p.id_osoby = z.id_osoby
    and z.id_wydzialy = w.id
    and (z.do is null or z.do > sysdate)
  group by w.nazwa