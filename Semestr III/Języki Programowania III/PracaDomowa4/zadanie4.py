def sort_midstep(number_array:list) -> list:
    digits = [int(digit) for digit in str(number_array)]
    return sum(digits)

def sort_by_digit(number_array:list) -> list:
    return sorted(number_array,key = sort_midstep)