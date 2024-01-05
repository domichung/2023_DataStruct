#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio> // 添加這個頭文件
using namespace std;

int main() {

    //檔名
    string file_name = "hi.cpp";
    string executable_name = file_name.substr(0, file_name.find_last_of("."));    
    string compile_command = "g++ " + file_name + " -o " + executable_name;
    int compile_result = system(compile_command.c_str());
    
    if ( compile_result != 0 ){
        cout << "#compile error " << file_name << " fail" << endl;
        exit;
    }
    
    FILE *input = fopen( "input.txt" , "r");
    
    char s[];
    while ( fgets( s , sizeof(s) , input ) ){
        string hold_string = s;
        printf(hold_string);
    }
        
    
            // string input_string;
            // if (fscanf(input, "%s", &input_string) == 1) {
                
            //     printf("==============================\n>>input: \n%s\n==============================\n>>output:\n", input_string);

            //     string execute_command = executable_name;
            //     string full_command = execute_command + " < input.txt";
            //     system(full_command.c_str());

            //     // 關閉檔案串流
            //     fclose(input);
            // } 
            // else {
            //     cout << "#fscanf error" << endl;
            //     fclose(input);
            // }
        
    

    return 0;
}
