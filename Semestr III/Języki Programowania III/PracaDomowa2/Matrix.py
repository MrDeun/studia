import numpy

def matrixCheck(matrix):
    for iterator in matrix[]:
        temp = ""


exampleMatrix = numpy.matrix(numpy.arange(12).reshape(3,4))
print(exampleMatrix)
print("Diagonalna: ",exampleMatrix.diagonal())
print("Najmniejsza wartosc: ",exampleMatrix.min())
print("Najwieksza wartosc: ",exampleMatrix.max())
print("Czy wszytkie liczby sa wieksze od polowy najwiekszego elementu? ",)