#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Activation Functions
double relu(double x)
{
    return (x > 0) ? x : 0;
}

double relu_derivative(double x)
{
    return (x > 0) ? 1 : 0;
}

void softmax(const vector<double> &input, vector<double> &output)
{
    double sum = 0.0;
    for (double val : input)
    {
        sum += exp(val);
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        output[i] = exp(input[i]) / sum;
    }
}

// Neural Network Parameters
const int INPUT_SIZE = 5;
const int HIDDEN_SIZE = 6;
const int OUTPUT_SIZE = 5;
const double LEARNING_RATE = 0.01;

// Network Layers
double input_layer[INPUT_SIZE];
double hidden_layer[HIDDEN_SIZE];
double output_layer[OUTPUT_SIZE];

// Weights and Biases
double input_to_hidden[HIDDEN_SIZE][INPUT_SIZE];
double hidden_bias[HIDDEN_SIZE];
double hidden_to_output[OUTPUT_SIZE][HIDDEN_SIZE];
double output_bias[OUTPUT_SIZE];

// Initialize Weights and Biases
void initialize_weights()
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        for (int j = 0; j < INPUT_SIZE; j++)
        {
            = ((double)rand() / RAND_MAX) - 0.5; // Random values between -0.5 and 0.5
        }
        hidden_bias[i] = 0.0;
    }
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            hidden_to_output[i][j] = ((double)rand() / RAND_MAX) - 0.5; // Random values between -0.5 and 0.5
        }
        output_bias[i] = 0.0;
    }
}

// Forward Pass
void forward_pass()
{
    // Input to Hidden Layer
    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        hidden_layer[i] = hidden_bias[i];
        for (int j = 0; j < INPUT_SIZE; j++)
        {
            hidden_layer[i] += input_layer[j] * input_to_hidden[i][j];
        }
        hidden_layer[i] = relu(hidden_layer[i]);
    }

    // Hidden to Output Layer
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        output_layer[i] = output_bias[i];
        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            output_layer[i] += hidden_layer[j] * hidden_to_output[i][j];
        }
    }

    // Apply Softmax to Output Layer
    vector<double> output_vector(output_layer, output_layer + OUTPUT_SIZE);
    vector<double> softmax_output(OUTPUT_SIZE);
    softmax(output_vector, softmax_output);
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        output_layer[i] = softmax_output[i];
    }
}

// Backward Pass
void backward_pass(int correct_index)
{
    double output_error[OUTPUT_SIZE];
    double hidden_error[HIDDEN_SIZE];

    // Output Error
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        output_error[i] = output_layer[i] - (i == correct_index ? 1.0 : 0.0);
    }

    // Update Hidden to Output Weights and Biases
    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            hidden_to_output[i][j] -= LEARNING_RATE * output_error[i] * hidden_layer[j];
        }
        output_bias[i] -= LEARNING_RATE * output_error[i];
    }

    // Hidden Layer Error
    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        hidden_error[i] = 0.0;
        for (int j = 0; j < OUTPUT_SIZE; j++)
        {
            hidden_error[i] += output_error[j] * hidden_to_output[j][i];
        }
        hidden_error[i] *= relu_derivative(hidden_layer[i]);
    }

    // Update Input to Hidden Weights and Biases
    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        for (int j = 0; j < INPUT_SIZE; j++)
        {
            input_to_hidden[i][j] -= LEARNING_RATE * hidden_error[i] * input_layer[j];
        }
        hidden_bias[i] -= LEARNING_RATE * hidden_error[i];
    }
}

// Train the Network
void train(vector<vector<double>> &training_data, vector<int> &labels, int epochs)
{
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double total_loss = 0.0;
        for (size_t i = 0; i < training_data.size(); i++)
        {
            // Load input
            for (int j = 0; j < INPUT_SIZE; j++)
            {
                input_layer[j] = training_data[i][j];
            }

            // Forward and Backward Pass
            forward_pass();
            backward_pass(labels[i]);

            // Calculate Loss
            double correct_output = output_layer[labels[i]];
            total_loss -= log(correct_output);
        }
        if (epoch % 100 == 0)
        {
            cout << "Epoch " << epoch << ", Loss: " << total_loss / training_data.size() << endl;
        }
    }
}

// Test the Network
int predict(vector<double> &input)
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        input_layer[i] = input[i];
    }
    forward_pass();

    // Find the index of the maximum value in the output layer
    int max_index = 0;
    for (int i = 1; i < OUTPUT_SIZE; i++)
    {
        if (output_layer[i] > output_layer[max_index])
        {
            max_index = i;
        }
    }
    return max_index;
}

int main()
{
    initialize_weights();

    // Training Data: Each row is an input, and the label is the index of the maximum value
    vector<vector<double>> training_data = {
        {0.1, 0.2, 0.3, 0.4, 0.5},
        {0.9, 0.8, 0.7, 0.6, 0.5},
        {0.2, 0.5, 0.1, 0.3, 0.4},
        {0.4, 0.3, 0.9, 0.2, 0.1},
        {0.3, 0.1, 0.4, 0.8, 0.2}};
    vector<int> labels = {4, 0, 1, 2, 3}; // Correct index for each row

    train(training_data, labels, 1000);

    // Test the network
    vector<double> test_input = {0.3, 0.6, 0.2, 0.1, 0.4};
    int prediction = predict(test_input);

    cout << "Predicted index of the largest value: " << prediction << endl;

    return 0;
}