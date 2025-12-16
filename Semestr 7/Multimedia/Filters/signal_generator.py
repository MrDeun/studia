import numpy as np
import math


# Saw singal
def saw_signal(amplitude: int, harmonics: int, point_size: int, frequency: float = 1.0):
    points = np.zeros(point_size)
    for i in range(harmonics):
        if i == 0:
            continue
        Ak = -(2 / i) * (-1) ** i
        for j in range(point_size):
            points[j] = points[j] + Ak * np.sin(
                2 * np.pi * i * j / point_size * frequency
            )
    return points


# Rectangle
def rec_signal(amplitude: int, harmonics: int, point_size: int, frequency: float = 1.0):
    points = np.zeros(point_size)
    for i in range(1, harmonics * 2, 2):
        if i == 0:
            continue
        Ak = (amplitude * 4) / (np.pi * i)
        for j in range(point_size):
            points[j] = points[j] + Ak * np.sin(
                2 * frequency * np.pi * i * j / point_size
            )
    return points


# Triangle
def tri_signal(amplitude: int, harmonics: int, point_size: int, frequency=1.0):
    points = np.zeros(point_size)
    for i in range(harmonics):
        if i == 0:
            continue
        Ak = (2 * point_size) / (np.pi**2) * (1 - (-1) ** i) / (i**2)
        for j in range(point_size):
            points[j] = points[j] + Ak * np.cos(
                2 * frequency * np.pi * i * j / point_size
            )
    return points


# Sinus approx
def sin_approx(periods, series_precision, point_count, amplitude=1.0):
    sin_range = np.zeros(point_count)
    for i in range(point_count):
        angle = i * np.pi / point_count * 2 * periods

        # Reduce angle to [-π, π] range
        angle = angle % (2 * np.pi)
        if angle > np.pi:
            angle -= 2 * np.pi

        y = 0
        term = angle

        for k in range(series_precision):
            y += term
            term *= -angle * angle / ((2 * k + 2) * (2 * k + 3))

        sin_range[i] = y * amplitude
    return sin_range


# Cosinus approx
def cos_approx(periods, series_precision, point_count, amplitude=1.0):
    cos_range = np.zeros(point_count)
    for i in range(point_count):
        angle = i * np.pi / point_count * 2 * periods

        # Reduce angle to [-π, π] range
        angle = angle % (2 * np.pi)
        if angle > np.pi:
            angle -= 2 * np.pi

        y = 1
        term = 1

        for k in range(1, series_precision):
            y += term
            term *= -angle * angle / ((2 * k + -1) * (2 * k + 0))

        cos_range[i] = y * amplitude
    return cos_range
