#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <vector>
#include <string_view>

#include "ansi.hpp"

using namespace std;
using namespace chrono;

void fatalErr(const char* message)
{
    cerr << "Error: " << message << '\n';
    system("pause");
    exit(0);
}

milliseconds parse_time(int time, string suffix)
{
    transform(suffix.begin(), suffix.end(), suffix.begin(), tolower);

    if (!suffix.ends_with('s')) 
        suffix += 's';
    
    if (suffix == "seconds")
        return milliseconds(seconds(time));

    else if (suffix == "minutes")
        return milliseconds(minutes(time));

    else if (suffix == "hours")
        return milliseconds(hours(time));
    else
        fatalErr("Invalid time provided");
}

// this could probably be a lot simpler and faster but the same could be said about my caveman brain
milliseconds parse_precise(const string& str)
{
    // 0 = hour, 1 = minute, 2 = second
    int section = 0;
    int i       = 0;
    int size    = str.size();

    milliseconds ms{};
    string       store{};

    for (const char c : str)
    {
        i++;

        if (section > 2)
            break;

        if (c != ':')
            store += c;

        if (c == ':' || i == size)
        {
            int value = stoi(store);

            switch (section)
            {
            case 0:
                ms += hours(value);
                break;
            case 1:
                ms += minutes(value);
                break;
            case 2:
                ms += seconds(value);
                break;
            }

            section++;
            store.clear();

            continue;
        }
    }

    if (ms == 0ms)
        fatalErr("Could not parse time!");

    return ms;
}

string display_time(const milliseconds& ms)
{
    auto tp     = system_clock::now() + ms;
    time_t time = system_clock::to_time_t(tp);
    tm localtime;

    localtime_s(&localtime, &time);

    stringstream ss;

    ss << put_time(&localtime, "%r");

    return ss.str();
}

string format_time(const milliseconds& ms_time)
{
    auto count        = ms_time.count();
    auto ms_to_minute = count % 60000;
    auto ms_to_hour   = count % 3600000;
    auto hour         = count / 3600000;

    stringstream ss;

    ss << setfill('0')
        << setw(2)
        << hour
        << ':'
        << setw(2)
        << (int)ms_to_hour / 60000
        << ':'
        << setw(2)
        << (int)ms_to_minute / 1000;

    return ss.str();
}

template<typename T>
inline void update(T value, int offset = 1)
{
    cout << cli::cursorNextline(offset)
        << cli::eraseLine()
        << "Time remaining: "
        << value
        << cli::cursorPreviousline(offset);
}

void countdown(const milliseconds& future_time, const milliseconds& delay = 100ms)
{
    auto future = system_clock::now() + future_time;

    milliseconds remaining = 10ms;

    std::cout << cli::hide_cursor();

    while (remaining > 0ms)
    {
        this_thread::sleep_for(delay);

        remaining = duration_cast<milliseconds>(future - system_clock::now());

        if (remaining <= 0ms)
        {
            update(format_time(0ms));
            break;
        }

        update(format_time(remaining));
    }

    cout << cli::show_cursor();
}

milliseconds proccess_args(int argc, char* argv[])
{
    if (argc == 2)
        return parse_precise(argv[1]);

    milliseconds ms{};

    if (argc >= 3)
        ms = parse_time(atoi(argv[1]), argv[2]);

    if (argc == 6 && strcmp(argv[3], "and") == 0)
        ms += parse_time(atoi(argv[4]), argv[5]);

    return ms;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        fatalErr("invalid argument! examples: 5 minute | 1 hour and 30 minutes | 0:5:30");

    milliseconds ms = proccess_args(argc, argv);

    system("cls");

    cout << "Set a timer for " << cli::color(display_time(ms), cli::colors::yellow) << endl;

    countdown(ms);

    cout << cli::cursorNextline()
         << cli::eraseLine() 
         << cli::color("DING DONG!!! Press any key to stop", cli::colors::red);

    bool played = PlaySound(TEXT("alarm.wav"), NULL, SND_ASYNC | SND_LOOP);

    if (played)
        _getch();
    else
        cerr << cli::color("Unable to play sound file", cli::colors::red);
   
    return 0;
} 

