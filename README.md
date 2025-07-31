# `database-cpp`

A very simple database (inspired by MongoDB) and JSON-ish serializer and deserializer. Written in C++ for learning.

⚠️ **Important:** There is no intent for this to be maintained, this is just a small learning project.

For instance, there is minimal to no safety checks for parsing JSON.

## Concept

### `DataType`

Currently supports `String`, `Boolean`, `Integer` (signed).

### Setup

The idea of `Scheme` is to establish a base structure of the table, i.e. names and data types of the columns.

A scheme currently doesn't do anything, but can be created like so:

```c++
Scheme scheme = {
    {
        {"name", DataType::String},
        {"notes", DataType::String},
        {"active", DataType::Boolean},
        {"id", DataType::Integer}
    }
};

FrostBase db = FrostBase{scheme};
```

### Creating an object

```c++
Object person1 = {
    {"name", "Felix"},
    {"notes", "Developer"},
    {"active", true},
    {"id", 123}
};
```

Add it ergonomically like:

```c++
db + person1;
```

### JSON API

**JSON.h**

Serialize or deserialize a single `Object`:


```c++
std::string fromObject(Object object)
Object toObject(std::string json)
```

**FrostBase.h**

Batch serialize or deserialize data:

```c++
std::string toJson();
void fromJson(std::string json);
```

### View in console

Latter can be used to view all contents of the database:

```c++
void printObject(Object object);
void printObjects();
```