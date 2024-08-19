#include <map>
#include <string>
#include <iostream>
#include <dpp/dpp.h>
#include <curl/curl.h>

#include "../utils.h"

std::string json_value_finder(const std::string& json, const std::string& key) {
    std::size_t start_pos = json.find("\"" + key + "\":");

    if (start_pos == std::string::npos) return "";

    start_pos = json.find(":", start_pos);
    std::size_t end_pos = json.find(",", start_pos);

    if (end_pos == std::string::npos)
        end_pos = json.find("}", start_pos);

    std::string value = json.substr(start_pos + 1, end_pos - start_pos - 1);

    if (value.front() == '\"' && value.back() == '\"')
        value = value.substr(1, value.size() - 2);

    return value;
}

std::string map_to_json(const std::map<std::string, std::string>& data) {
    std::string json = "{";
    bool first = true;
    for (const auto& pair : data) {
        if (!first) {
            json += ",";
        }
        json += "\"" + pair.first + "\":\"" + pair.second + "\"";
        first = false;
    }
    json += "}";
    return json;
}

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CURLcode fetch_curl_request(CURL* curl, const std::string& url, std::string& readBuffer) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    return curl_easy_perform(curl);
}

void http_post_request(const std::string& url, std::map<std::string, std::string>& data) {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        std::string postData = map_to_json(data); // Convierte el map a JSON o a un formato de parámetros

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postData.size());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

std::string http_get_request(const std::string& url) {
    CURL* curl;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        CURLcode res = fetch_curl_request(curl, url, readBuffer);
        (res != CURLE_OK)?
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl << url << std::endl:
            std::cout << std::endl;
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}