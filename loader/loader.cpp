#include "loader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct model load_model(const char *file_name) {
    model self {};

    // Open the file
    ifstream inputFile(file_name);

    // Check if the file is open successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
    }

    // Read the floats from the file into a vector
    vector<float> floatArray;
    float value;

    // Read each line from the file
    string line;
    while (getline(inputFile, line)) {
        // Skip lines that start with "//"
        if (line.substr(0, 2) == "//") {
            continue;
        }

        // Process the line and extract float values
        istringstream iss(line);
        while (iss >> value) {
            floatArray.push_back(value);
        }
    }

    // Close the file
    inputFile.close();

    // Convert the vector to an array
    int n = (int) floatArray.size();
    float arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = floatArray[i];
    }

    // Print the loaded floats
    cout << "Loaded Floats: ";
    for (float floatValue : arr) {
        cout << floatValue << " ";
    }
    cout << endl;

    self.vao = vao_create();
    self.vbo = vbo_create(GL_ARRAY_BUFFER, true);
    vao_bind(self.vao);
    vbo_buffer(self.vbo, arr, 0, sizeof(arr));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    self.gpu_data_length = (int) (sizeof(arr) / sizeof(float) / 8);
    cout << "There are: " << (int) (sizeof(arr) / sizeof(float) / 8) << " in this triangle" << endl;
    return self;
}

void draw_model(model model_to_draw) {
    vao_bind(model_to_draw.vao);
    glDrawArrays(GL_TRIANGLES, 0, model_to_draw.gpu_data_length);
}
void destroy_model(model model_to_destroy) {
    vao_destroy(model_to_destroy.vao);
    vbo_destroy(model_to_destroy.vbo);
}
