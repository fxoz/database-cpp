#include <unordered_map>
#include "FrostBase.h"
#include <iostream>

#include "JSON.h"

int main() {
    Scheme scheme = {
        {
            {"name", DataType::String},
            {"notes", DataType::String},
            {"active", DataType::Boolean},
            {"id", DataType::Integer}
        }
    };

    FrostBase db = FrostBase{scheme};

    Object object1 = {
        {"name", "Felix"},
        {"notes", "Developer"},
        {"active", true},
        {"id", 123}
    };


    Object object3 = JSON::toObject(R"({"notes":"Developer", "name": "Felix", "num": 1234, "abc":"xyz", "another_num": -1337, "hi": "hello", "hey": 1, "active": true, "inactive": false})");
    std::string object3_json = JSON::fromObject(object3);
    std::cout << object3_json << std::endl;
    Object object3_again = JSON::toObject(object3_json);

    //std::cout << JSON::fromObject(object1);

    db + object1;

    Object object2 = {
        {"name", "The Weeknd"},
        {"notes", "Singer"},
        {"active", true},
        {"id", 1337}
    };

    db + object2;

    db + object3;

    db.printHeader();
    db.printObjects();

    std::cout << db.toJson();

    return 0;
}
