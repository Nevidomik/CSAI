//Виконано згідно варіанту 5 методичних вказівок
//
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float Sum(short, short, short, short, float[], float[]); // функуія пошуку суми для першого завдання
vector<float> ChangeVector(vector<float>, float);        // функція множення елементів вектора на число

int main()
{
    // TASK 1 /////////////////////////
    float array_a[5] = {-1.1, 2.4, 5.6, -2.4, 0.5};
    float array_b[5] = {1.4, 3.6, 1.3, -2.1, -3.3};
    float x = 6.4;
    float z = -0.9;
    float result_first_task;

    // Задане в умові завдання рівння у програмному вигляді
    result_first_task = Sum(1, 5, 1, 3, array_a, array_b) / cos(x * z - 1.7) - cos(3.6 - pow(x, 2)) / Sum(2, 4, 2, 3, array_b, array_a) + Sum(2, 5, 3, 3, array_b, array_a) / cos(x - 0.3 * z);
    printf("=+=+=+ TASK 1 =+=+=+\nQ=(E[1->5] a^1 - b^3)/cos(x * z - 1.7) - cos(3.6 - x^2)/(E[2->4] b^2 - a^3) + (E[2->5] b^3 - a^3)/cos(x - 0.3 * z) = %f\n", result_first_task);
    // TASK 2 /////////////////////////////////

    vector<float> Vector = {3, 4.4, 5, 7.2};
    float real;

    // Вивід модифікованого і не модифікованого векторів
    // Введення числа для моження членів вектора
    printf("\n=+=+=+ TASK 2 =+=+=+\nInput real number : ");
    cin >> real;
    printf("\nVector : ");
    for (auto i : Vector)
        printf(" %.3f", i);
    Vector = ChangeVector(Vector, real);
    printf("\nAfter change Vector : ");
    for (auto i : Vector)
        printf(" %.3f", i);
    // TASK 3///////////////////////////////
    short size_array = 10;
    short array_R[size_array] = {5, 6, 7, 8, 4, 3, 2, 5, 9, 12};
    short result = 0;

    // Обчислення послідовного та паралельного опорів
    for (int i = 0; i < size_array; i++)
    {
        result += array_R[i];
    }
    printf("\n\n=+=+=+ TASK 2 =+=+=+\nSeries resistance equal : %i", result);

    float result_paralel = 0;
    for (int i = 0; i < size_array; i++)
    {
        result_paralel += (1.0 / array_R[i]);
    }
    printf("\nParalel resistance equal : %.3f", result_paralel);
}

float Sum(short lower_bound_summation, short upper_bound_summation, short exp_left, short exp_right, float left[5], float right[5])
{
    float result = 0;

    for (size_t i = lower_bound_summation; i < upper_bound_summation; i++)
    {
        result += pow(left[i], exp_left) - pow(right[i], exp_right);
    }

    return result;
}

vector<float> ChangeVector(vector<float> Vector, float mul_num)
{
    vector<float> ModifyVector;
    for (auto i : Vector)
        ModifyVector.push_back(i * mul_num);

    return ModifyVector;
}