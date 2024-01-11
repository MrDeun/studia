import random
random.seed()

def sort_odd() -> list:
    numbers = [random.randint(1,100) for _ in range(50)]
    sorted_number = filter(lambda x : x%2 == 1, numbers)
    return list(sorted_number)