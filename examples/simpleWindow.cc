#include <iostream>
#include <unistd.h>
#include "../src/maguic.hh"

int main()
{
    std::cout << "Hello World!\n";
    {
        Maguic::Window win{"Main Window"};

        sleep(1);
        win.setVisible(true);
        sleep(4);
        printf("Before out of scope\n");
    }
    printf("out of scope\n"); // win.setVisible(false);
    // sleep(1);
    // win.setVisible(true);
    // sleep(1);
    return 0;
}