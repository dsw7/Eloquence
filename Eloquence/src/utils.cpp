#include "utils.hpp"

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

unsigned short get_terminal_columns()
{
    static struct ::winsize window_size;
    window_size.ws_col = 0;

    if (::ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == 0)
    {
        return window_size.ws_col;
    }

    return 20;
}

void separator()
{
    static unsigned short columns = ::get_terminal_columns();
    std::cout << std::string(columns, '-') + '\n';
}
