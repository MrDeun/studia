--1 Prosze wypisac nazwisko (jedynie)
select nazwisko from osoby;
--2 Prosze wypisac pierwsze nazwisko wg. alfabetu
select min(nazwisko) from osoby;
--3 Prosze wypisac dane osoby, ktora posiada w/w(???) nazwisko
select o1.* 
    from osoby o1 
    where nazwisko=
        (select min(o2.nazwisko) from osoby o2);
--4 Dane osób o nazwiskach pisanych małymi literami
select o1.* 
    from osoby o1
    where char(o1.nazwisko)=
        (select lower(char(o2.nazwisko)) from osoby o2)
--5 Dane osób starszych od osoby najmłodszej
select o1.* 
    from osoby o1
    where o1.data_ur > (select min(o2.data_ur) from osoby o2)
--6 Dane osób aktualnie zatrudnionych (zagniezdzone)
select o1.* 
    from osoby o1, 
    where o1.id in (select z1.id_osoby 
                    from zatrudnienia z1) 
    and sysdate<(select z2.do 
                    from zatrudnienia z2);
--7 Dane osób zatrudnionych na wydziale informatyki
select o.* 
    from osoby o
    where o.id in (select z.id_osoby 
                      from 
                        zatrudnienia z, 
                        wydzialy w
                      where
                        z.id_wydzialy = w.id
                        and
                        w.nazwa like 'inf%');
--8 O ile kazda osoba jest mlodsza od najstarszej
select (select max(o2.data_ur) from osoby o2) - o1.data_ur from osoby o1;
--(PD) 9 Dane osób i aktualne pensje dla osob zatrudnionych