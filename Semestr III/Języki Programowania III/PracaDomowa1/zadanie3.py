def palidromCheck(sentenace):
    condition = True
    for i in range(int(len(sentenace)/2)):
        if(str(sentenace[i])==str(sentenace[len(sentenace)-i-1])):
            continue
        else:
            condition = False
            break
    return condition