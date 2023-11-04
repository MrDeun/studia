--DOM) Dla kazdej osoby podac kiedy miala 18 lat.
select imie1,nazwisko, data_ur+(18*365) as 'data pelnoletnosci' from osoby