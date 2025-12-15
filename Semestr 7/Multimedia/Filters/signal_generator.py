import numpy as np
import matplotlib.pyplot as plt


# Saw singal
def saw_signal(amplitude: int, harmonics: int, point_size: int):
    points = np.zeros(point_size)
    for i in range(harmonics):
        if i == 0:
            continue
        Ak = -(2 / i) * (-1) ** i
        for j in range(point_size):
            points[j] = points[j] + Ak * np.sin(2 * np.pi * i * j / point_size)
    return points


# Rectangle
def rec_signal(amplitude: int, harmonics: int, point_size: int):
    points = np.zeros(point_size)
    for i in range(harmonics):
        if i == 0:
            continue
        Ak = (amplitude * 4) / (np.pi * i)
        for j in range(point_size):
            points[j] = points[j] + Ak * np.sin(2 * np.pi * i * j / point_size)
    return points


# Triangle
def tri_signal(amplitude: int, harmonics: int, point_size: int):
    points = np.zeros(point_size)
    for i in range(harmonics):
        if i == 0:
            continue
        Ak = (2 * point_size) / (np.pi**2) * (1 - (-1) ** i) / (i**2)
        for j in range(point_size):
            points[j] = points[j] + Ak * np.cos(2 * np.pi * i * j / point_size)
    return points


# Sinus approx
def sin_approx(periods, series_precision, point_count):
    sin_range = np.zeros(point_count)
    for i in range(point_count):
        if i == 0:
            continue
        angle = i * np.pi / point_count * 2 * periods
        y = 0
        for k in range(series_precision):
            y += (-1) ** k * (angle ** (2 * k + 1)) / (math.factorial(2 * k + 1))
        sin_range[i] = y
    return sin_range
    x_range = np.array(range(point_count))

# Cosinus approx
def cos_approx(periods, series_precision, point_count):
    x_range = np.array(range(point_count))
    cos_range = np.zeros(point_count)
    for i in range(point_count):
        if i == 0:
            continue
        angle = i * np.pi / point_count * 2 * periods
        y = 0
        for k in range(series_precision):
            y += ((-1) ** k * (angle ** (2 * k))) / (math.factorial(2 * k))
        cos_range[i] = y
    cos_range[0] = 1
    return cos_range
