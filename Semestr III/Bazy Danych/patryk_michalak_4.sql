select o1.*, p1.pensja 
    from osoby o1, pensje p1
    where 
        (o1.id = p1.id_osoby 
        and (p1.do >= sysdate or p1.do is null)) 
        and o1.id in 
            (select z2.id_osoby 
                from zatrudnienia z2 
                where 
                    z2.do >= sysdate 
                    or z2.do is null)
