#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>

using namespace std;

LARGE_INTEGER Frequency;
LARGE_INTEGER Ticks1, Ticks2;
double ElapsedTime;

const int SIZE_ARRAY = 5;
const int HIDDEN_NUMBER = 3;
const int OUTPUT_NUMBER = SIZE_ARRAY;

double Input_Test[SIZE_ARRAY] = {0.1, 0.1, 0.3, 0.1, 0.2};
double Output_Need[SIZE_ARRAY] = {0, 0, 1, 0, 0};

struct Neuron
{
    double weights[SIZE_ARRAY];
    double bias;
    double output_signal;
    double error_signal;
};

Neuron HIDDEN_LAYER[HIDDEN_NUMBER];
Neuron OUTPUT_LAYER[OUTPUT_NUMBER];

double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

void initialize_weights(Neuron layer[], int layer_size, int input_size)
{
    srand((unsigned)time(0));
    for (int i = 0; i < layer_size; i++)
    {
        for (int j = 0; j < input_size; j++)
        {
            layer[i].weights[j] = ((double)rand() / RAND_MAX) - 0.5; // Random weights [-0.5, 0.5]
        }
        layer[i].bias = ((double)rand() / RAND_MAX) - 0.5; // Random bias
    }
}

void forward_pass()
{
    // Hidden layer
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < SIZE_ARRAY; j++)
        {
            sum += HIDDEN_LAYER[i].weights[j] * Input_Test[j];
        }
        sum += HIDDEN_LAYER[i].bias;
        HIDDEN_LAYER[i].output_signal = sigmoid(sum);
    }

    // Output layer
    double sum_exp = 0.0;
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < HIDDEN_NUMBER; j++)
        {
            sum += OUTPUT_LAYER[i].weights[j] * HIDDEN_LAYER[j].output_signal;
        }
        sum += OUTPUT_LAYER[i].bias;
        OUTPUT_LAYER[i].output_signal = exp(sum); // Using softmax preparation
        sum_exp += OUTPUT_LAYER[i].output_signal;
    }

    // Normalize output (Softmax)
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        OUTPUT_LAYER[i].output_signal /= sum_exp;
    }
}

void backward_pass()
{
    // Output layer error
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        OUTPUT_LAYER[i].error_signal = Output_Need[i] - OUTPUT_LAYER[i].output_signal;
    }

    // Hidden layer error
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < OUTPUT_NUMBER; j++)
        {
            sum += OUTPUT_LAYER[j].error_signal * OUTPUT_LAYER[j].weights[i];
        }
        HIDDEN_LAYER[i].error_signal = HIDDEN_LAYER[i].output_signal * (1 - HIDDEN_LAYER[i].output_signal) * sum;
    }

    // Update weights for output layer
    double learning_rate = 0.1;
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        for (int j = 0; j < HIDDEN_NUMBER; j++)
        {
            OUTPUT_LAYER[i].weights[j] += learning_rate * OUTPUT_LAYER[i].error_signal * HIDDEN_LAYER[j].output_signal;
        }
        OUTPUT_LAYER[i].bias += learning_rate * OUTPUT_LAYER[i].error_signal;
    }

    // Update weights for hidden layer
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        for (int j = 0; j < SIZE_ARRAY; j++)
        {
            HIDDEN_LAYER[i].weights[j] += learning_rate * HIDDEN_LAYER[i].error_signal * Input_Test[j];
        }
        HIDDEN_LAYER[i].bias += learning_rate * HIDDEN_LAYER[i].error_signal;
    }
}

int main()
{
    initialize_weights(HIDDEN_LAYER, HIDDEN_NUMBER, SIZE_ARRAY);
    initialize_weights(OUTPUT_LAYER, OUTPUT_NUMBER, HIDDEN_NUMBER);
    ofstream weights_file("weights.txt");
    ofstream output_file1("output1.txt");
    ofstream output_file2("output2.txt");
    ofstream output_file3("output3.txt");
    ofstream output_file4("output4.txt");
    ofstream output_file5("output5.txt");
    ofstream epoch_file("epoch.txt");
    ofstream erorr_file("erorr.txt");
    cout.precision(3);

    double mse = 0; // what mse?
    QueryPerformanceFrequency(&Frequency);

    weights_file << "output weights \t \t" << "hidden weights \n";
    QueryPerformanceCounter(&Ticks1);

    for (int epoch = 0; epoch < 1000; epoch++)
    {
        epoch_file << epoch << "\n";
        mse = 0;
        forward_pass();
        backward_pass();
        for (int k = 0; k < OUTPUT_NUMBER; k++)
        {
            weights_file << OUTPUT_LAYER[k].weights[k] << "\t";
            weights_file << HIDDEN_LAYER[0].weights[k] << "\t";
            mse += pow((OUTPUT_LAYER[k].output_signal - Output_Need[k]), 2);
        }
        cout << "|" << OUTPUT_LAYER[0].output_signal << "\t";
        cout << "|" << OUTPUT_LAYER[1].output_signal << "\t";
        cout << "|" << OUTPUT_LAYER[2].output_signal << "\t";
        cout << "|" << OUTPUT_LAYER[3].output_signal << "\t";
        cout << "|" << OUTPUT_LAYER[4].output_signal << "\t";
        output_file1 << OUTPUT_LAYER[0].output_signal << "\n";
        output_file2 << OUTPUT_LAYER[1].output_signal << "\n";
        output_file3 << OUTPUT_LAYER[2].output_signal << "\n";
        output_file4 << OUTPUT_LAYER[3].output_signal << "\n";
        output_file5 << OUTPUT_LAYER[4].output_signal << "\n";
        cout << "|" << mse << "\t" << "|" << epoch << endl;
        erorr_file << mse << "\n";

        weights_file << endl;
        system("cls");
        cout << "----------------------------------learnig in process-------------------------" << endl;
        cout << "|-out 1-|-out 2-|-out 3-|-out 4-|-out 5-|-error-|-epochs---------------------" << endl;
    }
    cout << "----------------------------------end learning-------------------------------" << endl;
    system("cls");
    QueryPerformanceCounter(&Ticks2);
    cout << "----------------------------------learnig results----------------------------" << endl;

    cout << "Results after training:\n";
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        cout << "Output " << i << ": " << OUTPUT_LAYER[i].output_signal << endl;
    }
    // Input_Test[0] = 0.1;
    // Input_Test[1] = 0.5;
    // Input_Test[2] = 0.3;
    // Input_Test[3] = 0.2;
    // Input_Test[4] = 0.1;

    // for (int i = 0; i < SIZE_ARRAY; i++)
    // {
    //     forward_pass();
    //     cout << "Output " << i << ": " << OUTPUT_LAYER[i].output_signal << endl;
    // }

    output_file1.close();
    output_file2.close();
    output_file3.close();
    output_file4.close();
    output_file5.close();
    weights_file.close();
    epoch_file.close();
    erorr_file.close();

    ElapsedTime = (Ticks2.QuadPart - Ticks1.QuadPart) * 1000.0 / Frequency.QuadPart;
    cout << ElapsedTime << " ms.\n";

    return 0;
}

// #include <iostream>
// #include <cmath>
// #include <cstdlib>
// #include <ctime>
// #include <fsteram>

// using namespace std;

// const int SIZE_ARRAY = 5;
// const int HIDDEN_NUMBER = 3;
// const int OUTPUT_NUMBER = SIZE_ARRAY;

// double Input_Test[SIZE_ARRAY] = {0.1, 0.1, 0.3, 0.1, 0.2};
// double Output_Need[SIZE_ARRAY] = {0, 0, 1, 0, 0};

// struct Neuron
// {
//     double weights[SIZE_ARRAY];
//     double bias;
//     double output_signal;
//     double error_signal;
// };

// Neuron HIDDEN_LAYER[HIDDEN_NUMBER];
// Neuron OUTPUT_LAYER[OUTPUT_NUMBER];

// double sigmoid(double x)
// {
//     return 1.0 / (1.0 + exp(-x));
// }

// void initialize_weights(Neuron layer[], int layer_size, int input_size)
// {
//     srand((unsigned)time(0));
//     for (int i = 0; i < layer_size; i++)
//     {
//         for (int j = 0; j < input_size; j++)
//         {
//             layer[i].weights[j] = ((double)rand() / RAND_MAX) - 0.5; // Random weights [-0.5, 0.5]
//         }
//         layer[i].bias = ((double)rand() / RAND_MAX) - 0.5; // Random bias
//     }
// }

// void forward_pass()
// {
//     // Hidden layer
//     for (int i = 0; i < HIDDEN_NUMBER; i++)
//     {
//         double sum = 0.0;
//         for (int j = 0; j < SIZE_ARRAY; j++)
//         {
//             sum += HIDDEN_LAYER[i].weights[j] * Input_Test[j];
//         }
//         sum += HIDDEN_LAYER[i].bias;
//         HIDDEN_LAYER[i].output_signal = sigmoid(sum);
//     }

//     // Output layer
//     double sum_exp = 0.0;
//     for (int i = 0; i < OUTPUT_NUMBER; i++)
//     {
//         double sum = 0.0;
//         for (int j = 0; j < HIDDEN_NUMBER; j++)
//         {
//             sum += OUTPUT_LAYER[i].weights[j] * HIDDEN_LAYER[j].output_signal;
//         }
//         sum += OUTPUT_LAYER[i].bias;
//         OUTPUT_LAYER[i].output_signal = exp(sum); // Using softmax preparation
//         sum_exp += OUTPUT_LAYER[i].output_signal;
//     }

//     // Normalize output (Softmax)
//     for (int i = 0; i < OUTPUT_NUMBER; i++)
//     {
//         OUTPUT_LAYER[i].output_signal /= sum_exp;
//     }
// }

// void backward_pass()
// {
//     // Output layer error
//     for (int i = 0; i < OUTPUT_NUMBER; i++)
//     {
//         OUTPUT_LAYER[i].error_signal = Output_Need[i] - OUTPUT_LAYER[i].output_signal;
//     }

//     // Hidden layer error
//     for (int i = 0; i < HIDDEN_NUMBER; i++)
//     {
//         double sum = 0.0;
//         for (int j = 0; j < OUTPUT_NUMBER; j++)
//         {
//             sum += OUTPUT_LAYER[j].error_signal * OUTPUT_LAYER[j].weights[i];
//         }
//         HIDDEN_LAYER[i].error_signal = HIDDEN_LAYER[i].output_signal * (1 - HIDDEN_LAYER[i].output_signal) * sum;
//     }

//     // Update weights for output layer
//     double learning_rate = 0.1;
//     for (int i = 0; i < OUTPUT_NUMBER; i++)
//     {
//         for (int j = 0; j < HIDDEN_NUMBER; j++)
//         {
//             OUTPUT_LAYER[i].weights[j] += learning_rate * OUTPUT_LAYER[i].error_signal * HIDDEN_LAYER[j].output_signal;
//         }
//         OUTPUT_LAYER[i].bias += learning_rate * OUTPUT_LAYER[i].error_signal;
//     }

//     // Update weights for hidden layer
//     for (int i = 0; i < HIDDEN_NUMBER; i++)
//     {
//         for (int j = 0; j < SIZE_ARRAY; j++)
//         {
//             HIDDEN_LAYER[i].weights[j] += learning_rate * HIDDEN_LAYER[i].error_signal * Input_Test[j];
//         }
//         HIDDEN_LAYER[i].bias += learning_rate * HIDDEN_LAYER[i].error_signal;
//     }
// }

// int main()
// {
//     initialize_weights(HIDDEN_LAYER, HIDDEN_NUMBER, SIZE_ARRAY);
//     initialize_weights(OUTPUT_LAYER, OUTPUT_NUMBER, HIDDEN_NUMBER);
//     ofstream weights_file("weights.txt");
//     ofstream output_file1("output1.txt");
//     ofstream output_file2("output2.txt");
//     ofstream output_file3("output3.txt");
//     ofstream output_file4("output4.txt");
//     ofstream output_file5("output5.txt");
//     ofstream epoch_file("epoch.txt");
//     ofstream erorr_file("erorr.txt");

//     for (int epoch = 0; epoch < 5000; epoch++)
//     {
//         forward_pass();
//         backward_pass();
//     }

//     cout << "Results after training:\n";
//     for (int i = 0; i < OUTPUT_NUMBER; i++)
//     {
//         cout << "Output " << i << ": " << OUTPUT_LAYER[i].output_signal << endl;
//     }
//     Input_Test[0] = 0.1;
//     Input_Test[1] = 0.5;
//     Input_Test[2] = 0.3; 
//     Input_Test[3] = 0.2;
//     Input_Test[4] = 0.1;

//     for(int i = 0; i < SIZE_ARRAY; i++){
//         forward_pass();
//         cout << "Output " << i << ": " << OUTPUT_LAYER[i].output_signal << endl;
//     }

//     output_file1.close();
//     output_file2.close();
//     output_file3.close();
//     output_file4.close();
//     output_file5.close();
//     weights_file.close();
//     epoch_file.close();
//     erorr_file.close();

//     return 0;
// }
