#include <stdio.h>
#include <stdlib.h>
// #include <lnlist.h>
#include <queue.h>
#include <socket.h>

int main(int argc, char const *argv[])
{
    Host host = Host(AF_INET, SOCK_STREAM, 0, 3503, INADDR_ANY);
    // LnList l = LnList<int>();
    // l.insert(1, 0);

    // for (int i = 0; i < 2; i++)
    // l.insert(i, i);

    // l[0] = 3;
    // l.remove(3);

    // for (int i = 0; i < l.size(); i++)
    //     printf("%i\n", l[i]);

    // Queue queue = Queue<int>();

    // for (int i = 0; i < 10; i++)
    //     queue.push(i);

    // queue.pop();
    // queue.pop();
    // queue[0] = 10;

    // for (int i = 0; i < queue.size(); i++)
    //     printf("%i\n", queue[i]);

    return 0;
}