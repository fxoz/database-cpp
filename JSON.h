//
// Created by Lynx on 2025-07-31.
//

#ifndef JSON_H
#define JSON_H
#include "FrostBase.h"

class JSON {
public:
    static std::string fromObject(Object object);
    static Object toObject(std::string json);
};

#endif //JSON_H
