#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "../env_loader.h"

using namespace std;

unordered_map<string, string> load_env_file(const string& fileName) {
    unordered_map<string, string> variables;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open env file " << fileName << endl;
        return variables;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string key, value;
        if (getline(iss, key, '=') && getline(iss, value)) {
            variables[key] = value;
        }
    }
    file.close();
    return variables;
}