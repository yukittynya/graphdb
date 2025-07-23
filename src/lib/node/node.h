#ifndef NODE_H 
#define NODE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    PROPERTY_BOOL,
    PROPERTY_CHAR,
    PROPERTY_FLOAT,
    PROPERTY_INT,
    PROPERTY_STRING,
} PropertyType;

typedef struct {
    PropertyType type;
    union {
        int i32;
        double f64;
        char c;
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

PropertyValue* createPropertyValue(PropertyType type, void* data); 
Property* createProperty(char* key, PropertyType type, void* data);
PropertyMap* createProprtyMap(Property properties[], size_t capacity);

#endif // !NODE_H
