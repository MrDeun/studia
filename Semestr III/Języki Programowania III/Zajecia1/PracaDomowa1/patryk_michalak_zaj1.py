#ZAJĘCIA 1, JPIII
#1.	Napisać program liczący:
#   a.	NWD(a,b)
#	b.	NWW(a,b)
#	c.	silnię(a)
#	d.	potęgę(a,n)
#2.	Napisać funkcję rysującą obrys trójkąta i prostokąta (przy wykorzystaniu dowolnego symbolu)
#3.	Napisać funkcję sprawdzającą czy dane wyrażenia są palindromami
#4.	Wykorzystując moduły proszę napisać:
#	a.	Funkcję zwracającą dowolny napis "od tyłu"
#	b.	Funkcję sprawdzającą czy dane ciągi znaków są anagramami
import zadanie1
import zadanie2
import zadanie3
import zadanie4

print("6! = " + zadanie1.factorial(6))
print("Najwiekszy wspolny dzielnik 2 i 6 to : " +zadanie1.biggestSharedDivisor(2,6))
print("Najmnniejszy wspólna wielkokrotnosci liczby 4 i 3 to: "  +zadanie1.smallestSharedMultipication(4,3))
print("6^3 = " +zadanie1.power(6,3))

zadanie2.printSquare(6)
zadanie2.printTriangle(6)

if(zadanie3.palidromCheck("ada")):
    print("Ada is a palidrom")
else:
    print("Ada is NOT a palidrom")

print("Hello World | " +zadanie4.reverseString("Hello World"))
print(" \"sup\" i \"pus\" to anagramy wzgledem siebie: " +zadanie4.anagramCheck("sup","pus"))