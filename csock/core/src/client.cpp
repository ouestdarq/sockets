// Client::Client(u_short domain, int type, int proto, int port, u_long dev)
//     : Socket(domain, type, proto, port, dev)
// {

//     if (this->connection = this->attach(this->sock, this->addr) < 0)
//         exit(1);
// }

// int Client::attach(int sock, struct sockaddr_in addr)
// {
//     return connect(sock, (struct sockaddr *)&addr, sizeof(addr));
// }