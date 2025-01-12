import numpy as np
import matplotlib.pyplot as plt
import random

# Binary representations of the digits 1, 4, 7, 0

error_threshold = 0.001

data = {
    1: [0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1],
    4: [1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1],
    7: [1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1],
    0: [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1],
}

labels = {1: [1, 1], 4: [1, 0], 7: [0, 0], 0: [0, 1]}

X = np.array(list(data.values()))  # Inputs
Y = np.array(list(labels.values()))  # Targets


def step_function(x, beta=1.0):
    return 1 / (1 + np.exp(-beta * x))


def train_single_layer_nn(X, Y, learning_rate=0.1, epochs=100):
    np.random.seed(0)  # For reproducibility
    num_samples, num_features = X.shape
    num_outputs = Y.shape[1]

    # Initialize weights and biases
    W = np.random.uniform(-1, 1, (num_outputs, num_features))
    b = np.random.uniform(-1, 1, num_outputs)

    errors = []

    for epoch in range(epochs):
        total_error = 0
        for x, y in zip(X, Y):
            # Forward pass
            net_input = np.dot(W, x) + b
            output = step_function(net_input)

            # Compute error
            error = y - output
            total_error += np.sum(error**2)

            # Update weights and biases (Perceptron Learning Rule)
            W += learning_rate * np.outer(error, x)
            b += learning_rate * error

        errors.append(total_error)
        print(f"Epoch: {epoch+1}, Error: {total_error}")
        if(total_error < error_threshold):
            break

    return W, b, errors


def test_single_layer_nn(X, W, b):
    predictions = []
    for x in X:
        net_input = np.dot(W, x) + b
        output = step_function(net_input)
        predictions.append(output)
    return np.array(predictions)


# Train the network with different hyperparameters
learning_rates = [0.1, 0.01, 0.5]
epochs = [1000,100,500]

for i in range(len(learning_rates)):
    W, b, errors = train_single_layer_nn(X, Y, learning_rate=learning_rates[i], epochs=epochs[i])

    # Plot the error convergence
    plt.plot(errors, label=f"Learning Rate = {learning_rates[i]}")

    plt.title("Error Convergence for Different Learning Rates")
    plt.xlabel("Epochs")
    plt.ylabel("Total Error")
    plt.legend()
    plt.show()

    # Test the network

    predictions = test_single_layer_nn(X, W, b)
    print("Predictions:", predictions)
    print("Targets:", Y)
