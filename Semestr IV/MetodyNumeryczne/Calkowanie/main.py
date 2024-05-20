import math

def func_test(x:float) -> float:
    res = (x * math.log(x,10))
    return res

def big_diff_approx(begin:float,end:float,count:int) -> float:
    deltaX = (end-begin)/count
    intermid = 0
    for i in range(1,count-1):
        intermid += func_test(begin + i*deltaX)
    approx = (func_test(begin) + intermid + func_test(end)) * deltaX/2
    return approx

def small_diff_approx(begin:float,end:float,count:int) -> float:
    deltaX = (end-begin)/count
    intermid = 0
    for i in range(1,count-1):
        intermid += func_test(begin + (i-1)*deltaX)
    approx = (func_test(begin) + intermid + func_test(end)) * deltaX/2
    return approx

    
print(big_diff_approx(0.01,2,100))
print(small_diff_approx(0.01,2,100))
