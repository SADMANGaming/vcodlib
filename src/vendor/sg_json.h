/*
   SG JSON HEADER
   THIS FILE IS A PART OF VCODLIB

   CREATED BY CHATGPT
   SOME BS ADDED BY SADMAN

   2024
*/

#ifndef SIMPLE_JSON_H
#define SIMPLE_JSON_H

#include <map>
#include <string>

class Json {
public:
    bool parse(const std::string& jsonString);

    bool contains(const std::string& key) const;

    std::string getString(const std::string& key) const;

    void print() const;

private:
    std::map<std::string, std::string> data;

    std::string parseString(const std::string& jsonString, size_t& pos);
    void skipWhitespace(const std::string& jsonString, size_t& pos);
};

#endif // SG_JSON
