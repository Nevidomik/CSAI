#include <iostream>
#include <math.h>
#include <fstream>
#include <windows.h>

using namespace std;
const int MAX_NUMBER = 3;
const int INPUT_NUMBER = 1;
const int HIDDEN_NUMBER = 2;
const int OUTPUT_NUMBER = 1;
const int SIZE_ARRAY = 5;
double Input_Test[SIZE_ARRAY] = {0.1, 0.1, 0.3, 0.1, 0.2};
double Output_Need[SIZE_ARRAY] = {0, 0, 1, 0, 0};
double Temp_Need[SIZE_ARRAY];

LARGE_INTEGER Frequency;
LARGE_INTEGER Ticks1, Ticks2;
double ElapsedTime;

struct neuron
{
    double weights[MAX_NUMBER];
    double output_signal;
    double error_out;
    double delta_error;
};
neuron INPUT_LAYER[INPUT_NUMBER];
neuron HIDDEN_LAYER[HIDDEN_NUMBER];
neuron OUTPUT_LAYER[OUTPUT_NUMBER];

double sigmoid(double);
void run(int);
void output_layer_errors(int);
void hidden_layer_errors(void);
void input_layer_errors(void);
void output_weights(void);
void hidden_weights(void);
void input_weights(int);
void initialize_weights();

    int main(void)
{
    initialize_weights();
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

    for (int epoch_count = 0; epoch_count < 50000; epoch_count++)
    {
        epoch_file << epoch_count << "\n";
        mse = 0;
        for (int i = 0; i < OUTPUT_NUMBER; i++)
        {
            for (int k = 0; k < SIZE_ARRAY; k++)
            {
                run(k);
                output_layer_errors(k);
                hidden_layer_errors();
                output_weights();
                weights_file << OUTPUT_LAYER[i].weights[k] << "\t";
                hidden_weights();
                weights_file << HIDDEN_LAYER[i].weights[k] << "\t";
                mse += pow((OUTPUT_LAYER[i].output_signal - Output_Need[k]), 2);
                cout << "|" << OUTPUT_LAYER[0].output_signal << "\t";
                Temp_Need[k] = OUTPUT_LAYER[0].output_signal;
                if (k == 0)
                    output_file1 << OUTPUT_LAYER[0].output_signal << "\n";
                else if (k == 1)
                    output_file2 << OUTPUT_LAYER[0].output_signal << "\n";
                else if (k == 2)
                    output_file3 << OUTPUT_LAYER[0].output_signal << "\n";
                else if (k == 3)
                    output_file4 << OUTPUT_LAYER[0].output_signal << "\n";
                else if (k == 4)
                    output_file5 << OUTPUT_LAYER[0].output_signal << "\n";
            }
        }
        cout << "|" << mse << "\t" << "|" << epoch_count << endl;
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
    for (int k = 0; k < SIZE_ARRAY; k++)
    {
        cout << Input_Test[k] << "--->" << Temp_Need[k] << endl;
    }
    double test_values[SIZE_ARRAY] = {0.1, 0.5, 0.3, 0.2, 0.1};
    cout << "-------------------------------------run results-----------------------------" << endl;
    for (int k = 0; k < SIZE_ARRAY; k++)
    {
        run(k);
        cout << test_values[k] << "--->" << OUTPUT_LAYER[0].output_signal << "\t" << endl;
    }
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

double sigmoid(double x)
{
    double y = 1 / (1 + exp(-x));
    return y;
}
void run(int index)
{ // index is global k
    double sum;

    for (int i = 0; i < MAX_NUMBER; i++)
    {
        sum = 0;
        for (int j = 0; j < INPUT_NUMBER; j++)
        {
            sum += INPUT_LAYER[i].weights[j] * Input_Test[index];
        }
        INPUT_LAYER[i].output_signal = sigmoid(sum - INPUT_LAYER[i].delta_error);
    }
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        sum = 0;
        for (int j = 0; j < INPUT_NUMBER; j++)
        {
            sum += HIDDEN_LAYER[i].weights[j] * INPUT_LAYER[j].output_signal;
        }
        HIDDEN_LAYER[i].output_signal = sigmoid(sum - HIDDEN_LAYER[i].delta_error);
    }
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        sum = 0;
        for (int j = 0; j < HIDDEN_NUMBER; j++)
        {
            sum += OUTPUT_LAYER[i].weights[j] * HIDDEN_LAYER[j].output_signal;
        }
        OUTPUT_LAYER[i].output_signal = sigmoid(sum - OUTPUT_LAYER[i].delta_error);
    }
}

void output_layer_errors(int index)
{
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        OUTPUT_LAYER[i].error_out = Output_Need[index] - OUTPUT_LAYER[i].output_signal * (1 - OUTPUT_LAYER[i].output_signal);
    }
}

void hidden_layer_errors(void)
{
    double sum;
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        sum = 0;
        for (int j = 0; j < OUTPUT_NUMBER; j++)
        {
            sum += OUTPUT_LAYER[j].error_out * OUTPUT_LAYER[j].weights[i];
            HIDDEN_LAYER[i].error_out = HIDDEN_LAYER[i].output_signal * (1 - HIDDEN_LAYER[i].output_signal) * sum;
        }
    }
}

void input_layer_errors(void)
{
    double sum;
    for (int i = 0; i < MAX_NUMBER; i++)
    {
        sum = 0;
        for (int j = 0; j < INPUT_NUMBER; j++)
        {
            sum += HIDDEN_LAYER[j].error_out * HIDDEN_LAYER[j].weights[i];
            INPUT_LAYER[i].error_out = INPUT_LAYER[i].output_signal * (1 - INPUT_LAYER[i].output_signal) * sum;
        }
    }
}

void output_weights(void)
{
    double rate = 0.025;
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        for (int j = 0; j < HIDDEN_NUMBER; j++)
        {
            OUTPUT_LAYER[i].weights[j] += rate * OUTPUT_LAYER[i].error_out * HIDDEN_LAYER[j].output_signal;
            OUTPUT_LAYER[i].delta_error -= rate * OUTPUT_LAYER[i].error_out;
        }
    }
}
void hidden_weights(void)
{
    double rate = 0.025;
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        for (int j = 0; j < INPUT_NUMBER; j++)
        {
            HIDDEN_LAYER[i].weights[j] += rate * HIDDEN_LAYER[i].error_out * INPUT_LAYER[j].output_signal;
            HIDDEN_LAYER[i].delta_error -= rate * HIDDEN_LAYER[i].error_out;
        }
    }
}

void input_weights(int index)
{
    double rate = 0.025;
    for (int i = 0; i < INPUT_NUMBER; i++)
    {
        for (int j = 0; j < MAX_NUMBER; j++)
        {
            INPUT_LAYER[i].weights[j] += rate * INPUT_LAYER[i].error_out * Input_Test[index];
            INPUT_LAYER[i].delta_error -= rate * INPUT_LAYER[i].error_out;
        }
    }
}

void initialize_weights()
{
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < INPUT_NUMBER; i++)
    {
        for (int j = 0; j < MAX_NUMBER; j++)
        {
            INPUT_LAYER[i].weights[j] = ((double)rand() / RAND_MAX) * 2 - 1; // Від -1 до 1
        }
    }
    for (int i = 0; i < HIDDEN_NUMBER; i++)
    {
        for (int j = 0; j < INPUT_NUMBER; j++)
        {
            HIDDEN_LAYER[i].weights[j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
    for (int i = 0; i < OUTPUT_NUMBER; i++)
    {
        for (int j = 0; j < HIDDEN_NUMBER; j++)
        {
            OUTPUT_LAYER[i].weights[j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
}