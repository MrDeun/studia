#Funkcja liczaca wartosc podanonego elementu z ciagu Fibonacciego
def value_of_fib(number):
    if number == 0: return 0
    if number == 1: return 1

    first_element = 0
    second_element = 1
    for iterator in range(1,number):
        temp = second_element
        second_element += first_element
        first_element = temp
    
    return second_element
