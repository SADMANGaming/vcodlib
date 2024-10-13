/*
   SG JSON CPP
   THIS FILE IS A PART OF VCODLIB

   CREATED BY SADMAN

   2024
*/

#include "sg_json.h"
#include <iostream>
#include <stdexcept>
#include <cctype>


void Json::skipWhitespace(const std::string& jsonString, size_t& pos) {
    while (pos < jsonString.size() && isspace(jsonString[pos])) {
        pos++;
    }
}


std::string Json::parseString(const std::string& jsonString, size_t& pos) {
    if (jsonString[pos] != '"') {
        throw std::runtime_error("Expected opening quotation for string");
    }
    pos++;

    std::string result;
    while (pos < jsonString.size() && jsonString[pos] != '"') {
        result += jsonString[pos++];
    }
    if (pos == jsonString.size()) {
        throw std::runtime_error("Unterminated string");
    }
    pos++;
    return result;
}

bool Json::parse(const std::string& jsonString) {
    size_t pos = 0;
    skipWhitespace(jsonString, pos);

    if (jsonString[pos] != '{') {
        throw std::runtime_error("Expected opening brace for JSON object");
    }
    pos++;

    while (pos < jsonString.size()) {
        skipWhitespace(jsonString, pos);

        if (jsonString[pos] == '}') {
            pos++;
            return true;
        }

        // Parse key
        std::string key = parseString(jsonString, pos);

        skipWhitespace(jsonString, pos);
        if (jsonString[pos] != ':') {
            throw std::runtime_error("Expected colon after key");
        }
        pos++;  // Skip the colon

        skipWhitespace(jsonString, pos);

        std::string value = parseString(jsonString, pos);

        data[key] = value;

        skipWhitespace(jsonString, pos);
        if (jsonString[pos] == ',') {
            pos++;
        }
    }

    return false;
}

bool Json::contains(const std::string& key) const {
    return data.find(key) != data.end();
}

std::string Json::getString(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Key not found in JSON object");
    }
}

void Json::print() const {
    for (const auto& pair : data) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
