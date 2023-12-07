#include "socket.h"

int main(int argc, char const *argv[])
{
    Host host = Host(AF_INET, SOCK_STREAM, 0, 3503, INADDR_ANY);

    return 0;
}
