#ifndef NODE_H 
#define NODE_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    PROPERTY_INT,
    PROPERTY_FLOAT,
    PROPERTY_BOOL,
    PROPERTY_CHAR,
    PROPERTY_STRING,
} PropertyType;

typedef struct {
    PropertyType type;
    union {
        int i32;
        double f64;
        char* string;
        bool boolean;
    } value;
} PropertyValue;

typedef struct {
    char* key;
    PropertyValue* value;
} Property;

typedef struct {
    Property* properties;
    size_t count;
    size_t capacity;
} PropertyMap;

typedef struct {
    uint64_t id;
    PropertyMap* properties;
} Node;

#endif // !NODE_H
