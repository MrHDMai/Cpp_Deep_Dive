#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sigmoid activation
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

// Predict the output for a sample using current weights
double predict(const vector<double>& x, const vector<double>& weights, double bias) {
    double linear_sum = bias;
    for (size_t i = 0; i < x.size(); ++i)
        linear_sum += x[i] * weights[i];
    return sigmoid(linear_sum);
}

// Train logistic regression using gradient descent
void train(const vector<vector<double>>& X, const vector<int>& y,
           vector<double>& weights, double& bias,
           double lr = 0.01, int epochs = 1000) {
    
    int n = X.size();
    int m = X[0].size();  // features

    weights.assign(m, 0.0);
    bias = 0.0;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        vector<double> grad_w(m, 0.0);
        double grad_b = 0.0;

        for (int i = 0; i < n; ++i) {
            double pred = predict(X[i], weights, bias);
            double error = pred - y[i];

            for (int j = 0; j < m; ++j)
                grad_w[j] += error * X[i][j];
            grad_b += error;
        }

        // Update weights and bias
        for (int j = 0; j < m; ++j)
            weights[j] -= lr * grad_w[j] / n;
        bias -= lr * grad_b / n;
    }
}

// Main function to test
int main() {
    vector<vector<double>> X = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    };
    vector<int> y = {0, 0, 0, 1}; // AND logic

    vector<double> weights;
    double bias;

    train(X, y, weights, bias, 0.1, 1000);

    for (const auto& sample : X) {
        double prob = predict(sample, weights, bias);
        cout << "Input: (" << sample[0] << "," << sample[1] << ") -> "
             << "Prediction: " << (prob >= 0.5 ? 1 : 0) << " (Prob = " << prob << ")\n";
    }

    return 0;
}
