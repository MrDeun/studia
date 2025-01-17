import numpy as np

test_subjects = [
    [-1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0],
    [1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0],
    [1.0, 1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0],
    [1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0,],
]


expected_results = [[0, 0], [1, 0], [1, 1], [0, 1]]


# Unipolar Sigmoid Activation Function
def sigmoid(x, beta=1):
    return 1 / (1 + np.exp(-beta * x))


# Derivative of the Sigmoid Function
def sigmoid_derivative(output, beta=1):
    return beta * output * (1 - output)


# Error Function
def compute_error(desired, output):
    return 0.5 * (desired - output) ** 2


# Sigmoidal Neuron Learning Algorithm
def sigmoidal_neuron_learning(
    X, D, eta=0.1, beta=1, max_epochs=1000, error_threshold=0.01
):
    """
    Sigmoidal neuron with unipolar activation.
    X: Input data (numpy array of shape [samples, features]).
    D: Desired output data (numpy array of shape [samples, 1]).
    eta: Learning rate (0 < eta <= 1).
    beta: Steepness of the activation function.
    max_epochs: Maximum number of epochs.
    error_threshold: Stop training when total error falls below this value.
    """
    n_samples, n_features = X.shape

    # Initialize weights (including bias as w_0)
    weights = np.random.randn(n_features + 1) * 0.01  # Small random weights
    X = np.c_[np.ones((n_samples, 1)), X]  # Add bias input (x_0 = 1)

    for epoch in range(max_epochs):
        total_error = 0

        for i in range(n_samples):
            x_i = X[i]  # Current input vector (including bias)
            d_i = D[i]  # Desired output

            # Compute the weighted sum (s) and neuron output
            s = np.dot(weights, x_i)
            output = sigmoid(s, beta)

            # Compute the error
            error = d_i - output
            total_error += compute_error(d_i, output)

            # Compute the gradient using the derivative of the sigmoid function
            gradient = eta * error * sigmoid_derivative(output, beta)

            # Update weights
            weights += gradient * x_i

        # Print the total error for monitoring
        print(f"Epoch {epoch+1}/{max_epochs}, Total Error: {total_error}")

        # Check convergence
        if total_error < error_threshold:
            print("Training Converged!")
            break

    return weights


# Example Usage
if __name__ == "__main__":
    # Define training data (X: input features, D: desired outputs)
    X = np.array(test_subjects)  #
    D = np.array([0, 1])  #

    # Train the sigmoidal neuron
    final_weights = sigmoidal_neuron_learning(
        X, D, eta=0.05, beta=1, max_epochs=10000, error_threshold=0.001
    )

    # Print final weights
    print("Final Weights (including bias):", final_weights)

    # Test the model
    print("\nTesting the trained neuron:")
    X_test = np.c_[np.ones((X.shape[0], 1)), X]  # Add bias input
    for x, d in zip(X_test, D):
        output = sigmoid(np.dot(final_weights, x), beta=1)
        print(f"Input: {x[1:]}, Desired: {d}, Output: {output:.4f}")
