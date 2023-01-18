#include <iostream>
#include <thread> 
#include <unistd.h>

void print_app_info(int counter) { 
    if (counter == 4) {
        exit(0);
    }

    std::string app; 
    if(counter % 2 == 0)
        app = "Notepad"; 
    else
        app = "WordPad";

    std::cout << "Name: " << app << ",Thread ID: " << std::this_thread::get_id() << ",Process ID: "
    << getpid() << std::endl;
}

int main() {

    for (int i = 0; i <= 4; i++) {
        std::thread t(print_app_info, i); 
        t.join();
    }
    return 0;
}
