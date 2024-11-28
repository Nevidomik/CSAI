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
float task_first(float x, int select);
float task_second(float z, int select);

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
            left_column = {"a", "b", "c"};
            right_column = {"1", "2", "3"};
        } else if(entries[entries_selected] == "while") {
            left_column = {"a", "b", "x"};
            right_column = {"1", "2", "5"};
        } else if(entries[entries_selected] == "do ... while") {
            left_column = {"a", "b", "d"};
            right_column = {"1", "2", "4"};
        }
    };
    auto menu = Menu(&entries, &entries_selected, option);



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
            vbox(std::move(left_elements)) | border, // Left column
            separator(),
            vbox(std::move(right_elements)) | border // Right column
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
                menu->Render(),      // Render menu
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

float task_first(float x = 0.6, int select = 0){
   float y, step_x = 1.5;
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
    return 0;
}

float task_second(float z = -2, int select = 0){
    ////
    float w, step_z = 0.5;

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

    return 0;
}