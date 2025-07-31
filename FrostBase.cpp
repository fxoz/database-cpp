//
// Created by Lynx on 2025-07-30.
//

#include "FrostBase.h"
#include <sstream>
#include <iostream>

#include "JSON.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define KEY     "\e[4;37m"

std::string typeToString(DataType type) {
    switch (type) {
        case DataType::Boolean: return "bool";
        case DataType::Integer: return "int";
        case DataType::String: return "str";
    }
    return "err";
}

std::string typeToStringColored(DataType type) {
    switch (type) {
        case DataType::Boolean: return MAGENTA "bool" RESET;
        case DataType::Integer: return BLUE "int"  RESET;
        case DataType::String: return GREEN "str" RESET;
    }
    return RED "error" RESET;
}

std::string FrostBase::valueToString(const Value& value) {
    return std::visit([](const auto& v) {
        std::ostringstream oss;
        oss << std::boolalpha << v;
        return oss.str();
    }, value);
}

void FrostBase::printHeader() {
    for (const auto& [name, type] : scheme) {
        std::stringstream ss;
        ss << "[" << name << " " << typeToStringColored(type) << "]";
        std::string text = ss.str();

        std::cout << text << " ";
    }
    std::cout << std::endl;

}

void FrostBase::printObject(Object object) {
    for (const auto& [name, value] : object) {
        std::stringstream ss;
        ss << "[" << KEY << name << RESET << " " << RESET << valueToString(value) << "]";
        std::string text = ss.str();

        std::cout << text << " ";
    }
}

void FrostBase::printObjects() {
    for (const Object& object : storage) {
        printObject(object);
        std::cout << std::endl;
    }
}


void FrostBase::insert(const Object& object) {
    // TODO - type checks
    storage.emplace_back(object);
}

void FrostBase::exportFile() {
    return;
}

std::string FrostBase::toJson() {
    std::stringstream ss;
    ss << "[";
    int i = 0;
    for (const Object& object : storage) {
        ss << JSON::fromObject(object);
        if (i+1 != storage.size()) { // add comma for everything but last item
            ss << ",";
        }
        i++;
    }
    ss << "]";
    return ss.str();
}

void FrostBase::fromJson(std::string json) {
    // TODO - error checking
    bool contentStarted = false;
    std::string objectJson;
    for (char c : json) {
        if (!contentStarted) {
            if (c == '[' || c == ' ') {
                continue;
            }
        }
        contentStarted = true;
        objectJson += c;

        if (c == '}') {
            insert(JSON::toObject(objectJson));
            objectJson = "";
        }
    }
}
