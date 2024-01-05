#include <iostream>
#include <cstdlib>
#include <cstdio> // 添加這個頭文件
using namespace std;

int main() {
    string file_name = "hi.cpp";
    string executable_name = file_name.substr(0, file_name.find_last_of("."));

    // 編譯cpp檔案
    string compile_command = "g++ " + file_name + " -o " + executable_name;
    int compile_result = system(compile_command.c_str());

    if (compile_result == 0) {
        // 使用 fopen 來打開檔案
        FILE *input = fopen("input.txt", "r+");
        if (input != nullptr) {
            // 使用 fscanf 從檔案中讀取值
            string input_string;
            if (fscanf(input, "%s", &input_string) == 1) {
                // 使用 printf 打印值，也可以根據需要調整
                printf("==============================\n>>>input = %s\n==============================\n>>output:\n", input_string);

                // 透過檔案串流提供輸入給執行檔
                string execute_command = executable_name;
                string full_command = execute_command + " < input.txt";
                system(full_command.c_str());

                // 關閉檔案串流
                fclose(input);
            } 
            else {
                cout << "#fscanf error" << endl;
                fclose(input);
            }
        } else {
            cout << "#cant open file" << endl;
        }
    } 
    else {
        cout << "#compile error " << file_name << " fail" << endl;
    }

    return 0;
}
