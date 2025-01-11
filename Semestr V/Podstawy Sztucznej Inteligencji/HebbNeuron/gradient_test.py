

x = 4.0
y = 2.0

delta = 0.1

def gradient(x,y) -> float:
    return 2.0*(x**3.0) + 3 * (y ** 2) + 4

print(f"Gradient without delta: ",gradient(x,y))
print(f"Gradient with minus delta: ",gradient(x-delta,y-delta))   
    