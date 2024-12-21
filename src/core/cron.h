#ifndef CRON_H
#define CRON_H

#include <string>
#include <vector>
#include <functional>

#include <time.h>

using namespace std;

class CronTime{
    private:
        vector<string> splitStr(string str, char delimiter = ' ');

        /** 
         * @return nullptr, for specific data 
         */
        function<bool(int)> func(string data);
        function<bool(int)> funcRange(int min, int max);
        function<bool(int)> funcDiv(int div);
        function<bool(int)> funcNum(vector<int> nums);

        function<bool(int)> minute = CronTime::funcRange(0, 59);
        function<bool(int)> hour = CronTime::funcRange(0, 23);
        function<bool(int)> monthday = CronTime::funcRange(1, 31);
        function<bool(int)> month = CronTime::funcRange(1, 12);
        function<bool(int)> weekday = CronTime::funcRange(0, 6);

    public:
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

#endif