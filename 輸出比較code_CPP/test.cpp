#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <cstdio>  // 加入此標頭檔

using namespace std;

void printFileContents(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Contents of " << filename << ":" << endl;
        cout << file.rdbuf();
        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }
}

int main() {
    cout << "Running test to compare outputs of a.cpp and b.cpp for inputs 1 to 3..." << endl;

    for (int input_number = 1; input_number <= 3; ++input_number) {
        string input_filename = "input" + to_string(input_number) + ".txt";
        cout << "Testing with input from " << input_filename << endl;

        // Compile a.cpp
        system("C:\\MinGW\\bin\\g++ -o a.exe a.cpp");  // 請更換成你的 g++ 路徑

        // Run a.cpp with input from input.txt and capture output to output_a.txt
        system((".\\a.exe < " + input_filename + " > output_a.txt").c_str());

        // Compile b.cpp
        system("C:\\MinGW\\bin\\g++ -o b.exe b.cpp");  // 請更換成你的 g++ 路徑

        // Run b.cpp with input from input.txt and capture output to output_b.txt
        system((".\\b.exe < " + input_filename + " > output_b.txt").c_str());

        // Print contents of output_a.txt and output_b.txt with line breaks
        printFileContents("output_a.txt");
        printFileContents("output_b.txt");

        // Compare outputs
        ifstream file_a("output_a.txt");
        ifstream file_b("output_b.txt");
        ostringstream content_a, content_b;

        content_a << file_a.rdbuf();
        content_b << file_b.rdbuf();

        // Compare line by line
        istringstream stream_a(content_a.str());
        istringstream stream_b(content_b.str());
        string line_a, line_b;
        int line_number = 1;

        cout << "Results for input " << input_number << ":" << endl;

        while (getline(stream_a, line_a) && getline(stream_b, line_b)) {
            if (line_a != line_b) {
                cerr << "Difference at line " << line_number << " for input " << input_number << ":" << endl;
                cerr << "a.cpp: " << line_a << endl;
                cerr << "b.cpp: " << line_b << endl;
                assert(false);  // or handle the difference accordingly
            } else {
                cout << "Line " << line_number << ": a.cpp: " << line_a << " | b.cpp: " << line_b << endl;
            }
            line_number++;
        }

        cout << "Test for input " << input_number << " passed!" << endl;

        // Append contents to new files
        ofstream result_file_a("result_output_a.txt", ios::app);  // ios::app 表示附加到文件的末尾
        result_file_a << "Results for input " << input_number << ":" << endl;
        result_file_a << content_a.str() << endl;
        result_file_a.close();

        ofstream result_file_b("result_output_b.txt", ios::app);
        result_file_b << "Results for input " << input_number << ":" << endl;
        result_file_b << content_b.str() << endl;
        result_file_b.close();
    }

    cout << "All tests passed!" << endl;

    return 0;
}
