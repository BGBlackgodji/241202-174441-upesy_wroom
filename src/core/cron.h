#include <string>
#include <vector>
#include <functional>

#include <time.h>

using namespace std;

class CronTime{
    private:
        vector<string> splitStr(string str, char delimiter = ' ');

        // [min, max, div]
        vector<int> splitData(string data);

    public:
        // min in range
        unsigned short min_minute = 0;
        unsigned short min_hour = 0;
        unsigned short min_monthday = 1;
        unsigned short min_month = 1;
        unsigned short min_weekday = 0;

        // max in range
        unsigned short max_minute = 59;
        unsigned short max_hour = 23;
        unsigned short max_monthday = 31;
        unsigned short max_month = 12;
        unsigned short max_weekday = 6;

        // divisible by ...
        unsigned short div_minute = 1;
        unsigned short div_hour = 1;
        unsigned short div_monthday = 1;
        unsigned short div_month = 1;
        unsigned short div_weekday = 1;
        
        CronTime();
        CronTime(string cronStr);
        
        bool operator==(const tm& timeinfo);
        bool operator!=(const tm& timeinfo);
};

class CronJobListener {
    public:
        string name;
        CronTime time;
        function<void(void)> callback;
        bool once;

        CronJobListener(string jobName, string cronTime, function<void(void)> jobCallback, bool offAfterCall);
};

class CronJob {
    private:
        static tm lastTick;
        static vector<CronJobListener> listener;

    public:
        static void tick();

        static void on(string name, string cronTime, function<void(void)> callback);
        static void once(string name, string cronTime, function<void(void)> callback);

        static void off(string name);
};