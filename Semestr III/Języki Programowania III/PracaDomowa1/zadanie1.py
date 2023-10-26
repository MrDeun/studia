import math

def biggestSharedDivisor(a,b):
    while b!=0:
        temp = b
        b = a%b
        a = temp
    return a
    #return math.gcd(a,b)

def smallestSharedMultipication(a,b):
    NWD = biggestSharedDivisor(a,b)
    return (a*b)/NWD


def factorial(degree):
    if((degree == 0) or (degree == 1) ):
        return 1
    else:
        return degree*factorial(degree-1)
    
    #return math.factorial(degree)
    
def power(value,degree):
    calculation = 1
    for i in range(degree):
        calculation*=value 
    return calculation
    #math.pow(value,degree)