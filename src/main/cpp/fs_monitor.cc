#include<fs_monitor.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

bool FsMonitor::Init(string &path)
{
    if (!inotifytools_initialize()) {
		printf("inotifytools_initialize failed\n");
		return -1;
	}
 
 
	inotifytools_initialize_stats();
 
    this->path = path;

	cout << "Monitor dir:" <<  this->path << endl;

    return true;
}

bool FsMonitor::Run()
{
    this->thread = std::thread(FsMonitor::handleEvents,this);
    return true;
}

bool FsMonitor::Stop()
{
    ev_break(loop_, EVBREAK_ALL);
    return true;
}

void FsMonitor::HandleEvents(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    struct fs_io * fs_watcher = (struct fs_io *)watcher;
    FsMonitor * fs_monitor = (FsMonitor *)fs_watcher->data;

    int length, i = 0;
    char buffer[BUF_LEN];
    length = read(fs_monitor->fd_, buffer, BUF_LEN);
    if (length < 0) {
        perror("read");
        return;
    }

    while (i < length) {
        struct inotify_event *event = (struct inotify_event *) &buffer[i];
        if (event->len) {
            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR) {
                    std::cout <<"The directory " << event->name <<" was created." << std::endl;
                }
                else {
                    std::cout <<"The file " << event->name << " was created." << std::endl;
                }
            }
            else if (event->mask & IN_DELETE) {
                if (event->mask & IN_ISDIR) {
                    std::cout <<"The directory " << event->name << " was deleted." << std::endl;
                }
                else {
                    std::cout <<"The file " << event->name << " was deleted." << std::endl;
                }
            }
            else if (event->mask & IN_MODIFY) {
                if (event->mask & IN_ISDIR) {
                    std::cout <<"The directory " << event->name << " was modified." << std::endl;
                }
                else {
                    std::cout <<"The file " << event->name << " was modified." << std::endl;
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }
}

bool FsMonitor::RemoveItem(const std::string &item_name) {
    auto find_item = item_wd_.find(item_name);
    if (find_item == item_wd_.end()) {
        std::cout << "no item " << item_name << " to remove" << std::endl;
        return false;
    }
    int wd = find_item->second;
    inotify_rm_watch(fd_, wd);
    return true;
}

bool FsMonitor::ModifyItem(const std::string &item_name, uint32_t mask) {
    // remove and add
    return true;
}

// int main(int argc, char **argv) {
//     FsMonitor fs_monitor;
//     std::vector<std::pair<std::string,uint32_t>> item_list;
//     item_list.emplace_back(std::pair<std::string,uint32_t>("/tmp", IN_MODIFY | IN_CREATE | IN_DELETE));
//     if (fs_monitor.Init(item_list) == false) {
//         return -1;
//     }
//     std::cout << "Starting..." << std::endl;
//     fs_monitor.Run();
//     while (true) {
//         usleep(1000 * 1000);
//     }
//     std::cout << "End..." << std::endl;

//     return 0;
// }