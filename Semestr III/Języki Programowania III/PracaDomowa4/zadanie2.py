from enum import Enum

def monotonicity_check(number_list : list) -> str:
    state = "Unknown"

    for iterator in range(len(number_list)-1):
        if( number_list[iterator] < number_list[iterator+1] ):
            match state:
                case "Unknown":
                    state = "Ascending"
                case "Static":
                    state = "Not Descending"
                case "Ascending":
                    state = state
                case "Descending":
                    return "Unknown"
                case "Not Descending":
                    state = state
                case "Not Ascending":
                    return "Unknown"
                case _:
                    return "Unknown"
        elif( number_list[iterator] == number_list[iterator+1] ):
            match state:
                case "Unknown":
                    state = "Static"
                case "Static":
                    state = state
                case "Ascending":
                    state = "Not Descending"
                case "Descending":
                    state = "Not Ascending"
                case "Not Ascending":
                    state = state
                case "Not Descending":
                    state = state
                case _:
                    return "Unknown"
        elif( number_list[iterator] > number_list[iterator+1] ):
            match state:
                case "Unknown":
                    state = "Descending"
                case "Static":
                    state = "Not Ascending"
                case "Ascending":
                    return "Unknown"
                case "Descending":
                    state = state
                case "Not Ascending":
                    state = state
                case "Not Descending":
                    return "Unknown"
                case _:
                    return "Unknown"
    
    return state