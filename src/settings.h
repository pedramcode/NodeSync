#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct
{
    char *node_name;
    unsigned int port;
    unsigned int workers;
} settings_t;

#endif