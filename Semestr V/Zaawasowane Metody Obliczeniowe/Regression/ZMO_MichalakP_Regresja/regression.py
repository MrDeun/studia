import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression

def read_dataframe():
  dataframe = pd.read_csv("auto-mpg.data")
  dataframe.pop('car_name')
  dataframe.replace('?',np.nan,inplace=True)
  dataframe = dataframe.dropna()
  
  features = []
  for column in dataframe:
    if column == "mpg":
      continue
    features.append(column)
  X = dataframe[features]
  y = dataframe['mpg']
  return X,y


def least_squares(X:pd.DataFrame,y:pd.DataFrame):
  X_matrix = X.to_numpy().astype(float)
  Y_vector = y.to_numpy().astype(float)

  X_matrix = np.c_[np.ones(X_matrix.shape[0]),X_matrix]
  X_transformed = np.matrix_transpose(X_matrix).astype(float)
  
  beta = np.linalg.inv(X_transformed @ X_matrix) @ X_transformed @ Y_vector
  return beta

def library_regression(X,y):
  model = LinearRegression().fit(X,y)
  return model.coef_


def main():
  X, y = read_dataframe()
  my_coef = least_squares(X.copy(),y.copy())
  lib_coef = library_regression(X.copy(),y.copy())
  for i in range(len(lib_coef)):
    print(f"My Coef{i}: {my_coef[i+1]}\t\tDiff: {abs(my_coef[i+1]-lib_coef[i])}\t\tLibrary Coef{i}: {lib_coef[i]}")
  print(f"{my_coef[0]}")
  print(*lib_coef)
main()


