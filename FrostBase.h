//
// Created by Lynx on 2025-07-30.
//

#ifndef FROSTBASE_H
#define FROSTBASE_H

#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

enum class DataType {
    String,
    Integer,
    Boolean,
};

typedef std::variant<std::string, bool, int> Value;
typedef std::unordered_map<std::string, Value> Object;
typedef std::unordered_map<std::string, DataType> Scheme;

class FrostBase {
public:
    Scheme scheme;
    std::vector<Object> storage;

    explicit FrostBase(Scheme s) {
        scheme = std::move(s);
        storage = {};
    }

    void operator+ (const Object object) {
        insert(object);
    }

    static std::string valueToString(const Value &value);

    void printHeader();

    std::string toJson();

    void fromJson(std::string json);

    static void printObject(Object object);
    void printObjects();

    void insert(const Object& object);
    void exportFile();
};

#endif //FROSTBASE_H
