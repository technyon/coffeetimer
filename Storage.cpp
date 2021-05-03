#include "Storage.h"
#include "Arduino.h"


Storage::Storage()
{
    if(!SPIFFS.begin(true))
    {
        Serial.println(F("SPIFFS Mount Failed"));
        initializeConfig();
    }

    load();
}

void Storage::load()
{
    File file = SPIFFS.open("/cfg", FILE_READ);

    if(!file || file.isDirectory())
    {
        Serial.println(F("- failed to open file for reading"));
        initializeConfig();
        return;
    }

    size_t bytes = file.read((uint8_t*)&_config, sizeof(_config));

    if(bytes == 0)
    {
        initializeConfig();
    }

    Serial.print(F("Read "));
    Serial.print(bytes);
    Serial.println(F("from file."));

    file.close();

    _config._isDirty = false;
}

void Storage::save()
{
    if(!_config._isDirty) return;

    File file = SPIFFS.open("/cfg", FILE_WRITE);
    if(!file)
    {
        Serial.println(F("- failed to open file for writing"));
        return;
    }

    if(file.write((uint8_t *)&_config, sizeof(_config)))
    {
        Serial.println(F("- file written"));
    } else {
        Serial.println(F("- write failed"));
    }
    file.close();

    _config._isDirty = false;
}

void Storage::initializeConfig()
{
    Serial.println("No valid config found. Initializing with default values.");
    for(int i=0; i< sizeof(_config.signature); i++)
    {
        _config.signature[i] = signature[i];
    }
    _config.duration = 5;
}

float Storage::duration()
{
    return _config.duration;
}

void Storage::setDuration(float value)
{
    if(_config.duration != value)
    {
        _config.duration = value;
        _config._isDirty = true;
    }
}
