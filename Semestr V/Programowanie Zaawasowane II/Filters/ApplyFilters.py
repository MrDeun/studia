import cv2
import json
import numpy as np


def load_filters(file_path):
    """Wczytuje filtry z pliku JSON."""
    with open(file_path, 'r') as file:
        data = json.load(file)
    return data['filters']


def apply_filter(image, filter_data):
    """Aplikuje wybrany filtr na obraz zgodnie z danymi z JSON."""
    filter_name = filter_data['name']
    times = filter_data.get('times', 1)
    params = filter_data.get('params', {})

    for _ in range(times):
        if filter_name == "blur":
            ksize = params.get("ksize", 5)
            ksize = max(3, (ksize // 2) * 2 + 1)
            image = cv2.GaussianBlur(image, (ksize, ksize), 0)

        elif filter_name == "grayscale":
            if len(image.shape) == 3:
                image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        elif filter_name == "edge_detection":
            threshold1 = params.get("threshold1", 100)
            threshold2 = params.get("threshold2", 200)
            if len(image.shape) == 3:
                gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
                image = cv2.Canny(gray_image, threshold1, threshold2)
            else:
                image = cv2.Canny(image, threshold1, threshold2)

        elif filter_name == "sharpen":
            kernel = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])
            image = cv2.filter2D(image, ddepth=-1, kernel=kernel)

        else:
            print(f"Nieznany filtr: {filter_name}")

    return image


def main():
    image_path = input("Podaj ścieżkę do zdjęcia: ")
    filters_path = "filters.json"

    image = cv2.imread(image_path)
    if image is None:
        print("Nie udało się wczytać obrazu.")
        return

    original_image = image.copy()
    filters = load_filters(filters_path)

    while True:
        print("\nDostępne filtry:")
        for i, f in enumerate(filters):
            print(f"{i + 1}. Filtr: {f['name']}, Powtórzenia: {f.get('times', 1)}, Parametry: {f.get('params', {})}")

        print("0. Zakończ i wyświetl efekt końcowy.")
        choice = input("Wybierz numer filtra do zastosowania (lub 0, aby zakończyć): ")

        if choice == "0":
            break

        try:
            choice = int(choice) - 1
            if 0 <= choice < len(filters):
                selected_filter = filters[choice]

                times = input(
                    f"Ile razy zastosować filtr '{selected_filter['name']}'? (Domyślnie: {selected_filter.get('times', 1)}): ")
                if times.isdigit():
                    selected_filter['times'] = int(times)

                image = apply_filter(image, selected_filter)
                cv2.imshow(f"Efekt filtra: {selected_filter['name']}", image)
                cv2.waitKey(0)()
                cv2.destroyAllWindows()
            else:
                print("Nieprawidłowy wybór. Spróbuj ponownie.")
        except ValueError:
            print("Nieprawidłowy wybór. Spróbuj ponownie.")

    cv2.imshow("Oryginalne zdjęcie", original_image)
    cv2.imshow("Efekt końcowy", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()