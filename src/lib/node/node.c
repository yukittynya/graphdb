#include "node.h"

#include <stdlib.h>
#include <string.h>

PropertyValue* createPropertyValue(PropertyType type, void* data) {
    if (data == NULL) {
        return NULL;
    }

    PropertyValue* result = (PropertyValue*) malloc(sizeof(PropertyValue));

    if (result == NULL) {
        return NULL;
    }

    result -> type = type;

    switch (type) {
        case PROPERTY_BOOL:
            result -> value.boolean = *(bool*) data;
            break;

        case PROPERTY_CHAR:
            result -> value.c = *(char*) data;
            break;

        case PROPERTY_FLOAT:
            result -> value.f64 = *(double*) data;
            break;

        case PROPERTY_INT:
            result -> value.i32 = *(int*) data;
            break;

        case PROPERTY_STRING:
            result -> value.string = (char*) malloc(strlen((char*) data) + 1);

            if (result -> value.string == NULL) {
                free(result -> value.string);

                return NULL;
            }

            strcpy(result -> value.string, (char *) data);
            break;

        default:
            free(result);
            return NULL;
    }

    return result;
}

Property* createProperty(char* key, PropertyType type, void* data) {
    if (key == NULL || data == NULL) {
        return NULL;
    }

    Property* result = (Property*) malloc(sizeof(Property));

    strcpy(result -> key, key);
    result -> value = createPropertyValue(type, data);

    return result;
}

PropertyMap* createProprtyMap(Property* properties, size_t capacity) {
    PropertyMap* map = (PropertyMap*) malloc(sizeof(PropertyMap));

    map -> properties = properties;
    map -> count = 0;
    map -> capacity = capacity;

    return map;
}
