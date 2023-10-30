import numpy

# Python w swojej najprostrzej formie nie ma tablicy znanej z C++
# Wszytkie struktury danych sa prowadzone tylko w jednym wymiarze
# Biblioteka numpy uzupelnia ten brak dodajac swojego array'a (numpy.array) ktorego
# mozna takze potraktowac jako macierz (numpy.matrix)

def compareMatrix(matrix):
    for a in range(matrix.shape[0]):
        temp = "["
        for b in range(matrix.shape[1]):
            temp += str(matrix[a,b]>halfMax) + ", "
        print(temp,"]")
    return

exampleMatrix = numpy.matrix(numpy.arange(16).reshape(4,4))
halfMax = exampleMatrix.max()/2
print(exampleMatrix)
print("Diagonalna: ",exampleMatrix.diagonal())
print("Najmniejsza wartosc: ",exampleMatrix.min())
print("Najwieksza wartosc: ",exampleMatrix.max())
print("Wartosc srednia: ",exampleMatrix.mean())
print("Macierz z wszytkimi wartosciamy podniesionymi o dziesiec\n", exampleMatrix + 10)
print(compareMatrix(numpy.matrix(exampleMatrix)))