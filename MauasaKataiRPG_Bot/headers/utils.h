#ifndef __UTILS_H__
#define __UTILS_H__

/*
* A function that converts a map that represents a json, to a string in the json format
* @param std::map<std::string, std::string>: The map to be converted to json
* @return string: The json in a string
*/
std::string map_to_json(const std::map<std::string, std::string>& data);

#endif