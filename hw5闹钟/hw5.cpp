#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <list>
#include <assert.h>

using namespace std;

string __time2str(int timeH,int timeM)
{
    string hour, minute;
    hour = to_string(timeH);
    if (timeH < 10)hour = "0" + hour;
    minute = to_string(timeM);
    if (timeM < 10)minute = "0" + minute;
    return hour + ":" + minute;
}
string time2str(int time)
{
    return __time2str(time / 60, time % 60);
}
class Alarm
{
public:
    enum AlarmType
    {
        Repeat,
        Snooz
    };
    Alarm(int time, AlarmType type, string name) :setTime(time), alarmtype(type), alarmName(name) {}
    // other functions
//   virtual void Trigger() = 0;
    int setTime;//时间戳
    AlarmType alarmtype;
    string alarmName;
};

class RepeatableAlarm;

class SnoozeableAlarm;

class AlarmClock
{
public:
    // constructors and destructor
    AlarmClock() :currentTime(0) {}
    // other functions
    void AddAlarm(Alarm* alarm);
    void TimeElapse();

private:

    list<Alarm*> alarms;
    // other member variables
    int currentTime;
};

void AlarmClock::AddAlarm(Alarm* alarm)
{
    alarms.push_back(alarm);
}

void AlarmClock::TimeElapse()
{
    for (list<Alarm*>::iterator it = alarms.begin(); it!=alarms.end(); it++)
    {
        if (currentTime == (*it)->setTime)
        {
            if ((*it)->alarmtype==Alarm::Repeat)
            {
                cout << "Alarm " + (*it)->alarmName + " has triggered at " + time2str(currentTime) + "."<<endl;
            }
            else
            {
                cout << "Alarm " + (*it)->alarmName + " has triggered at " + time2str(currentTime) + ". Snooze ? (Y / N)" << endl;
                string choice;
                cin >> choice;
                if (choice == "Y")
                {
                    (*it)->setTime += 10;
                }
                else
                {
                    alarms.erase(it--);
                }
            }
        }
    }
    currentTime++;
    if (currentTime > 24 * 60)currentTime = 0;
}

/**************** Input function ******************/
void Input(AlarmClock& clock)
{
    int numberofAlarmsToAdd;
    cin >> numberofAlarmsToAdd;
    for (int i = 0; i < numberofAlarmsToAdd; i++)
    {
        string type, time, alarmName;
        cin >> type >> time>> alarmName;
        int timeH, timeM;
        timeH = stoi(time.substr(0, 2));
        timeM = stoi(time.substr(3, 2));
        if (type == "R")
        {
            Alarm *alarm=new Alarm(timeH * 60 + timeM, Alarm::Repeat, alarmName);
            clock.AddAlarm(alarm);
        }
        else
        {
            Alarm* alarm = new Alarm(timeH * 60 + timeM, Alarm::Snooz, alarmName);
            clock.AddAlarm(alarm);
        }
    }
}

int main()
{
    AlarmClock clock;
    for (int days = 0; days < 3; days++)
    {
        cout << "Do you want to add any alarms?" << endl;
        Input(clock);
        for (int minute = 0; minute < 24 * 60; minute++)
        {
            clock.TimeElapse();
        }
        cout << "A day has elapsed." << endl;
    }
}
