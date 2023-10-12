def printSquare(side):
        for j in range(side):
            if(j==0 or j==side-1):
                print("#"*side)
            else:
                print("#" + " "*int(side-2) + "#")

def printTriangle(side):
    for j in range(side):
        if(j<2):
            print("#"*int(j+1)+" "*int(side-j))
        elif(j==side-1):
            print("#"*int(j+1))
        else:
            print("#"+" "*(j-1)+"#")    