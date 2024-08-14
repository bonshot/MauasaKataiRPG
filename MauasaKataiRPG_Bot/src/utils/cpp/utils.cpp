#include <map>
#include <string>
#include <dpp/dpp.h>
#include <curl/curl.h>

#include "../utils.h"

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

std::string http_get_request(const std::string& url) {
    CURL* curl;
    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        CURLcode res = fetch_curl_request(curl, url, readBuffer);
        (res != CURLE_OK)?
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl:
            std::cout << "Request: " << readBuffer << std::endl;
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return readBuffer;
}

void http_post_request(const std::string& url, std::map<std::string, std::string>& data) {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}