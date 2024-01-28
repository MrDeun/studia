#Usunac liczby ujemne z listy

def eradicate_negatives(list_in:list) -> list:
    temp = [element for element in list_in if element>=0]
    return temp

list = [-2,-1,0,1,2,3]
print(list,"   ",eradicate_negatives(list))