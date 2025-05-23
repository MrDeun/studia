-- 1) Utworzyc tablice (roznymi sposobami)
create table *NAZWA TABELI*
(
    *NAZWA DANYCH* *TYP DANYCH*
)
-- 2) Zmienic jej nazwe
alter table old_name rename to new_name
-- 3) Wypisac jej atrybuty
select * from table_name
-- 4) Wpisac wiersze do tablicy (roznymi sposobami)
insert into nazwa_tabeli (kolumna1, kolumna2, ...)
values (wartosc1, wartosc2, ...)
-- 5) Wypisac kolumny (roznymi sposobami)
-- 6) Usunac obiekty
-- 7) Dodanie kolumny do istniejacej tabeli
-- 8) Zmodyfikowanie istniejacej kolumny o stwierdzenie NOT NULL
-- 9) Zmiana nazwy kolumny
-- 10) Usuniecie kolumny
-- 11) Usuniecie krotki wiersza
-- 12) Wyswietlic piersze/ostatnie alfabetycznie nazwisko
-- 13) Z tabeli osoby Wyswietlic nazwiska pisane duzymi literami a imie1 pisane z duzej litery
-- 14) w tabeli osoby zmodyfikowac nazwisko napisane wielkimi literami dla osob ktorych id to 1,2
-- 15) W tabeli osoby zmodyikowac nazwisko napisane z duzej litery, a imie1 napisane wielkimi literami do osoby o id=3
-- 16) Wybrac dane osobowe osob, ktorych nazwiska wpisane sa malymi literami.
-- 17) Wyznaczyc dane osobowe osob, ktorych nazwiska wpisane sa malymi literami
-- 18) Wyznaczyc dane osobowe osob, ktore w nazwisku posiadaja na drugiej pozycji litere o 
-- 19) Wyswietlic dane wszytkich wydzialow ktore wewnatrz nazwy zawieraja litere 'a'
-- 20) Wybrac dane osobowe i w miejsce brakujacego drugiego imienia wpisac tekst 'brak'
-- 21) Wypisac rozne nazwiska z tabeli Osoby wyrownane do prawej strony (20 znakow)
-- 22) Wypisac rozne drugie litery z nazwiska w tabeli osoby i dlugosc imienia
-- 23) Wybrac id, nazwisko, imie1, plec tak aby zamiast 'K' wyswietlalo 'kobieta' a zamiast 'M' bedzie wyswietlalo 'Mezczyzna'
-- 24) Wyswietlic dane wszytkich osob, ktore urodzily sie po 01.01.1983 roku
-- 25) Wybrac dane osobowe osob urodzonych po 1/01/1990 roku
-- 26) Wyswietlic sam rok
-- 27) Wyswietlic dane dla wierszy gdzie w dacie do rok jest mniejszy jak 2012
-- 28) Z tabeli pensje Wyswietlic id_osoby oraz jej srednia pensje, max pensje, zliczyc wiersze i pogrupowac wg id_osoby
-- 29) Osoby obecnie zatrudnione
-- 30) Osoby majace aktualna pensje
-- 31) najpierw zliczyc i pogrupowac po id_osoby
-- 32) z tabeli pensje Wyswietlic id_osoby jej srednia pensje, max pensje, 
--     zliczyc wiersze gdze nie ma okreslonej 
--     daty konca wyplacania pensji (czyli aktualne pensje) 
--     i pogrupowac wg id_osoby
-- 33) z tabeli pensje wyswitelic id_osoby jej srednia pensje, max pensje, zliczyc wiersze gdzie
--     nie ma okreslonej daty konca wyplacania pensji (czyli same aktualne pensje) i pogrupowac wg id_osoby
-- 34) wyswitelic dla kazdej osoby id_osoby i zliczyc dla niej srednia pensje dla osob 
--     majacych pensje powyzej i posortowac wynik wedlug sredniej
-- 35) wyswietlic dlugosc nazwiska
-- 36) z tabeli osoby wyswietlic lacznie jako jedna kolumne atrybuty imie 1 i nazwisko nazywajace nowa kolumne dane
-- 37) z tabeli osoby wyswietlic lacznie jako jedna kolumne atrybuty imie 1 i nazwysko nazywajac nowa kolumne dane,
--     sprawdzic czy posiadane jest imie2 jesli nie wpisac brak, wyswietlic date urorzenia, a w kolumnie plec w zaleznosci od odznaczenia wpisac kobieta, mezczyzna lub ?
-- 38) wyswietlic dane z tabel osoby i pensje
-- 39) wyswietlic dane z dwoch tabel laczac wewnetrzenie na kolumnach id i id_osoby
-- 40) wyswietlic dane dla osob o id 1,2,3 posiadajacych aktualna pensje
-- 41) wybrac id, nazwisko, imie1, oraz aktualna pensje
-- 42) wyswietlic dane osobowe wszytkich osob zatrudnionych nie posiadajacych aktualnej pensji
-- 43) wybrac wszytkie dane osob zatrudnionych aktualnie pracujace wraz z nazwa wydzialu
-- 44) Wyznaczyć średnią pensję aktualnie pracujących na każdym wydziale i wyświetlić w postaci:
-- 45) Wyznaczyć średnią wieku aktualnie pracujących pracowników dla każdej płci
-- 46) wypisać aktualnego szefa
-- 47) wyświetlić dane osobowe wszystkich osob o nazwisku pisanym malymi literami
-- 48) dane najstarszej osoby
-- 49) wyświetlić dane osób dla których data urodzenia jest większa od min daty urodzenia
-- 50) wybrać dane osobowe osób nieposiadających aktualnej pensji
-- 51) wybrać dane osobowe pierwszej osoby według alfabetu
-- 52) wybrać dane szefów
-- 53)Wyświetlić wszystkie dane osób, które posiadają najkrótsze nazwisko .
-- 54) wydział o nazwie maksymalnej dlugości I wypisać zatrudnione tam osoby
WITH najdluzsza_nazwa AS (
    SELECT *
    FROM WYDZIALY w, ZATRUDNIENIA z
    WHERE w.id = z.ID_WYDZIALY
    AND LENGTH(w.nazwa) = (SELECT MAX(LENGTH(w1.nazwa)) FROM WYDZIALY w1)
)
SELECT *
FROM osoby o, ZATRUDNIENIA z
WHERE o.id = najdluzsza_nazwa.ID_OSOBY;
-- 55) Wybrać najmłodszą osobę już niepracującą
with niepracujace as
(
 select o.* from osoby o, ZATRUDNIENIA z
    where z.id_osoby = o.id
    and z.do < sysdate     
)

select o1.* from osoby o1, niepracujace
where o1.DATA_UR = (select min(DATA_UR) from niepracujace)
-- 56) dane najstarszego szefa

-- 57) Wyznaczyć wydział, na którym suma pensji jest największa
-- 58) wyświetlić największą pensje aktualnie wypłacaną
-- 59) Na którym wydziale pracuje aktualnie najwięcej osób
-- 60) Wybrać osoby, które nie otrzymały jeszcze podwyżki
-- 61) Wybrać wydział, który ma najstarszego szefa aktualnie pracującego
-- 62) wyświetlić dane wydziałów posiadających więcej jak 2 pracowników

-- 63) najstarsze osoby z każdej płci
select * from osoby
    where plec = 'K'
    and data_ur = (select min(data_ur) from osoby where plec = 'K')
UNION ALL
select * from osoby
    where plec = 'M'
    and data_ur = (select min(data_ur) from osoby where plec = 'M')
