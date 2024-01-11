import random
random.seed()

def generate_number_list() -> list:
    list = []
    for random_number in range(20):
        list.append(random.random())
    return list

def find_divideable_by_5_7() -> list:
    numbers = range(1,201)
    dividable = filter(lambda x: x % 5 == 0 or x % 7 == 0, numbers)
    return list(dividable)
    

print(generate_number_list())
print(find_divideable_by_5_7())
