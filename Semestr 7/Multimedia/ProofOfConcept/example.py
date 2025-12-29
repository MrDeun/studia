import numpy as np
import matplotlib.pyplot as plt
from scipy import signal as sp_signal
from scipy.fft import fft, fftfreq


class SignalGenerator:
    """Generator sygnałów testowych"""

    @staticmethod
    def generate(signal_type, frequency, sample_rate, duration):
        """
        Generuje sygnał testowy

        signal_type: 'sin', 'square', 'triangle', 'sawtooth'
        frequency: częstotliwość sygnału w Hz
        sample_rate: częstotliwość próbkowania w Hz
        duration: czas trwania w sekundach
        """
        t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)

        if signal_type == "sin":
            return t, np.sin(2 * np.pi * frequency * t)
        elif signal_type == "square":
            return t, sp_signal.square(2 * np.pi * frequency * t)
        elif signal_type == "triangle":
            return t, sp_signal.sawtooth(2 * np.pi * frequency * t, 0.5)
        elif signal_type == "sawtooth":
            return t, sp_signal.sawtooth(2 * np.pi * frequency * t)
        else:
            raise ValueError(f"Nieznany typ sygnału: {signal_type}")


class FIRFilter:
    """Projektowanie i analiza filtrów FIR"""

    WINDOWS = {
        "rectangular": np.ones,
        "hamming": np.hamming,
        "hanning": np.hanning,
        "blackman": np.blackman,
        "bartlett": np.bartlett,
    }

    def __init__(self, sample_rate):
        self.sample_rate = sample_rate
        self.coefficients = None
        self.filter_type = None

    def design_lowpass(self, cutoff_freq, transition_width, window="hamming"):
        """Projektuje filtr dolnoprzepustowy"""
        self.filter_type = "lowpass"
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        cutoff_normalized = cutoff_freq / nyquist

        self.coefficients = sp_signal.firwin(
            numtaps, cutoff_normalized, window=window, pass_zero="lowpass"
        )
        return self.coefficients

    def design_highpass(self, cutoff_freq, transition_width, window="hamming"):
        """Projektuje filtr górnoprzepustowy"""
        self.filter_type = "highpass"
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        cutoff_normalized = cutoff_freq / nyquist

        self.coefficients = sp_signal.firwin(
            numtaps, cutoff_normalized, window=window, pass_zero="highpass"
        )
        return self.coefficients

    def design_bandpass(self, low_freq, high_freq, transition_width, window="hamming"):
        """Projektuje filtr środkowoprzepustowy"""
        self.filter_type = "bandpass"
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2

        self.coefficients = sp_signal.firwin(
            numtaps,
            [low_freq / nyquist, high_freq / nyquist],
            window=window,
            pass_zero="bandpass",
        )
        return self.coefficients

    def design_bandstop(self, low_freq, high_freq, transition_width, window="hamming"):
        """Projektuje filtr środkowozaporowy"""
        self.filter_type = "bandstop"
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2

        self.coefficients = sp_signal.firwin(
            numtaps,
            [low_freq / nyquist, high_freq / nyquist],
            window=window,
            pass_zero="bandstop",
        )
        return self.coefficients

    def _calculate_order(self, transition_width):
        """Oblicza rząd filtra na podstawie szerokości pasma przejściowego"""
        # Przybliżona formuła dla filtrów FIR z oknem
        order = int(3.3 * self.sample_rate / transition_width)
        # Upewniamy się, że rząd jest nieparzysty
        if order % 2 == 0:
            order += 1
        return order

    def apply_filter(self, signal):
        """Aplikuje zaprojektowany filtr do sygnału"""
        if self.coefficients is None:
            raise ValueError("Najpierw zaprojektuj filtr!")
        return sp_signal.lfilter(self.coefficients, 1.0, signal)

    def get_frequency_response(self, npoints=8192):
        """Zwraca odpowiedź częstotliwościową filtra"""
        if self.coefficients is None:
            raise ValueError("Najpierw zaprojektuj filtr!")

        w, h = sp_signal.freqz(self.coefficients, worN=npoints, fs=self.sample_rate)
        return w, 20 * np.log10(np.abs(h) + 1e-10)  # w dB

    def get_impulse_response(self):
        """Zwraca odpowiedź impulsową filtra"""
        if self.coefficients is None:
            raise ValueError("Najpierw zaprojektuj filtr!")
        return self.coefficients


class SignalAnalyzer:
    """Analiza harmoniczna sygnałów"""

    @staticmethod
    def compute_fft(signal, sample_rate):
        """Oblicza FFT sygnału i zwraca widmo amplitudowe"""
        N = len(signal)
        yf = fft(signal)
        xf = fftfreq(N, 1 / sample_rate)

        # Bierzemy tylko połowę (częstotliwości dodatnie)
        positive_freq_idx = xf >= 0
        xf = xf[positive_freq_idx]
        yf = np.abs(yf[positive_freq_idx]) * 2 / N

        return xf, yf

    @staticmethod
    def plot_fft_comparison(
        signal_before, signal_after, sample_rate, title="Analiza harmoniczna"
    ):
        """Porównuje widmo przed i po filtrowaniu"""
        freq_before, amp_before = SignalAnalyzer.compute_fft(signal_before, sample_rate)
        freq_after, amp_after = SignalAnalyzer.compute_fft(signal_after, sample_rate)

        plt.figure(figsize=(12, 5))

        plt.subplot(1, 2, 1)
        plt.plot(freq_before, amp_before)
        plt.title("Przed filtrowaniem")
        plt.xlabel("Częstotliwość [Hz]")
        plt.ylabel("Amplituda")
        plt.grid(True)
        plt.xlim(0, sample_rate / 2)

        plt.subplot(1, 2, 2)
        plt.plot(freq_after, amp_after)
        plt.title("Po filtrowaniu")
        plt.xlabel("Częstotliwość [Hz]")
        plt.ylabel("Amplituda")
        plt.grid(True)
        plt.xlim(0, sample_rate / 2)

        plt.tight_layout()
        plt.suptitle(title, y=1.02, fontsize=14)
        return plt


def demonstrate_filters():
    """Demonstracja działania wszystkich filtrów"""

    # Parametry
    sample_rate = 1000  # Hz
    duration = 1.0  # sekundy

    # Generowanie sygnału testowego (mieszanka częstotliwości)
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    test_signal = (
        np.sin(2 * np.pi * 10 * t)  # 10 Hz
        + 0.5 * np.sin(2 * np.pi * 50 * t)  # 50 Hz
        + 0.3 * np.sin(2 * np.pi * 120 * t)  # 120 Hz
        + 0.2 * np.sin(2 * np.pi * 200 * t)
    )  # 200 Hz

    # ====================
    # FILTR DOLNOPRZEPUSTOWY
    # ====================
    print("=" * 50)
    print("FILTR DOLNOPRZEPUSTOWY")
    print("=" * 50)

    fir_filter = FIRFilter(sample_rate)
    fir_filter.design_lowpass(cutoff_freq=80, transition_width=20, window="hamming")

    filtered_lowpass = fir_filter.apply_filter(test_signal)

    # Odpowiedź częstotliwościowa
    freq, response = fir_filter.get_frequency_response()
    plt.figure(figsize=(12, 8))

    plt.subplot(3, 1, 1)
    plt.plot(freq, response)
    plt.title("Odpowiedź częstotliwościowa - Filtr dolnoprzepustowy")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Wzmocnienie [dB]")
    plt.grid(True)
    plt.axvline(80, color="r", linestyle="--", label="Częstotliwość odcięcia")
    plt.legend()

    # Odpowiedź impulsowa
    plt.subplot(3, 1, 2)
    impulse = fir_filter.get_impulse_response()
    plt.stem(impulse, basefmt=" ")
    plt.title("Odpowiedź impulsowa (skokowa)")
    plt.xlabel("Numer próbki")
    plt.ylabel("Amplituda")
    plt.grid(True)

    # Sygnał przed i po
    plt.subplot(3, 1, 3)
    plt.plot(t[:500], test_signal[:500], alpha=0.7, label="Przed filtrowaniem")
    plt.plot(t[:500], filtered_lowpass[:500], alpha=0.7, label="Po filtrowaniu")
    plt.title("Sygnał w dziedzinie czasu")
    plt.xlabel("Czas [s]")
    plt.ylabel("Amplituda")
    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

    # Analiza harmoniczna
    SignalAnalyzer.plot_fft_comparison(
        test_signal,
        filtered_lowpass,
        sample_rate,
        "Analiza harmoniczna - Filtr dolnoprzepustowy",
    )
    plt.show()

    # ====================
    # FILTR GÓRNOPRZEPUSTOWY
    # ====================
    print("\n" + "=" * 50)
    print("FILTR GÓRNOPRZEPUSTOWY")
    print("=" * 50)

    fir_filter.design_highpass(cutoff_freq=80, transition_width=20, window="blackman")

    filtered_highpass = fir_filter.apply_filter(test_signal)

    freq, response = fir_filter.get_frequency_response()
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(freq, response)
    plt.title("Odpowiedź częstotliwościowa - Filtr górnoprzepustowy")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Wzmocnienie [dB]")
    plt.grid(True)
    plt.axvline(80, color="r", linestyle="--", label="Częstotliwość odcięcia")
    plt.legend()

    plt.subplot(1, 2, 2)
    impulse = fir_filter.get_impulse_response()
    plt.stem(impulse, basefmt=" ")
    plt.title("Odpowiedź impulsowa")
    plt.xlabel("Numer próbki")
    plt.ylabel("Amplituda")
    plt.grid(True)

    plt.tight_layout()
    plt.show()

    SignalAnalyzer.plot_fft_comparison(
        test_signal,
        filtered_highpass,
        sample_rate,
        "Analiza harmoniczna - Filtr górnoprzepustowy",
    )
    plt.show()

    # ====================
    # FILTR ŚRODKOWOPRZEPUSTOWY
    # ====================
    print("\n" + "=" * 50)
    print("FILTR ŚRODKOWOPRZEPUSTOWY")
    print("=" * 50)

    fir_filter.design_bandpass(
        low_freq=40, high_freq=100, transition_width=15, window="hanning"
    )

    filtered_bandpass = fir_filter.apply_filter(test_signal)

    freq, response = fir_filter.get_frequency_response()
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(freq, response)
    plt.title("Odpowiedź częstotliwościowa - Filtr środkowoprzepustowy")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Wzmocnienie [dB]")
    plt.grid(True)
    plt.axvline(40, color="r", linestyle="--", label="Dolna częst. odcięcia")
    plt.axvline(100, color="r", linestyle="--", label="Górna częst. odcięcia")
    plt.legend()

    plt.subplot(1, 2, 2)
    impulse = fir_filter.get_impulse_response()
    plt.stem(impulse, basefmt=" ")
    plt.title("Odpowiedź impulsowa")
    plt.xlabel("Numer próbki")
    plt.ylabel("Amplituda")
    plt.grid(True)

    plt.tight_layout()
    plt.show()

    SignalAnalyzer.plot_fft_comparison(
        test_signal,
        filtered_bandpass,
        sample_rate,
        "Analiza harmoniczna - Filtr środkowoprzepustowy",
    )
    plt.show()

    # ====================
    # FILTR ŚRODKOWOZAPOROWY
    # ====================
    print("\n" + "=" * 50)
    print("FILTR ŚRODKOWOZAPOROWY")
    print("=" * 50)

    fir_filter.design_bandstop(
        low_freq=40, high_freq=100, transition_width=15, window="hamming"
    )

    filtered_bandstop = fir_filter.apply_filter(test_signal)

    freq, response = fir_filter.get_frequency_response()
    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(freq, response)
    plt.title("Odpowiedź częstotliwościowa - Filtr środkowozaporowy")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Wzmocnienie [dB]")
    plt.grid(True)
    plt.axvline(40, color="r", linestyle="--", label="Dolna częst. zaporowa")
    plt.axvline(100, color="r", linestyle="--", label="Górna częst. zaporowa")
    plt.legend()

    plt.subplot(1, 2, 2)
    impulse = fir_filter.get_impulse_response()
    plt.stem(impulse, basefmt=" ")
    plt.title("Odpowiedź impulsowa")
    plt.xlabel("Numer próbki")
    plt.ylabel("Amplituda")
    plt.grid(True)

    plt.tight_layout()
    plt.show()

    SignalAnalyzer.plot_fft_comparison(
        test_signal,
        filtered_bandstop,
        sample_rate,
        "Analiza harmoniczna - Filtr środkowozaporowy",
    )
    plt.show()

    # ====================
    # PORÓWNANIE OKIEN
    # ====================
    print("\n" + "=" * 50)
    print("PORÓWNANIE RÓŻNYCH OKIEN")
    print("=" * 50)

    plt.figure(figsize=(14, 8))
    windows = ["rectangular", "hamming", "hanning", "blackman", "bartlett"]

    for idx, window in enumerate(windows, 1):
        fir_filter.design_lowpass(cutoff_freq=100, transition_width=20, window=window)
        freq, response = fir_filter.get_frequency_response()

        plt.subplot(2, 3, idx)
        plt.plot(freq, response)
        plt.title(f"Okno: {window}")
        plt.xlabel("Częstotliwość [Hz]")
        plt.ylabel("Wzmocnienie [dB]")
        plt.grid(True)
        plt.ylim(-100, 5)
        plt.axvline(100, color="r", linestyle="--", alpha=0.5)

    plt.tight_layout()
    plt.show()


def interactive_filter_design():
    """Interaktywne projektowanie filtra z wyborem parametrów"""

    print("\n" + "=" * 60)
    print("INTERAKTYWNE PROJEKTOWANIE FILTRA FIR")
    print("=" * 60)

    # Wybór typu sygnału
    print("\nWybierz typ sygnału testowego:")
    print("1. Sinus")
    print("2. Prostokąt")
    print("3. Trójkąt")
    print("4. Piła")
    signal_choice = input("Wybór (1-4): ").strip()

    signal_types = {"1": "sin", "2": "square", "3": "triangle", "4": "sawtooth"}
    signal_type = signal_types.get(signal_choice, "sin")

    frequency = float(input("Częstotliwość sygnału [Hz] (np. 50): ") or "50")

    # Wybór typu filtra
    print("\nWybierz typ filtra:")
    print("1. Dolnoprzepustowy")
    print("2. Górnoprzepustowy")
    print("3. Środkowoprzepustowy")
    print("4. Środkowozaporowy")
    filter_choice = input("Wybór (1-4): ").strip()

    # Wybór okna
    print("\nWybierz typ okna:")
    print("1. Rectangular")
    print("2. Hamming")
    print("3. Hanning")
    print("4. Blackman")
    print("5. Bartlett")
    window_choice = input("Wybór (1-5): ").strip()

    windows = {
        "1": "rectangular",
        "2": "hamming",
        "3": "hanning",
        "4": "blackman",
        "5": "bartlett",
    }
    window = windows.get(window_choice, "hamming")

    # Parametry
    sample_rate = 1000
    duration = 2.0
    transition_width = float(
        input("\nSzerokość pasma przejściowego [Hz] (np. 20): ") or "20"
    )

    # Generowanie sygnału
    t, test_signal = SignalGenerator.generate(
        signal_type, frequency, sample_rate, duration
    )

    # Dodajemy szum i wyższe harmoniczne
    test_signal = (
        test_signal
        + 0.3 * np.sin(2 * np.pi * frequency * 3 * t)
        + 0.1 * np.random.randn(len(t))
    )

    # Projektowanie filtra
    fir_filter = FIRFilter(sample_rate)

    if filter_choice == "1":
        cutoff = float(input("Częstotliwość odcięcia [Hz]: ") or "100")
        fir_filter.design_lowpass(cutoff, transition_width, window)
    elif filter_choice == "2":
        cutoff = float(input("Częstotliwość odcięcia [Hz]: ") or "100")
        fir_filter.design_highpass(cutoff, transition_width, window)
    elif filter_choice == "3":
        low = float(input("Dolna częstotliwość [Hz]: ") or "50")
        high = float(input("Górna częstotliwość [Hz]: ") or "150")
        fir_filter.design_bandpass(low, high, transition_width, window)
    else:
        low = float(input("Dolna częstotliwość zaporowa [Hz]: ") or "50")
        high = float(input("Górna częstotliwość zaporowa [Hz]: ") or "150")
        fir_filter.design_bandstop(low, high, transition_width, window)

    # Filtrowanie
    filtered_signal = fir_filter.apply_filter(test_signal)

    # Wyświetlanie wyników
    freq, response = fir_filter.get_frequency_response()
    impulse = fir_filter.get_impulse_response()

    # Wykres 1: Odpowiedź częstotliwościowa i impulsowa
    plt.figure(figsize=(14, 10))

    plt.subplot(3, 2, 1)
    plt.plot(freq, response, linewidth=2)
    plt.title("Odpowiedź częstotliwościowa", fontsize=12, fontweight="bold")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Wzmocnienie [dB]")
    plt.grid(True, alpha=0.3)

    plt.subplot(3, 2, 2)
    plt.stem(impulse, basefmt=" ")
    plt.title("Odpowiedź impulsowa (skokowa)", fontsize=12, fontweight="bold")
    plt.xlabel("Numer próbki")
    plt.ylabel("Amplituda")
    plt.grid(True, alpha=0.3)

    # Wykres 2: Sygnał przed i po
    plt.subplot(3, 2, 3)
    samples_to_show = min(1000, len(t))
    plt.plot(
        t[:samples_to_show], test_signal[:samples_to_show], alpha=0.7, label="Przed"
    )
    plt.plot(
        t[:samples_to_show],
        filtered_signal[:samples_to_show],
        alpha=0.8,
        label="Po",
        linewidth=1.5,
    )
    plt.title("Sygnał w dziedzinie czasu", fontsize=12, fontweight="bold")
    plt.xlabel("Czas [s]")
    plt.ylabel("Amplituda")
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Wykres 3: Analiza harmoniczna
    freq_before, amp_before = SignalAnalyzer.compute_fft(test_signal, sample_rate)
    freq_after, amp_after = SignalAnalyzer.compute_fft(filtered_signal, sample_rate)

    plt.subplot(3, 2, 4)
    plt.plot(freq_before, amp_before, alpha=0.7, label="Przed")
    plt.plot(freq_after, amp_after, alpha=0.8, label="Po", linewidth=1.5)
    plt.title("Widmo sygnału (FFT)", fontsize=12, fontweight="bold")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Amplituda")
    plt.xlim(0, 500)
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.subplot(3, 2, 5)
    plt.semilogy(freq_before, amp_before + 1e-10, alpha=0.7, label="Przed")
    plt.semilogy(freq_after, amp_after + 1e-10, alpha=0.8, label="Po", linewidth=1.5)
    plt.title("Widmo (skala logarytmiczna)", fontsize=12, fontweight="bold")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Amplituda (log)")
    plt.xlim(0, 500)
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Informacje o filtrze
    plt.subplot(3, 2, 6)
    plt.axis("off")
    info_text = f"""
    PARAMETRY FILTRA:
    
    Typ filtra: {fir_filter.filter_type}
    Okno: {window}
    Rząd filtra: {len(impulse)}
    Pasmo przejściowe: {transition_width} Hz
    
    Typ sygnału: {signal_type}
    Częstotliwość: {frequency} Hz
    Częstotliwość próbkowania: {sample_rate} Hz
    """
    plt.text(
        0.1, 0.5, info_text, fontsize=11, family="monospace", verticalalignment="center"
    )

    plt.tight_layout()
    plt.show()

    print("\n" + "=" * 60)
    print("Projekt filtra zakończony!")
    print("=" * 60)


# Uruchomienie programu
if __name__ == "__main__":
    print("=" * 60)
    print("APLIKACJA PROJEKTOWANIA FILTRÓW FIR")
    print("=" * 60)
    print("\nWybierz tryb:")
    print("1. Demonstracja wszystkich filtrów")
    print("2. Interaktywne projektowanie filtra")

    choice = input("\nWybór (1-2): ").strip()

    if choice == "1":
        demonstrate_filters()
    else:
        interactive_filter_design()
