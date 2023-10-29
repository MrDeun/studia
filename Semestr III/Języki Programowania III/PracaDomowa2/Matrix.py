import numpy
exampleMatrix = numpy.matrix(numpy.arange(16).reshape(4,4))
halfMax = exampleMatrix.max()/2
print(exampleMatrix)
print("Diagonalna: ",exampleMatrix.diagonal())
print("Najmniejsza wartosc: ",exampleMatrix.min())
print("Najwieksza wartosc: ",exampleMatrix.max())
print("Wartosc srednia: ",exampleMatrix.mean())
print(all(iterator > halfMax for iterator in exampleMatrix.all()))