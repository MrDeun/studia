# Symulowanie ilości wygenerowanego metanu przez krowy w ciągu roku 
## Przeprowadzone przez: Patryk Michalak


### Etap I - Rozprowadzanie całkowitej ilości stada dorosłego między bydłem na mięso a krowami na mleko.

Rozkład Bernoulliego o 52.6% szansy żeby dana krowa była krową mleczną.

### Etap II - Obliczenie ilość cieląt

Całe stado wymożne przez zmienna losową o rozkładzie wykładniczym

### Etap III - Symulacje przyrostu stada przez miesiące
 - Podetap 1 - Wyrośnięcie cięląt do nowych dorosłych, które typ nowego dorosłego jest przepisany rozkładem z etapu I, i narodziny nowych cięląt.
 - Podetap 2 - Zgon dorosłych osobników w pewnym rozkładzie bernouliego, gdzie śmiertelności krów na mięso jest znacząco większa od śmiertelności krów mlecznych. 
 - Podetap 3 - Obliczanie ilość wyprodukowanego metanu w ciągu miesiąc, poprzez rozkład dyskretny średnich wartości wygenerowanego metanu przez krowę na roku, wraz z współczynnikami poszególnych typu krów i współczynnik aktualnego miesiąca przez ztablicowane wartości rozkładu normalnego.