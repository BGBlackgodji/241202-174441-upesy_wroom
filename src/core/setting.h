#ifndef SETTING_H
#define SETTING_H

#include <string>
#include <vector>
#include <ArduinoJson.h>
#include <components/box.h>
#include <components/display.h>

using namespace std;

const int boxNum = 15;

class AppDisplaySetting
{
public:
    int address = 0;
    int charactor = 0;
    int line = 0;

    AppDisplaySetting();

    void toJson(JsonObject &doc);
    void fromJson(const JsonObject &doc);
};

class AppBoxSetting
{
public:
    int servoPort = 0;
    string name = "";
    string cronString = "";

    AppBoxSetting();

    void toJson(JsonObject &doc);
    void fromJson(const JsonObject &doc);
};

class AppSetting
{
public:
    AppDisplaySetting display;
    vector<AppBoxSetting> box;

    AppSetting();

    void toJson(JsonDocument &doc);
    void fromJson(JsonDocument &doc);
};

extern AppSetting appSetting;

extern Display display;
extern vector<Box> box;

void loadSetting(AppSetting setting);

#endif
