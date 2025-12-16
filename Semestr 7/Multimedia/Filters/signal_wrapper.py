import numpy as np


class Signal:
    values: np.ndarray
    title: str

    def __init__(self, values: np.ndarray, title: str):
        self.values = values
        self.title = title
