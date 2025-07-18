#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

typedef enum {
    PROPERTY_INT,
    PROPERTY_FLOAT,
    PROPERTY_BOOL,
    PROPERTY_CHAR,
    PROPERTY_STRING,
} PropertyType;

typedef struct {
    char* key;
    PropertyType* value;
} Property;

typedef struct {
    Property* properties;
    size_t count;
    size_t capacity;
} PropertyMap;

typedef struct {
    uint64_t nodeId;
    PropertyMap* properties;
} Node;

#endif // !NODE_H
