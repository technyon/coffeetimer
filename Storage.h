#pragma once

#include "FS.h"
#include "SPIFFS.h"

struct Config
{
    char signature[9];
    float duration;
};

class Storage
{
public:
    Storage();
    virtual ~Storage() = default;

    float duration();
    void setDuration(float value);

    void save();

private:
    char* signature = "Espresso";

    void load();
    void initializeConfig();

    Config _config;
};
