#include "socket.h"

int main(int argc, char const *argv[])
{
    Host host = Host(AF_INET, SOCK_STREAM, 0, 3503, INADDR_ANY);

    return 0;
}

float dt_ms(struct timeval i, struct timeval f)
{
    return ((f.tv_sec - i.tv_sec) * 1000000.0f) + ((f.tv_usec - i.tv_usec) / 1000.0f);
}
