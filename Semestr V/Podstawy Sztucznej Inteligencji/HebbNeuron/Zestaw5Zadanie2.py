import numpy as np


one = [
    -1.0,-1.0,1.0,
    -1.0,-1.0,1.0,
    -1.0,-1.0,1.0,
    -1.0,-1.0,1.0
]

four = [
    1.0,-1.0,1.0,
    1.0,1.0,1.0,
    -1.0,-1.0,1.0,
    -1.0,-1.0,1.0
]

import numpy as np

# Define the bipolar activation function
def bipolar_activation(x, beta=1):
    return (1 - np.exp(-beta * x)) / (1 + np.exp(-beta * x))

# Define the error function
def compute_error(d, y):
    return 0.5 * (d - y) ** 2

# Hebbian learning algorithm
def hebbian_learning(X, D, eta=0.001, beta=1, max_epochs=10000, error_threshold=0.01):
    n_samples, n_features = X.shape
    # Initialize weights to zero or random small values
    weights = np.random.rand(n_features) * 0.01
    theta = 0  # Bias term
    
    for epoch in range(max_epochs):
        total_error = 0  # Sum of errors for this epoch
        
        for i in range(n_samples):
            x_i = X[i]
            d_i = D[i]
            
            # Compute weighted input (sum) and output
            weighted_sum = np.dot(x_i, weights) + theta
            y_i = bipolar_activation(weighted_sum, beta)
            
            # Update weights using Hebbian rule
            weights += eta * d_i * x_i
            theta += eta * d_i  # Update bias term
            
            # Compute error for this sample
            error = compute_error(d_i, y_i)
            total_error += error
        
        # Print error for this epoch
        print(f"Epoch {epoch+1}/{max_epochs}, Total Error: {total_error}")
        
        # Check convergence
        if total_error < error_threshold:
            print("Converged!")
            break
    
    return weights, theta

# Example usage
if __name__ == "__main__":
    # Define training data
    # X: Input features (2 samples, 2 features each)
    X = np.array([one,four])
    
    # D: Desired outputs for the training samples
    D = np.array([-1,1])  # Desired outputs (bipolar)

    # Train the Hebbian neuron
    weights, theta = hebbian_learning(X, D, eta=0.001, beta=1, max_epochs=10000, error_threshold=0.01)
    
    # Print final weights and bias
    print("Final Weights:", weights)
    print("Final Bias (theta):", theta)
