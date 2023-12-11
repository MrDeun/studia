--1)proszę wybrać najstarszą osobę obecnie pracującą
select o.* 
  from osoby o, zatrudnienia z
  where 
    z.id_osoby = o.id
    and ( (z.do is null) or  (sysdate> z.do) )
    and sysdate-o.data_ur in 
      ( select max(sysdate-o2.data_ur) from osoby o2 );
--2)proszę wybrać najmłodszą kobietę z każdego wydziału
select z.id_wydzialy,o.* from zatrudnienia z, osoby o
where 
  z.id_osoby = o.id 
  and plec='K'
--3)proszę wybrać drugą co do wielkości pensję
select max(pensja) from (  
  select p2.* 
    from pensje p2
      where ( ( select max(p1.pensja) from pensje p1)  > p2.pensja )
      order by (-p2.pensja))
  
--4)proszę wybrać wydział na którym pracuje najwięcej osób danej płci
--5)proszę wybrać najwyższą pensję wypłacaną na każdym wydziale, osobie aktualnie zatrudnione