import SquareDictonary as sq
# Słownik to struktura danych która przechowuje dane
# w sposób uporządkowany i zawartosc komorki mozna zmienic
cardata = dict(brand = "Opel", year = "1979", color="tan")
print(cardata)
cardata.update({"color":"green"}) # Mozna zmieniac zawartosc komorki juz istniejacej
print(cardata["color"])
cardata.update({"register":"FY912"}) # Mozna dodawac nowe komorki
print(cardata)
cardata.pop("brand") # Mozna usuwac elementy z slownika
print(cardata)


# Zbiór działa na takiej samej zasadzie co zbiory
# W algebrze zbiorów. Takze, zbioty nie sa indexowane.

namesetA = set("Stefan Marek Konstantyn".split())
namesetB = set("Mikolaj Stefan Jacek".split())

# Mozemy wykonac operacje iloczynu zbioru aka. wybrac elementy ktore
# pojawia TYLKO sie w obu zbiorach
print(namesetA.intersection(namesetB))
# Mozemy wykonac operacje (AuB)\(AnB)
print(namesetA.symmetric_difference(namesetB))
# Mozemy wykonac operacje AuB
print(namesetA.union(namesetB))
# Mozemy wykonac operacje A\B
print(namesetA.difference(namesetB))

#Krotka to najzwyklejsza tablica ktorych danych nie mozna modyfikowac
tupleExample = (1,2,3,4,5,6,'a','b','c','d','e','f')
#tupleExample[2] = 3 #Python wykryje w tym momencie wykryje blad gdyz krotka(tuple) nie ma metody modyfikakcji elemntow.

sq.squaredictonary()