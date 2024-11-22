#include <iostream>
#include <cmath>

using namespace std;

float function_one(float x);
float function_two_one(float z);
float function_two_two(float z);

int main(){
    cout << "lab 2" << endl;

    float y, x = 0.6, step_x = 1.5;
    int n = 6;
///
    for(int i = 0; i < n; n++){
        if (x >= 0.6) {
            y = function_one(x);
            x += step_x;
        } else {
            break;
        }
    }

    while(n != 0){
        if(x >= 0.6) {
            y = function_one(x);
            x += step_x;
            n--;
        } else {
            break;
        }
    }

    do {
        if(x >= 0.6) {
            y = function_one(x);
            x += step_x;
            n--;
        } else {
            break;
        }
    } while (n != 0);
////
    x = 0.2;
    step_x = 0.8;

    for(; x <= 10; x += step_x){
        y = function_one(x);
    }

    while(x <= 10){
        y = function_one(x);
        x += step_x;
    }

    do {
        y = function_one(x);
        x += step_x;
    } while(x <= 10);
////
    float w, z = -2, step_z = 0.5;

    for(; z <= 3; z += step_z){
        if (-2 <= z && z <= 0.5){
            w = function_two_one(z);
        }
        else if(0.5 < z){
            w = function_two_two(z);
        }
    }

    while(z <= 3){
        if (-2 <= z && z <= 0.5){
            w = function_two_one(z);
            z += step_z;
        }
        else if(0.5 < z){
            w = function_two_two(z);
            z += step_z;
        }
    }

    do{
        if (-2 <= z && z <= 0.5){
            w = function_two_one(z);
            z += step_z;
        }
        else if(0.5 < z){
            w = function_two_two(z);
            z += step_z;
        }
    } while(z <= 3);

}

float function_one(float x){
    return (x + cos(2 * x)) / (x + 2);
}
float function_two_one(float z){
    return (z - sin(z));
}
float function_two_two(float z){
    return (atan(z - 0.3));
}