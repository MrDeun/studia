import numpy as np
class FIRFilter:
    """Projektowanie i analiza filtrów FIR"""
    
    WINDOWS = {
        'rectangular': np.ones,
        'hamming': np.hamming,
        'hanning': np.hanning,
        'blackman': np.blackman,
        'bartlett': np.bartlett
    }
    
    def __init__(self, sample_rate):
        self.sample_rate = sample_rate
        self.coefficients = None
        self.filter_type = None
        
    def design_lowpass(self, cutoff_freq, transition_width, window='hamming'):
        """Projektuje filtr dolnoprzepustowy"""
        self.filter_type = 'lowpass'
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        cutoff_normalized = cutoff_freq / nyquist
        
        self.coefficients = sp_signal.firwin(
            numtaps, 
            cutoff_normalized, 
            window=window,
            pass_zero='lowpass'
        )
        return self.coefficients
    
    def design_highpass(self, cutoff_freq, transition_width, window='hamming'):
        """Projektuje filtr górnoprzepustowy"""
        self.filter_type = 'highpass'
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        cutoff_normalized = cutoff_freq / nyquist
        
        self.coefficients = sp_signal.firwin(
            numtaps,
            cutoff_normalized,
            window=window,
            pass_zero='highpass'
        )
        return self.coefficients
    
    def design_bandpass(self, low_freq, high_freq, transition_width, window='hamming'):
        """Projektuje filtr środkowoprzepustowy"""
        self.filter_type = 'bandpass'
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        
        self.coefficients = sp_signal.firwin(
            numtaps,
            [low_freq / nyquist, high_freq / nyquist],
            window=window,
            pass_zero='bandpass'
        )
        return self.coefficients
    
    def design_bandstop(self, low_freq, high_freq, transition_width, window='hamming'):
        """Projektuje filtr środkowozaporowy"""
        self.filter_type = 'bandstop'
        numtaps = self._calculate_order(transition_width)
        nyquist = self.sample_rate / 2
        
        self.coefficients = sp_signal.firwin(
            numtaps,
            [low_freq / nyquist, high_freq / nyquist],
            window=window,
            pass_zero='bandstop'
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