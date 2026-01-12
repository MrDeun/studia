import numpy as np
import matplotlib.pyplot as plt


def lowpass_filter_windowed_sinc(signal, fc, M):
    """
    Apply FIR lowpass filter using windowed sinc method with Blackman window.

    Args:
        signal: Input signal as numpy array
        fc: Normalized cutoff frequency (0 to 0.5)
        M: Number of filter coefficients

    Returns:
        Filtered signal as numpy array
    """
    # Generate ideal sinc function
    z = np.zeros(M)
    for k in range(M):
        k_idx = k + 1  # Convert to 1-based indexing
        if (k_idx - M / 2) < 0:
            z[k] = np.sin(2 * np.pi * fc * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z[k] = 2 * np.pi * fc
        else:
            z[k] = np.sin(2 * np.pi * fc * (k_idx - M / 2)) / (k_idx - M / 2)

    # Normalize
    z = z / np.sum(z)

    # Apply Blackman window
    a = np.arange(1, M + 1)
    window = 0.42 - 0.5 * np.cos(2 * np.pi * a / M) + 0.08 * np.cos(4 * np.pi * a / M)
    filter_coeffs = z * window

    # Apply filter using convolution
    filtered_signal = np.convolve(signal, filter_coeffs, mode="same")

    return filtered_signal, filter_coeffs


def highpass_filter_windowed_sinc(signal, fc, M):
    """
    Apply FIR highpass filter using windowed sinc method with Blackman window.

    Args:
        signal: Input signal as numpy array
        fc: Normalized cutoff frequency (0 to 0.5)
        M: Number of filter coefficients

    Returns:
        Filtered signal and filter coefficients
    """
    # Generate ideal sinc function for lowpass
    z = np.zeros(M)
    for k in range(M):
        k_idx = k + 1
        if (k_idx - M / 2) < 0:
            z[k] = np.sin(2 * np.pi * fc * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z[k] = 2 * np.pi * fc
        else:
            z[k] = np.sin(2 * np.pi * fc * (k_idx - M / 2)) / (k_idx - M / 2)

    # Normalize
    z = z / np.sum(z)

    # Apply Blackman window
    a = np.arange(1, M + 1)
    window = 0.42 - 0.5 * np.cos(2 * np.pi * a / M) + 0.08 * np.cos(4 * np.pi * a / M)
    lowpass_coeffs = z * window

    # Convert to highpass using spectral inversion
    # Highpass = delta - lowpass
    highpass_coeffs = -lowpass_coeffs
    highpass_coeffs[M // 2] += 1  # Add impulse at center

    # Apply filter
    filtered_signal = np.convolve(signal, highpass_coeffs, mode="same")

    return filtered_signal, highpass_coeffs


def bandpass_filter_windowed_sinc(signal, fc_low, fc_high, M):
    """
    Apply FIR bandpass filter using windowed sinc method with Blackman window.

    Args:
        signal: Input signal as numpy array
        fc_low: Lower normalized cutoff frequency (0 to 0.5)
        fc_high: Upper normalized cutoff frequency (0 to 0.5)
        M: Number of filter coefficients

    Returns:
        Filtered signal and filter coefficients
    """
    # Generate lowpass filter with upper cutoff
    z_high = np.zeros(M)
    for k in range(M):
        k_idx = k + 1
        if (k_idx - M / 2) < 0:
            z_high[k] = np.sin(2 * np.pi * fc_high * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z_high[k] = 2 * np.pi * fc_high
        else:
            z_high[k] = np.sin(2 * np.pi * fc_high * (k_idx - M / 2)) / (k_idx - M / 2)

    # Generate lowpass filter with lower cutoff
    z_low = np.zeros(M)
    for k in range(M):
        k_idx = k + 1
        if (k_idx - M / 2) < 0:
            z_low[k] = np.sin(2 * np.pi * fc_low * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z_low[k] = 2 * np.pi * fc_low
        else:
            z_low[k] = np.sin(2 * np.pi * fc_low * (k_idx - M / 2)) / (k_idx - M / 2)

    # Normalize both
    z_high = z_high / np.sum(z_high)
    z_low = z_low / np.sum(z_low)

    # Apply Blackman window
    a = np.arange(1, M + 1)
    window = 0.42 - 0.5 * np.cos(2 * np.pi * a / M) + 0.08 * np.cos(4 * np.pi * a / M)

    lowpass_high = z_high * window
    lowpass_low = z_low * window

    # Bandpass = highpass(fc_low) - highpass(fc_high)
    # Which is equivalent to: lowpass(fc_high) - lowpass(fc_low)
    bandpass_coeffs = lowpass_high - lowpass_low

    # Apply filter
    filtered_signal = np.convolve(signal, bandpass_coeffs, mode="same")

    return filtered_signal, bandpass_coeffs


def bandstop_filter_windowed_sinc(signal, fc_low, fc_high, M):
    """
    Apply FIR bandstop (notch) filter using windowed sinc method with Blackman window.

    Args:
        signal: Input signal as numpy array
        fc_low: Lower normalized cutoff frequency (0 to 0.5)
        fc_high: Upper normalized cutoff frequency (0 to 0.5)
        M: Number of filter coefficients

    Returns:
        Filtered signal and filter coefficients
    """
    # Generate lowpass filter with upper cutoff
    z_high = np.zeros(M)
    for k in range(M):
        k_idx = k + 1
        if (k_idx - M / 2) < 0:
            z_high[k] = np.sin(2 * np.pi * fc_high * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z_high[k] = 2 * np.pi * fc_high
        else:
            z_high[k] = np.sin(2 * np.pi * fc_high * (k_idx - M / 2)) / (k_idx - M / 2)

    # Generate lowpass filter with lower cutoff
    z_low = np.zeros(M)
    for k in range(M):
        k_idx = k + 1
        if (k_idx - M / 2) < 0:
            z_low[k] = np.sin(2 * np.pi * fc_low * (k_idx - M / 2)) / (k_idx - M / 2)
        elif (k_idx - M / 2) == 0:
            z_low[k] = 2 * np.pi * fc_low
        else:
            z_low[k] = np.sin(2 * np.pi * fc_low * (k_idx - M / 2)) / (k_idx - M / 2)

    # Normalize both
    z_high = z_high / np.sum(z_high)
    z_low = z_low / np.sum(z_low)

    # Apply Blackman window
    a = np.arange(1, M + 1)
    window = 0.42 - 0.5 * np.cos(2 * np.pi * a / M) + 0.08 * np.cos(4 * np.pi * a / M)

    lowpass_high = z_high * window
    lowpass_low = z_low * window

    # Bandstop = lowpass(fc_low) + highpass(fc_high)
    # Bandstop = lowpass(fc_low) + (delta - lowpass(fc_high))
    bandstop_coeffs = lowpass_low - lowpass_high
    bandstop_coeffs[M // 2] += 1  # Add impulse at center

    # Apply filter
    filtered_signal = np.convolve(signal, bandstop_coeffs, mode="same")

    return filtered_signal, bandstop_coeffs


def apply_filter_menu(pure_signal, point_count):
    """
    Interactive menu for applying different filter types.
    """
    print("\n=== Filter Selection ===")
    print("1. Lowpass Filter")
    print("2. Highpass Filter")
    print("3. Bandpass Filter")
    print("4. Bandstop (Notch) Filter")
    print("5. No filter")

    filter_choice = input("Choose filter type: ")

    if filter_choice == "5":
        return None, None, None

    print("\nFilter Parameters:")
    M = int(input("Filter order (number of coefficients, e.g., 101): "))

    if filter_choice == "1":
        # Lowpass
        fc = float(input("Normalized cutoff frequency (0 to 0.5, e.g., 0.1): "))
        filtered_signal, filter_coeffs = lowpass_filter_windowed_sinc(
            pure_signal, fc, M
        )
        filter_params = {"type": "Lowpass", "fc": fc, "M": M}

    elif filter_choice == "2":
        # Highpass
        fc = float(input("Normalized cutoff frequency (0 to 0.5, e.g., 0.1): "))
        filtered_signal, filter_coeffs = highpass_filter_windowed_sinc(
            pure_signal, fc, M
        )
        filter_params = {"type": "Highpass", "fc": fc, "M": M}

    elif filter_choice == "3":
        # Bandpass
        fc_low = float(
            input("Lower normalized cutoff frequency (0 to 0.5, e.g., 0.05): ")
        )
        fc_high = float(
            input("Upper normalized cutoff frequency (0 to 0.5, e.g., 0.15): ")
        )
        filtered_signal, filter_coeffs = bandpass_filter_windowed_sinc(
            pure_signal, fc_low, fc_high, M
        )
        filter_params = {
            "type": "Bandpass",
            "fc_low": fc_low,
            "fc_high": fc_high,
            "M": M,
        }

    elif filter_choice == "4":
        # Bandstop
        fc_low = float(
            input("Lower normalized cutoff frequency (0 to 0.5, e.g., 0.05): ")
        )
        fc_high = float(
            input("Upper normalized cutoff frequency (0 to 0.5, e.g., 0.15): ")
        )
        filtered_signal, filter_coeffs = bandstop_filter_windowed_sinc(
            pure_signal, fc_low, fc_high, M
        )
        filter_params = {
            "type": "Bandstop",
            "fc_low": fc_low,
            "fc_high": fc_high,
            "M": M,
        }

    else:
        return None, None, None

    return filtered_signal, filter_coeffs, filter_params


def visualize_filter_results(
    pure_signal, filtered_signal, filter_coeffs, filter_params, point_count
):
    """
    Create comprehensive visualization of filter results.
    """
    fig = plt.figure(figsize=(14, 10))

    # 1. Original combined signal (time domain)
    plt.subplot(3, 2, 1)
    plt.plot(pure_signal)
    plt.title("Original Combined Signal (Time Domain)")
    plt.xlabel("Sample")
    plt.ylabel("Amplitude")
    plt.grid(True)

    # 2. Filtered signal (time domain)
    plt.subplot(3, 2, 2)
    plt.plot(filtered_signal)
    filter_title = f"Filtered Signal ({filter_params['type']})"
    plt.title(filter_title)
    plt.xlabel("Sample")
    plt.ylabel("Amplitude")
    plt.grid(True)

    # 3. Filter impulse response
    plt.subplot(3, 2, 3)
    plt.stem(filter_coeffs, basefmt=" ")
    plt.title(f"Filter Impulse Response (M={filter_params['M']})")
    plt.xlabel("Sample")
    plt.ylabel("Amplitude")
    plt.grid(True)

    # 4. Filter frequency response
    plt.subplot(3, 2, 4)
    filter_fft = np.fft.fft(filter_coeffs, point_count)
    filter_magnitude = np.abs(filter_fft[: point_count // 2])
    freqs = np.linspace(0, 0.5, point_count // 2)
    plt.plot(freqs, filter_magnitude)
    plt.title("Filter Frequency Response")
    plt.xlabel("Normalized Frequency")
    plt.ylabel("Magnitude")

    # Add cutoff frequency lines
    if filter_params["type"] in ["Lowpass", "Highpass"]:
        plt.axvline(
            x=filter_params["fc"],
            color="r",
            linestyle="--",
            label=f'Cutoff = {filter_params["fc"]}',
        )
    else:  # Bandpass or Bandstop
        plt.axvline(
            x=filter_params["fc_low"],
            color="r",
            linestyle="--",
            label=f'Low = {filter_params["fc_low"]}',
        )
        plt.axvline(
            x=filter_params["fc_high"],
            color="g",
            linestyle="--",
            label=f'High = {filter_params["fc_high"]}',
        )

    plt.legend()
    plt.grid(True)

    # 5. Original signal FFT
    plt.subplot(3, 2, 5)
    y_original = np.fft.fft(pure_signal, point_count)
    yy_original = np.abs(y_original[: point_count // 2]) / (point_count / 2)
    plt.plot(freqs, yy_original)
    plt.title("Original Signal - Frequency Spectrum")
    plt.xlabel("Normalized Frequency")
    plt.ylabel("Magnitude")

    # Add cutoff frequency lines
    if filter_params["type"] in ["Lowpass", "Highpass"]:
        plt.axvline(
            x=filter_params["fc"],
            color="r",
            linestyle="--",
            label=f'Cutoff = {filter_params["fc"]}',
        )
    else:
        plt.axvline(
            x=filter_params["fc_low"],
            color="r",
            linestyle="--",
            label=f'Low = {filter_params["fc_low"]}',
        )
        plt.axvline(
            x=filter_params["fc_high"],
            color="g",
            linestyle="--",
            label=f'High = {filter_params["fc_high"]}',
        )

    plt.legend()
    plt.grid(True)

    # 6. Filtered signal FFT
    plt.subplot(3, 2, 6)
    y_filtered = np.fft.fft(filtered_signal, point_count)
    yy_filtered = np.abs(y_filtered[: point_count // 2]) / (point_count / 2)
    plt.plot(freqs, yy_filtered)
    plt.title("Filtered Signal - Frequency Spectrum")
    plt.xlabel("Normalized Frequency")
    plt.ylabel("Magnitude")

    # Add cutoff frequency lines
    if filter_params["type"] in ["Lowpass", "Highpass"]:
        plt.axvline(
            x=filter_params["fc"],
            color="r",
            linestyle="--",
            label=f'Cutoff = {filter_params["fc"]}',
        )
    else:
        plt.axvline(
            x=filter_params["fc_low"],
            color="r",
            linestyle="--",
            label=f'Low = {filter_params["fc_low"]}',
        )
        plt.axvline(
            x=filter_params["fc_high"],
            color="g",
            linestyle="--",
            label=f'High = {filter_params["fc_high"]}',
        )

    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()
