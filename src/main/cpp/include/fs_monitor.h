//#pragma once
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <thread>
//#include <ev.h>

#include <inotifytools/inotifytools.h>
#include <inotifytools/inotify.h>

using namespace std;

class FsMonitor {
    public:

        // register file/directory path and event mask.
        bool Init(string &path);
        bool Run();
        bool Stop();

    private:

        static void handleEvents(FsMonitor &monitor);

    private:
        string path;

        std::thread thread;
};
