import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def f(x, y):
    """Funkcja f(x,y) = (x^2 * cos(x) + 2y) / x"""
    return (x**2 * np.cos(x) + 2 * y) / x


def improved_euler(f, x0, y0, x_end, h):
    """
    Ulepszona metoda Eulera (metoda Heuna)

    Wzory:
    k1 = f(x_n, y_n)
    k2 = f(x_n + h, y_n + h*k1)
    y_{n+1} = y_n + h/2 * (k1 + k2)
    """
    # Przygotowanie tablic
    n_steps = int((x_end - x0) / h) + 1
    x_values = np.linspace(x0, x_end, n_steps)
    y_values = np.zeros(n_steps)
    dy_values = np.zeros(n_steps)

    # Warunek początkowy
    y_values[0] = y0
    dy_values[0] = f(x0, y0)

    # Nagłówek tabeli
    print("=" * 80)
    print("ULEPSZONA METODA EULERA (METODA HEUNA)")
    print("=" * 80)
    print(f"Równanie: dy/dx = (x² * cos(x) + 2y) / x")
    print(f"Warunek początkowy: y({x0:.4f}) = {y0:.4f}")
    print(f"Przedział: [{x0:.4f}, {x_end:.4f}]")
    print(f"Krok: h = {h:.6f}")
    print("=" * 80)
    print(f"{'n':>3} {'x':>12} {'y':>15} {'dy/dx':>15} {'k1':>15} {'k2':>15}")
    print("-" * 80)

    # Punkt początkowy
    print(
        f"{0:3d} {x_values[0]:12.6f} {y_values[0]:15.8f} {dy_values[0]:15.8f} {'---':>15} {'---':>15}"
    )

    # Iteracje metodą Heuna
    for i in range(n_steps - 1):
        x_n = x_values[i]
        y_n = y_values[i]

        # Krok 1: k1 = f(x_n, y_n)
        k1 = f(x_n, y_n)

        # Krok 2: k2 = f(x_n + h, y_n + h*k1)
        k2 = f(x_n + h, y_n + h * k1)

        # Krok 3: y_{n+1} = y_n + h/2 * (k1 + k2)
        y_values[i + 1] = y_n + (h / 2) * (k1 + k2)
        dy_values[i + 1] = f(x_values[i + 1], y_values[i + 1])

        # Wyświetl wyniki
        print(
            f"{i+1:3d} {x_values[i+1]:12.6f} {y_values[i+1]:15.8f} {dy_values[i+1]:15.8f} {k1:15.8f} {k2:15.8f}"
        )

    print("=" * 80)

    return x_values, y_values, dy_values


# Dane zadania
x0 = np.pi
y0 = np.pi**2
x_end = 2 * np.pi
h = np.pi / 10

# Rozwiązanie
x_values, y_values, dy_values = improved_euler(f, x0, y0, x_end, h)

# Tworzenie wykresów
fig = plt.figure(figsize=(16, 12))

# Wykres 3D - główny
ax1 = fig.add_subplot(1, 1, 1, projection="3d")
# Rysowanie krzywej rozwiązania w 3D (x, y, dy/dx)
ax1.plot(x_values, y_values, dy_values, "b-", linewidth=2.5, label="Krzywa rozwiązania")
ax1.scatter(
    x_values,
    y_values,
    dy_values,
    c="red",
    s=80,
    marker="o",
    edgecolors="darkred",
    linewidths=2,
)
ax1.scatter(
    [x0],
    [y0],
    [dy_values[0]],
    c="lime",
    s=200,
    marker="*",
    edgecolors="darkgreen",
    linewidths=2,
    label="Warunek początkowy",
)

ax1.set_xlabel("x", fontsize=11, fontweight="bold")
ax1.set_ylabel("y", fontsize=11, fontweight="bold")
ax1.set_zlabel("dy/dx", fontsize=11, fontweight="bold")
ax1.set_title("Przestrzeń fazowa (x, y, dy/dx)", fontsize=12, fontweight="bold")
ax1.legend(fontsize=9)
ax1.grid(True, alpha=0.3)

# Wykres 2D - y(x)
# ax2 = fig.add_subplot(2, 2, 2)
# ax2.plot(x_values, y_values, 'bo-', linewidth=2, markersize=8)
# ax2.plot(x0, y0, 'g*', markersize=15, label='Warunek początkowy')
# ax2.grid(True, alpha=0.3)
# ax2.set_xlabel('x', fontsize=11, fontweight='bold')
# ax2.set_ylabel('y', fontsize=11, fontweight='bold')
# ax2.set_title('Rozwiązanie y(x)', fontsize=12, fontweight='bold')
# ax2.legend(fontsize=9)
# x_ticks = np.linspace(x0, x_end, 6)
# ax2.set_xticks(x_ticks)
# ax2.set_xticklabels([f'{x/np.pi:.2f}π' for x in x_ticks])

# # Wykres 2D - dy/dx(x)
# ax3 = fig.add_subplot(2, 2, 3)
# ax3.plot(x_values, dy_values, 'ro-', linewidth=2, markersize=8)
# ax3.grid(True, alpha=0.3)
# ax3.set_xlabel('x', fontsize=11, fontweight='bold')
# ax3.set_ylabel('dy/dx', fontsize=11, fontweight='bold')
# ax3.set_title('Pochodna dy/dx(x)', fontsize=12, fontweight='bold')
# ax3.set_xticks(x_ticks)
# ax3.set_xticklabels([f'{x/np.pi:.2f}π' for x in x_ticks])

# # Wykres portretowy fazowy 2D (y, dy/dx)
# ax4 = fig.add_subplot(2, 2, 4)
# ax4.plot(y_values, dy_values, 'mo-', linewidth=2, markersize=8)
# ax4.plot(y0, dy_values[0], 'g*', markersize=15, label='Początek')
# ax4.plot(y_values[-1], dy_values[-1], 'r*', markersize=15, label='Koniec')
# ax4.grid(True, alpha=0.3)
# ax4.set_xlabel('y', fontsize=11, fontweight='bold')
# ax4.set_ylabel('dy/dx', fontsize=11, fontweight='bold')
# ax4.set_title('Portret fazowy (y, dy/dx)', fontsize=12, fontweight='bold')
# ax4.legend(fontsize=9)

plt.suptitle(
    "Rozwiązanie równania różniczkowego dy/dx = (x²cos(x) + 2y)/x\nulepszoną metodą Eulera",
    fontsize=14,
    fontweight="bold",
    y=0.995,
)

plt.tight_layout()
plt.show()

# Podsumowanie
print(f"\nWartość końcowa: y({x_end:.6f}) = {y_values[-1]:.8f}")
print(f"Pochodna końcowa: dy/dx({x_end:.6f}) = {dy_values[-1]:.8f}")
