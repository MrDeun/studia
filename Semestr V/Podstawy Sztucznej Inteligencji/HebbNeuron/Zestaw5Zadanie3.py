import numpy as np
import matplotlib.pyplot as plt
train_data = [
  [ 
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0,

  ],
  [
    1.0,-1.0,1.0,
    1.0, 1.0,1.0,
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0, 
  ]
]

test_data = [
  [ 
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0,
   -1.0, 1.0,1.0,
   -1.0,-1.0,1.0,

  ],
  [
    1.0, 1.0,1.0,
    1.0, 1.0,1.0,
   -1.0,-1.0,1.0,
   -1.0,-1.0,1.0, 
  ]
]

results = [0,1]

def sigmoid(x, beta=1):
  return 1 / (1 + np.exp(-beta * x))
def sigmoid_derivative(x,beta=1):
  return sigmoid(x,beta=beta) * (1 - sigmoid(x,beta=beta))

def train(X,D,learning_rate=0.001,epochs=1000,error_threshold=0.005):
  num_samples, num_features = X.shape
  weights = np.random.randn(num_features)
  errors = []
  for epoch in range(epochs):
    total_error = 0.0
    for i in range(num_samples):
      x_input = X[i]
      y_expected = D[i]

      net_input = np.dot(x_input,weights)
      y_predicted = sigmoid(net_input)
      
      error = y_expected - y_predicted
      total_error += (error**2) * 0.5

      for j in range(len(weights)):
        weights[j] += learning_rate*error*sigmoid_derivative(net_input)*x_input[j]
    errors.append(total_error)
    #print(f"Epoch: {epoch+1}, Error: {total_error}")
    # print(f"{total_error} \t {error_threshold}")
    if(total_error < error_threshold):
      break
  return weights,errors

def test_single_layer(X, W):
    predictions = []
    for x in X:
        net_input = np.dot(x,W)
        output = sigmoid(net_input)
        predictions.append(output)
    return np.array(predictions)



if __name__ == "__main__":
  X = np.array(train_data)
  D = np.array(results)

  learning_rates = [0.01,0.1,0.05]
  epochs = [1000,100,5000]


  weights = []

  for lr,e in zip(learning_rates,epochs):
    print(lr,e)
    weights, errors = train(X,D,learning_rate=lr,epochs=e)

    plt.plot(errors)
    plt.xlabel("Epoka")
    plt.ylabel("Bląd")
    plt.show()

  predictions = test_single_layer(np.array(test_data),weights)
  print(predictions)
  predictions = test_single_layer(X,weights)
  print(predictions)