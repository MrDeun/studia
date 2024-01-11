# funcja Lambda jest to skrocony zapis dla stworzenia funkcji
# anonimowej. Przydaje sie na przyklad w wypadku gdy wyszukujemy 
# w jakims zbiorze liczby ktore spelniaja szczegolne warunki albo
# dla kazdej wartosci znajdujacej sie w strukturze danych musimy wymnozyc
# przez jakas stala.

def lambda_example():
    numbers = range(1,21)
    square_numbers = list(map(lambda x : x*x,numbers))
    return square_numbers
    

print(lambda_example())