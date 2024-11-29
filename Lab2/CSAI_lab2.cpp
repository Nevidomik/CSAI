#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace std;
using namespace ftxui;

float function_one(float x);
float function_two_one(float z);
float function_two_two(float z);
std::vector<float> task_first(float, int, string);
std::vector<float> task_second(float, int);
std::vector<string> vectortostring(vector<float>);
std::vector<string> vectortostring2(int);

//right and left is MIXED UP
int main(){
    //variables, vectors, components
    vector<string> tab_values {
        "Task 1",
        "Task 2",
    };
    int tab_selected = 0;
    auto tab_toggle = Toggle(&tab_values, &tab_selected);

    vector<string> entries {
        "for",
        "while",
        "do ... while",
    };
    int entries_selected = 0;


    vector<string> left_column;
    vector<string> right_column;

    string input_subtask = "a";
    auto subtask_input = Input(&input_subtask, "Enter a or b: ");
    string input_x = "0";
    auto variable_input = Input(&input_x, "Enter x: ");

    MenuOption option;
    option.on_enter = [&]{
        int x;
        if(entries[entries_selected] == "for"){
            left_column = vectortostring(task_first(stof(input_x), 1, input_subtask));
            right_column = vectortostring2(left_column.size());
        } else if(entries[entries_selected] == "while") {
            left_column = vectortostring(task_first(stof(input_x), 2, input_subtask));
            right_column = vectortostring2(left_column.size());
        } else if(entries[entries_selected] == "do ... while") {
            left_column = vectortostring(task_first(stof(input_x), 3, input_subtask));
            right_column = vectortostring2(left_column.size());
        }
    };
    auto menu = Menu(&entries, &entries_selected, option);

    MenuOption option2;
    option2.on_enter = [&]{
        int x;
        if(entries[entries_selected] == "for"){
            left_column = vectortostring(task_second(stof(input_x), 1));
            right_column = vectortostring2(left_column.size());
        } else if(entries[entries_selected] == "while") {
            left_column = vectortostring(task_second(stof(input_x), 2));
            right_column = vectortostring2(left_column.size());
        } else if(entries[entries_selected] == "do ... while") {
            left_column = vectortostring(task_second(stof(input_x), 3));
            right_column = vectortostring2(left_column.size());
        }
    };
    auto menu2 = Menu(&entries, &entries_selected, option2);



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
            vbox(std::move(right_elements)) | border, // Left column
            separator(),
            vbox(std::move(left_elements)) | border // Right column
        });
    });

    // Tab container to handle tabs
    auto tab_container = Container::Tab({
        Renderer([&] {
            return vbox({
                menu->Render(),      // Render menu
                separator(),
                variable_input->Render(),
                separator(),
                subtask_input->Render(),
                separator(),
                columns_renderer->Render(), // Render columns
            });
        }),
        Renderer([&] {
            return vbox({
                menu2->Render(),      // Render menu
                separator(),
                variable_input->Render(),
                separator(),
                columns_renderer->Render(), // Render columns
            });
        }),
    }, &tab_selected);

    // Vertical container
    auto component = Container::Vertical({
        tab_toggle,
        menu,
        menu2,
        variable_input,
        subtask_input,
        columns_renderer,
    });

    // Main renderer
    auto renderer = Renderer(component, [&] {
        return vbox({
            tab_toggle->Render(), // Render toggle
            separator(),
            tab_container->Render(), // Render tab content
        }) | border;
    });

    // Start the interactive screen loop
    ScreenInteractive::Fullscreen().Loop(renderer);

 /////  

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

vector<float> task_first(float x = 0.6, int select = 0, string subtask = "c"){
    float step_x = 1.5;
    int n = 6;
    vector<float> y;
///
    if(subtask == "a"){
        switch(select){
            case 1:
                for (int i = 0; i < n; n++){
                    if (x >= 0.6){
                        y.push_back(function_one(x));
                        x += step_x;
                    } else {
                        break;
                    }
                }
                break;
            case 2:
                while (n != 0){
                    if (x >= 0.6){
                        y.push_back(function_one(x));
                        x += step_x;
                        n--;
                    } else {
                        break;
                    }
                }
                break;
            case 3:
                do{
                    if (x >= 0.6){
                        y.push_back(function_one(x));
                        x += step_x;
                        n--;
                    } else {
                        break;
                    }
                } while (n != 0);
                break;
            default:
                y.push_back(0);
                break;
        }
    } else if (subtask == "b"){
        step_x = 0.8;
        switch (select){
            case 1:
                for (; x <= 10; x += step_x){
                    y.push_back(function_one(x));
                }
                break;
            case 2:
                while (x <= 10){
                    y.push_back(function_one(x));
                    x += step_x;
                }
                break;
            case 3:
                do{
                    y.push_back(function_one(x));
                    x += step_x;
                } while (x <= 10);
                break;
            default:
                y.push_back(0);
                break;
        }
    } else {
        y.push_back(0);
    }

    return y;
}

vector<float> task_second(float z = -2, int select = 0){
    ////
    float step_z = 0.5;
    vector<float> w;
    switch(select){
        case 1:
            for(; z <= 3; z += step_z){
                if (-2 <= z && z <= 0.5){
                    w.push_back(function_two_one(z));
                }
                else if(0.5 < z){
                    w.push_back(function_two_two(z));
                }
            }
            break;
        case 2:
            while(z <= 3){
                if (-2 <= z && z <= 0.5){
                    w.push_back(function_two_one(z));
                    z += step_z;
                }
                else if(0.5 < z){
                    w.push_back(function_two_two(z));
                    z += step_z;
                }
            }
            break;
        case 3:
            do{
                if (-2 <= z && z <= 0.5){
                    w.push_back(function_two_one(z));
                    z += step_z;
                }
                else if(0.5 < z){
                    w.push_back(function_two_two(z));
                    z += step_z;
                }
            } while(z <= 3);
            break;
        default:
            w.push_back(0);
            return w;   
    }
    return w;
}

vector<string> vectortostring(vector<float> vect){
    vector<string> convert;
    for(float i: vect){
        convert.push_back(to_string(i));
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