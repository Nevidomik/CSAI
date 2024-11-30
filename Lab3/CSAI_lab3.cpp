#include <iostream>
#include <vector>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;

void view(float[], int);
vector<string> vectortostring(float[], int);
vector<string> vectortostring2(int);
float* sort_exchange(float[], int, int);
float* sort_bubble(float[], int, int);
float* sort_insert(float[], int, int);

int main(){
    int size_array;
    int choose_app;
    int type;


    cout << "Size array: ";
    cin >> size_array;

    float array[size_array];
    float sort_array[size_array];
    for(int i = 0; i < size_array; i++){
        cout << "Enter element [" << i << "] = ";
        cin >> array[i];
    }
    cout << "END\n\n";
    cout << "Choose App for calculation?" << endl;
    cout << "1 - sort exchange" << endl;
    cout << "2 - sort bubble" << endl;
    cout << "3 - sort insert" << endl;
    cout << "Enter : ";
    cin >> choose_app;
    cout << "Choose up sort or down sort:" << endl;
    cout << "1 - up sort" << endl;
    cout << "2 - down sort" << endl;
    cout << "Enter : ";
    cin >> type;
    switch(choose_app){
        case 1:
            view(sort_exchange(array, size_array, type), size_array);
            break;
        case 2:
            view(sort_bubble(array, size_array, type), size_array);
            break;
        case 3:
            view(sort_insert(array, size_array, type), size_array);
            break;
        default:
            break;
    }
}

float* sort_exchange(float arr[], int size_arr, int type){
    float temp;
    for(int i = 0; i < size_arr; i++){
        for(int j = 0; j < size_arr; j++){
            switch(type){
                case 1:
                    if(arr[i] < arr[j]){
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                    break;
                case 2:
                    if(arr[i] > arr[j]){
                        temp = arr[j];
                        arr[j] = arr[i];
                        arr[i] = temp;
                    }
                    break;
                default:
                    break;
            }

        }
    }
    return arr;
}

float* sort_bubble(float arr[], int size_arr, int type){
    float temp;
    bool flag = true;
    for(int i = 0; (i < size_arr) && flag; i++){
        flag = false;
        for(int j = 0; j < size_arr; j++){
            switch(type){
                case 1:
                    if(arr[j] > arr[i]){
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                        flag = true;
                    }
                    break;
                case 2:
                    if(arr[j] < arr[i]){
                        temp = arr[j];
                        arr[j] = arr[i];
                        arr[i] = temp;
                        flag = true;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    return arr;
}

float* sort_insert(float arr[], int size_arr, int type){
    float temp;
    int first;
    for(int i = size_arr - 1; i >= 0; i--){
        first = 0;
        for(int j = 0; j <= i; j++){
            switch(type){
                case 1:
                    if(arr[j] > arr[first]){
                        first = j;
                    }
                    temp = arr[first];
                    arr[first] = arr[i];
                    arr[i] = temp;
                    break;
                case 2:
                    if(arr[j] < arr[first]){
                        first = j;
                    }
                    temp = arr[first];
                    arr[first] = arr[i];
                    arr[i] = temp;
                    break;
                default:
                    break;
            }
        }
    }
    return arr;
}

void view(float arr[], int size_arr){
    vector<string> left_column, right_column;
    right_column = vectortostring(arr, size_arr);
    left_column = vectortostring2(size_arr);
    auto columns_renderer = Renderer([&] {
        // Build the left column
        Elements left_elements;
        for (const auto& item : left_column) {
            left_elements.push_back(text(item));
        }

        // Build the right column
        Elements right_elements;
        for (const auto& item : right_column) {
            right_elements.push_back(text(item));
        }

        // Combine columns and return
        return hbox({
            vbox(std::move(left_elements)), // Left column
            separator(),
            vbox(std::move(right_elements)), // Right column
        });
    });

    auto component = Container::Vertical({
        columns_renderer,
    });

        // Main renderer
    auto renderer = Renderer(component, [&] {
        return vbox({ 
            columns_renderer->Render(),
        }) | border;
    });

    // Start the interactive screen loop
    ScreenInteractive::FitComponent().Loop(renderer);
}

vector<string> vectortostring(float arr[], int size_arr){
    vector<string> convert;
    for(int i = 0; i < size_arr; i++){
        convert.push_back(to_string(arr[i]));
    }
    return convert;
}

vector<string> vectortostring2(int size){
    vector<string> convert;
    for(int i = 0; i < size; i++){
        convert.push_back(to_string(i + 1));
    }
    return convert;
}