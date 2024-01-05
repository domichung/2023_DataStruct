#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const int MAX_SELLERS = 6;

void generateTestData(ofstream &file, int numCommands) {
    srand(time(0)); 

    vector<string> products;
    vector<string> sellers;

    for (int i = 0; i < numCommands * 2; ++i) {
        string name = "";
        for (int j = 0; j < rand() % 10 + 1; ++j) {
            char c = 'a' + rand() % 26;
            if (rand() % 2 == 0) {
                c = toupper(c);
            }
            name += c;
        }

        if (i % 2 == 0) {
            products.push_back(name);
        } else {
            sellers.push_back(name);
        }
    }

    file << "5\n"; 

    for (int i = 0; i < numCommands; ++i) {
        int commandType = rand() % 4 + 1;

        switch (commandType) {
            case 1: {
                string product = products[rand() % products.size()];
                string seller = sellers[rand() % sellers.size()];
                int price = rand() % 100 + 1;
                file << "insert " << product << " " << seller << " " << price << "\n";
                break;
            }
            case 2: {
                string product = products[rand() % products.size()];
                file << "search " << product << "\n";
                break;
            }
            case 3: {
                string product = products[rand() % products.size()];
                file << "buy " << product << "\n";
                break;
            }
            case 4:
                file << "sort\n";
                break;
        }
    }

    file << "report\n";
}

int main() {
    ofstream outputFile("inputowo.txt");

    if (outputFile.is_open()) {
        generateTestData(outputFile, 1000); 
        outputFile.close();
        cout << "測資生成成功。\n";
    } else {
        cerr << "無法開啟檔案。\n";
    }

    return 0;
}
