#include "setting.h"

AppDisplaySetting::AppDisplaySetting() : address(0), charactor(0), line(0) {}

void AppDisplaySetting::toJson(JsonObject &doc)
{
    doc["address"] = address;
    doc["charactor"] = charactor;
    doc["line"] = line;
}

void AppDisplaySetting::fromJson(const JsonObject &doc)
{
    address = doc["address"];
    charactor = doc["charactor"];
    line = doc["line"];
}

AppBoxSetting::AppBoxSetting() {}

void AppBoxSetting::toJson(JsonObject &doc)
{
    doc["servoPort"] = servoPort;
    doc["name"] = name;
    doc["cronString"] = cronString;
}

void AppBoxSetting::fromJson(const JsonObject &doc)
{
    servoPort = doc["servoPort"];
    name = doc["name"].as<string>();
    cronString = doc["cronString"].as<string>();
}

AppSetting::AppSetting()
{
    display = AppDisplaySetting();
    box = vector<AppBoxSetting>(boxNum);
}

void AppSetting::toJson(JsonDocument &doc)
{
    JsonObject displayObj = doc.createNestedObject("display");
    display.toJson(displayObj);

    JsonArray boxArr = doc.createNestedArray("box");
    for (int i = 0; i < boxNum; i++)
    {
        JsonObject boxObj = boxArr.createNestedObject();
        box[i].toJson(boxObj);
        boxArr[i].set(boxObj);
    }
}

void AppSetting::fromJson(JsonDocument &doc)
{
    display.fromJson(doc["display"]);

    JsonArray boxArr = doc["box"].as<JsonArray>();
    for (int i = 0; i < boxNum; i++)
    {
        box[i].fromJson(boxArr[i]);
    }
}

AppSetting appSetting = AppSetting();

Display display = Display();
vector<Box> box = vector<Box>(boxNum);

void loadSetting(AppSetting setting)
{
    appSetting = setting;

    display = Display(
        setting.display.address,
        setting.display.charactor,
        setting.display.line);

    for (int i = 0; i < boxNum; i++)
    {
        AppBoxSetting boxSetting = setting.box[i];

        box[i] = Box::create(
            boxSetting.servoPort,
            boxSetting.name,
            boxSetting.cronString);
    }
}
