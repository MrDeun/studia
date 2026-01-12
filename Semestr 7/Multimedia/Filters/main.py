import signal_generator as SignalGenerator
import signal_wrapper
import filters as Filters

import numpy as np
import matplotlib.pyplot as plt

point_count = 0x800
signals = []


def generate_sinus():
    cycles = int(input("Cycles: "))
    precision = int(input("Series precision: "))
    amplitude = float(input("Amplitude: "))
    arr = SignalGenerator.sin_approx(
        periods=cycles,
        series_precision=precision,
        point_count=point_count,
        amplitude=amplitude,
    )
    return signal_wrapper.Signal(arr, "Sin signal")


def generate_cosinus():
    cycles = int(input("Cycles: "))
    precision = int(input("Series precision: "))
    amplitude = float(input("Amplitude: "))
    arr = SignalGenerator.cos_approx(
        periods=cycles,
        series_precision=precision,
        point_count=point_count,
        amplitude=amplitude,
    )
    return signal_wrapper.Signal(arr, "Cos signal")


def generate_saw():
    amplitude = int(input("Amplitude: "))
    harmonics = int(input("Harmonics: "))
    frequency = float(input("Frequency: "))
    arr = SignalGenerator.rec_signal(
        amplitude=amplitude,
        harmonics=harmonics,
        point_size=point_count,
        frequency=frequency,
    )
    return signal_wrapper.Signal(arr, "Saw signal")


def generate_triangle():
    amplitude = int(input("Amplitude: "))
    harmonics = int(input("Harmonics: "))
    frequency = float(input("Frequency: "))
    arr = SignalGenerator.rec_signal(
        amplitude=amplitude,
        harmonics=harmonics,
        point_size=point_count,
        frequency=frequency,
    )
    return signal_wrapper.Signal(arr, "Triangle signal")


def generate_rectangle():
    amplitude = int(input("Amplitude: "))
    harmonics = int(input("Harmonics: "))
    frequency = float(input("Frequency: "))
    arr = SignalGenerator.rec_signal(
        amplitude=amplitude,
        harmonics=harmonics,
        point_size=point_count,
        frequency=frequency,
    )
    return signal_wrapper.Signal(arr, "Rectangle signal")


if __name__ == "__main__":
    print("Hello to signal processing!")
    loop_choices = True

    while loop_choices:
        option = input(
            "Choose a signal to generate"
            "\n\t1. Sinus\n\t2. Cosinus"
            "\n\t3. Saw signal\n\t"
            "4. Triangle signal\n\t"
            "5. Rectangle signal\n\t"
            "6. Finish picking signals\n"
        )

        match option:
            case "1":
                signal = generate_sinus()
                signals.append(signal)
            case "2":
                signal = generate_cosinus()
                signals.append(signal)
            case "3":
                signal = generate_saw()
                signals.append(signal)
            case "4":
                signal = generate_triangle()
                signals.append(signal)
            case "5":
                signal = generate_rectangle()
                signals.append(signal)
            case "6":
                loop_choices = False
            case _:
                continue

    assert len(signals) > 0

    # Combine all signals
    pure_signal = np.zeros(point_count)
    for signal in signals:
        pure_signal += signal.values

    # Apply filter with interactive menu
    filtered_signal, filter_coeffs, filter_params = Filters.apply_filter_menu(
        pure_signal, point_count
    )

    if filtered_signal is not None:
        # Visualize filter results
        Filters.visualize_filter_results(
            pure_signal, filtered_signal, filter_coeffs, filter_params, point_count
        )
    else:
        # Original visualization without filter
        plot_counts = len(signals) + 2
        plt.figure(figsize=(10, 8))

        for i in range(len(signals)):
            plt.subplot(plot_counts, 1, i + 1)
            plt.plot(signals[i].values)
            plt.title(signals[i].title)
            plt.grid(True)

        plt.subplot(plot_counts, 1, len(signals) + 1)
        plt.scatter(range(point_count), pure_signal, s=1)
        plt.title("Combined signals")
        plt.grid(True)

        t = range(point_count)
        y = np.fft.fft(pure_signal, point_count)
        yy = np.sqrt(y * np.conjugate(y)) / (point_count / 2)
        yy = yy[: len(yy) // 2]

        plt.subplot(plot_counts, 1, plot_counts)
        plt.title("Fourier Transform of combined signal")
        plt.bar(t[: len(t) // 2], yy)
        plt.grid()

        plt.tight_layout()
        plt.show()
