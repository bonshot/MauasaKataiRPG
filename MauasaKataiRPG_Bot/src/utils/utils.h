#include <map>
#include <string>

#ifndef __UTILS_H__
#define __UTILS_H__

/**
* @brief A function that finds a value in a json string
* @param json: The json string -> string&
* @param key: The key of the value that will be found -> string&
* @return string: The value of the key
**/
std::string json_value_finder(const std::string& json, const std::string& key);

/** 
* @brief A function that converts a map that represents a json, to a string in the json format
* @param map that it will be converted to json -> map<string, string>
* @return string: The json in a string
**/
std::string map_to_json(const std::map<std::string, std::string>& data);

/**
* @brief A function that makes a request to an api and returns the json response using the dpp::http_request constructor
* @param url: The url of the api that will be requested -> string&
* @return string: The json response of the api
**/
void http_post_request(const std::string& url, std::map<std::string, std::string>& data);

/**
 * @brief A function that makes a request to an api and returns the json response using the dpp::http_request constructor
 * @param url: The url of the api that will be requested -> string&
 * @return string: The json response of the api
**/
std::string http_get_request(const std::string& url);


#endif