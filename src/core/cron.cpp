#include "cron.h"

#include <api/ntime.h>

#include <sstream>

vector<string> CronTime::splitStr(string str, char delimiter)
{
    vector<string> arr;

    istringstream stream(str);
    string token;

    int idx = 0;
    while (getline(stream, token, delimiter))
    {
        arr[idx++] = token;
    }

    return arr;
}

vector<int> CronTime::splitData(string data)
{
    if (data == "*")
    {
        return vector<int>{-1, -1, -1};
    }

    vector<string> token = splitStr(data, '/');
    if (token.size() == 2 && token[0] == "*")
    {
        return vector<int>{-1, -1, stoi(token[1])};
    }

    token = splitStr(data, '-');
    if (token.size() == 2)
    {
        return vector<int>{stoi(token[0]), stoi(token[1]), -1};
    }

    int ndata = stoi(data);
    return vector<int>{ndata, ndata, -1};
}

CronTime::CronTime() {}

CronTime::CronTime(string cronStr)
{
    vector<string> content = splitStr(cronStr);

    if (content.size() != 5)
        return;

    for (int i = 0; i < content.size(); i++)
    {
        vector<int> min_max_div = splitData(content[i]);

        switch (i)
        {
        case 0:
        {
            if (min_max_div[0] != -1) min_minute = min_max_div[0];
            if (min_max_div[1] != -1) max_minute = min_max_div[1];
            if (min_max_div[2] != -1) div_minute = min_max_div[2];
            break;
        }
        case 1:
        {
            if (min_max_div[0] != -1) min_hour = min_max_div[0];
            if (min_max_div[1] != -1) max_hour = min_max_div[1];
            if (min_max_div[2] != -1) div_hour = min_max_div[2];
            break;
        }
        case 2:
        {
            if (min_max_div[0] != -1) min_monthday = min_max_div[0];
            if (min_max_div[1] != -1) max_monthday = min_max_div[1];
            if (min_max_div[2] != -1) div_monthday = min_max_div[2];
            break;
        }
        case 3:
        {
            if (min_max_div[0] != -1) min_month = min_max_div[0];
            if (min_max_div[1] != -1) max_month = min_max_div[1];
            if (min_max_div[2] != -1) div_month = min_max_div[2];
            break;
        }
        case 4:
        {
            if (min_max_div[0] != -1) min_weekday = min_max_div[0];
            if (min_max_div[1] != -1) max_weekday = min_max_div[1];
            if (min_max_div[2] != -1) div_weekday = min_max_div[2];
            break;
        }
        }
    }
}

bool CronTime::operator==(const tm &timeinfo)
{
    return
    (timeinfo.tm_min >= min_minute)
    && (timeinfo.tm_hour >= min_hour)
    && (timeinfo.tm_mday >= min_monthday)
    && (timeinfo.tm_mon >= min_month)
    && (timeinfo.tm_wday >= min_weekday)

    && (timeinfo.tm_min <= max_minute)
    && (timeinfo.tm_hour <= max_hour)
    && (timeinfo.tm_mday <= max_monthday)
    && (timeinfo.tm_mon <= max_month)
    && (timeinfo.tm_wday <= max_weekday)

    && (timeinfo.tm_min % div_minute == 0)
    && (timeinfo.tm_hour % div_hour == 0)
    && (timeinfo.tm_mday % div_monthday == 0)
    && (timeinfo.tm_mon % div_month == 0)
    && (timeinfo.tm_wday % div_weekday == 0);
}

bool CronTime::operator!=(const tm &timeinfo)
{
    return !operator==(timeinfo);
}

CronJobListener::CronJobListener(string jobName, string cronTime, function<void(void)> jobCallback, bool offAfterCall) {
    name = jobName;
    time = CronTime(cronTime);
    callback = jobCallback;
    once = offAfterCall;
}

vector<CronJobListener> CronJob::listener;

void CronJob::tick()
{
    tm timeinfo = NetworkTime::get();

    vector<string> rmJob;

    for (int i = 0; i < listener.size(); i++) {
        CronJobListener job = listener[i];

        if (job.time != timeinfo) continue;
        job.callback();

        if (!job.once) continue;
        rmJob.push_back(job.name);
    }

    for (int j = 0; j < rmJob.size(); j++) {
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
    while (i != listener.size()) {
        CronJobListener job = listener[i];

        if (job.name == name) {
            listener.erase(listener.begin() + i);
            continue;
        }

        i++;
    }
}
