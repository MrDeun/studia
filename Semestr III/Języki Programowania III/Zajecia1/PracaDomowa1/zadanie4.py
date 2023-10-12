def reverseString(sentance):
    return sentance[::-1]

def anagramCheck(First,Second):
    if(sorted(First)==sorted(Second)):
        return True
    else:
        return False