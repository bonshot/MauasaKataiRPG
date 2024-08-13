#include <unordered_map>
#include <string>

#ifndef __ENV_LOADER_H__
#define __ENV_LOADER_H__

/**
* A function that loads a .env file and returns a map with the variables.
* If the file does not exist, it will return an empty map.
* the format of the .env is: VARIABLE_NAME=VARIABLE_VALUE
* @param fileName: The name of the file to be loaded -> const string& 
* @return The map with the variables -> unordered_map<string, string>
**/
std::unordered_map<std::string, std::string> load_env_file(const std::string& fileName);

#endif