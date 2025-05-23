#Funkcja sprawdzajace polozenie punktu wzgledem trojkata (?????)
<<<<<<< HEAD

# Mozemy wyliczyc polozenie punktu wzgledem trojkata po przez wyliczenie
# czy suma pol powierzchni trojkatow utworzonych z podanego punktu 
# i dwoch wierzcholkow trojkata jest rowna polu powierzchni calego trojkata
#
# Jesli ktores z pomniejszych pol jest rowne zero to znaczy ze punkt znajduje
# sie na jednej z odcinkow tworzacych trojkat 
#
# Jesli pole trojkata jest rowne sumie pomniejszych trojkatow, 
# to znaczy ze punkt jest w trojkacie, wliczajac w tym krawedzie trojkata
#
# Jesli pole trojkata jest rozne od sumy pomniejszych trojkatow, 
# punkt jest poza trojkatem 
=======
#Utworzylem klasy punktu i trojkata dla wlasnej wygody rozwiazywania
>>>>>>> a51c39c45f1ee591549d6486f61f82d55359b971
class Point(object):
    def __init__(self, x:float, y:float):
        self.X = x
        self.Y = y

class Triangle(object):
    def __init__(self,vertex1:Point,vertex2:Point,vertex3:Point):
        self.Vertex1 = vertex1
        self.Vertex2 = vertex2
        self.Vertex3 = vertex3
    def __init__(self,x1:float,y1:float,x2:float,y2:float,x3:float,y3:float):
        self.Vertex1 = Point(x1,y1)
        self.Vertex2 = Point(x2,y2)
        self.Vertex3 = Point(x3,y3)

def triangleArea(vertex1:Point,vertex2:Point,vertex3:Point) -> float:
    return abs( (vertex1.X*(vertex2.Y-vertex3.Y) + 
                 vertex2.X*(vertex3.Y-vertex1.Y) + 
                 vertex3.X*(vertex1.Y-vertex2.Y)) /2.0)


def isInside(triangle_in:Triangle,point_in:Point) -> str:
    mainArea = triangleArea(triangle_in.Vertex1,triangle_in.Vertex2,triangle_in.Vertex3)

    subArea1 = triangleArea(point_in,triangle_in.Vertex2,triangle_in.Vertex3)
    subArea2 = triangleArea(triangle_in.Vertex1,point_in,triangle_in.Vertex3)
    subArea3 = triangleArea(triangle_in.Vertex1,triangle_in.Vertex2,point_in)

    if subArea1==0 or subArea2==0 or subArea3==0:
        return "Point is on the side of the triangle"
    elif mainArea==subArea1+subArea2+subArea3:
        return "Point is inside of the triangle"
    else:
        return "Point is outside of the triangle"



