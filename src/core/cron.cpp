#include "cron.h"

#include <api/ntime.h>

#include <sstream>

vector<string> CronTime::splitStr(string str, char delimiter)
{
    vector<string> arr;

    istringstream stream(str);
    string token;

    while (getline(stream, token, delimiter))
    {
        arr.push_back(token);
    }

    return arr;
}

function<bool(int)> CronTime::func(string data)
{
    if (data == "*")
    {
        return nullptr;
    }

    vector<string> token = splitStr(data, '/');
    if (token.size() == 2 && token[0] == "*")
    {
        return CronTime::funcDiv(
            stoi(token[1])
        );
    }

    token = splitStr(data, '-');
    if (token.size() == 2)
    {
        return CronTime::funcRange(
            stoi(token[0]),
            stoi(token[1])
        );
    }

    token = splitStr(data, ',');

    vector<int> intToken;
    for (int i = 0; i < token.size(); i++) {
        intToken.push_back(
            stoi(token[i])
        );
    }

    return CronTime::funcNum(intToken);
}
function<bool(int)> CronTime::funcRange(int min, int max)
{
    return [&](int n) -> bool
    {
        return n >= min && n <= max;
    };
}

function<bool(int)> CronTime::funcDiv(int div)
{
    return [&](int n) -> bool
    {
        return n % div == 0;
    };
}

function<bool(int)> CronTime::funcNum(vector<int> nums)
{
    return [&](int n) -> bool
    {
        for (int i = 0; nums.size(); i++)
        {
            if (nums[i] == n)
                return true;
        }

        return false;
    };
}
CronTime::CronTime() {}

CronTime::CronTime(string cronStr)
{
    vector<string> content = splitStr(cronStr);

    if (content.size() != 5)
        return;

    for (int i = 0; i < content.size(); i++)
    {
        string data = content[i];

        function<bool(int)> callback = CronTime::func(data);
        if (callback == nullptr) continue;

        switch (i)
        {
        case 0:
        {
            minute = callback;
            break;  
        }
        case 1:
        {
            hour = callback;
            break;
        }
        case 2:
        {
            monthday = callback;
            break;
        }
        case 3:
        {
            month = callback;
            break;
        }
        case 4:
        {
            weekday = callback;
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

bool CronTime::operator==(const tm &timeinfo)
{
    return
        CronTime::minute(timeinfo.tm_min) &&
        CronTime::hour(timeinfo.tm_hour) &&
        CronTime::monthday(timeinfo.tm_mday) &&
        CronTime::month(timeinfo.tm_mon) &&
        CronTime::weekday(timeinfo.tm_wday);
}

bool CronTime::operator!=(const tm &timeinfo)
{
    return !operator==(timeinfo);
}

CronJobListener::CronJobListener(string jobName, string cronTime, function<void(void)> jobCallback, bool offAfterCall)
{
    name = jobName;
    time = CronTime(cronTime);
    callback = jobCallback;
    once = offAfterCall;
}

tm CronJob::lastTick;
vector<CronJobListener> CronJob::listener;

void CronJob::tick()
{
    tm timeinfo = NetworkTime::get();

    if (timeinfo.tm_min == lastTick.tm_min)
        return;
    lastTick = timeinfo;

    vector<string> rmJob;

    for (int i = 0; i < listener.size(); i++)
    {
        CronJobListener job = listener[i];

        if (job.time != timeinfo)
            continue;
        job.callback();

        if (!job.once)
            continue;
        rmJob.push_back(job.name);
    }

    for (int j = 0; j < rmJob.size(); j++)
    {
        off(rmJob[j]);
    }
}

void CronJob::on(string name, string cronTime, function<void(void)> callback)
{
    CronJobListener job(name, cronTime, callback, false);

    listener.push_back(job);
}

void CronJob::once(string name, string cronTime, function<void(void)> callback)
{
    CronJobListener job(name, cronTime, callback, true);

    listener.push_back(job);
}

void CronJob::off(string name)
{
    int i = 0;
    while (i != listener.size())
    {
        CronJobListener job = listener[i];

        if (job.name == name)
        {
            listener.erase(listener.begin() + i);
            continue;
        }

        i++;
    }
}
