#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "stdint.h"
#include "netinet/in.h"

#include "utils/pool/thpool.h"

#include "_global.h"

typedef struct
{
    struct sockaddr_in *addr;
    SOCK_FD conn_fd;
} connection_t;

typedef struct
{
    uint32_t port;
    uint32_t workers;
    SOCK_FD sock_fd;
    threadpool pool;
    void *connection_handler;
} tcp_server_t;

/// @brief Instantiate a TPC server
/// @param port Port number
/// @param max_connections Max pending connections
/// @param connection_handler Request handler function, function argument should convert to *connection_t - void* handler(void *conn)
/// @return TPC server pointer
tcp_server_t *tcp_server_init(uint32_t port, uint32_t max_connections, void *connection_handler);

/// @brief TCP server start listening
/// @param server Pointer of tcp server
void tcp_server_listen(tcp_server_t *server);

/// @brief Frees tcp server
/// @param server Pointer of tcp server
void tcp_server_free(tcp_server_t *server);

/// @brief Frees and closes tcp connection request
/// @param connection Pointer to connection
void tcp_server_close(connection_t *connection);

#endif