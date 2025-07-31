//
// Created by Lynx on 2025-07-31.
//

#include "JSON.h"

#include <iostream>
#include <sstream>
#include <string>

#include "FrostBase.h"


std::string JSON::fromObject(Object object) {
    std::stringstream ss;
    ss << "{";
    int i = 0;

    for (const auto& [name, value] : object) {
        std::string valueString = FrostBase::valueToString(value);

        if (std::holds_alternative<std::string>(value)) { // "string"
            valueString = "\"" + valueString + "\"";
        }

        ss << "\"" << name  << "\":" << valueString;

        if (i+1 != object.size()) { // add comma for everything but last item
            ss << ",";
        }
        i++;
    }

    ss << "}";
    return ss.str();
}

Object JSON::toObject(std::string json) {
    // TODO - error checking
    Object object = {};

    bool inKey = false;
    bool soonValue = false; // : has been seen
    bool inValue = false;
    std::string key;
    char lastChar;

    std::string value_str;
    bool value_bool;

    bool isValueInt = false;
    bool isValueBool = false;

    for (char c : json) {
        if ((c == ' ' || c == ',') && !inValue) // ignore whitespace
            continue;

        if (soonValue && c == 't') { // true
            inValue = true;
            isValueBool = true;
            value_bool = true;
        }

        if (soonValue && c == 'f') { // false
            inValue = true;
            isValueBool = true;
            value_bool = false;
        }

        if (soonValue && !inValue) {
            if (std::isdigit(c) || c == '-') { // number values
                inValue = true;
                isValueInt = true;
            }
        }

        if (!soonValue && !inValue) { // key parsing
            if (lastChar == '"' && !inKey && c != ':') { // begin key
                inKey = true;
            }
            if (c == '"' && inKey) { // end key
                inKey = false;
            }
        }

        if (lastChar == '"' && soonValue) { // begin value
            inValue = true;
        }

        bool endOfString = c == '"';
        bool endOfNumber = isValueInt && !(std::isdigit(c) || c == '-');
        bool endOfBool = isValueBool && c == 'e';

        if (inValue && (endOfString || endOfNumber || endOfBool)) { // end value
            inValue = false;
            soonValue = false;

            // INSERT KEY & VALUE
            if (isValueInt) {
                object.insert({key, std::stoi(value_str)});
            }
            else if (isValueBool) {
                object.insert({key, value_bool});
            } else {
                object.insert({key, value_str});
            }

            // reset
            value_str = "";
            key = "";
            isValueInt = false;
            isValueBool = false;
        }

        if (c == ':' && !inKey && !inValue) // a stray : means value is following
            soonValue = true;

        if (inKey) {
            key += c;
        }

        if (inValue) {
            value_str += c;
        }

        //std::cout << "[" << c << "] inKey: " << inKey << " inValue: " << inValue << " soonValue: " << soonValue << "" << "" << "\n";
        lastChar = c;
    }

    return object;
}
