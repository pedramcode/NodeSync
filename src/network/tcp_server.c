#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "string.h"

#include "utils/logging/log.h"

#include "tcp_server.h"

tcp_server_t *tcp_server_init(uint32_t port, uint32_t workers, void *connection_handler)
{
    tcp_server_t *server = calloc(1, sizeof(tcp_server_t));
    server->port = port;
    server->workers = workers;
    server->pool = thpool_init(64);
    server->connection_handler = connection_handler;

    SOCK_FD fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        log_error("Socket creation failed");
        exit(1);
    }
    server->sock_fd = fd;

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        log_error("Setsockopt failed");
        exit(1);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        log_error("Bind failed");
        exit(EXIT_FAILURE);
    }

    return server;
}

void tcp_server_listen(tcp_server_t *server)
{
    if (listen(server->sock_fd, server->workers) < 0)
    {
        log_error("Listen failed");
        exit(EXIT_FAILURE);
    }
    log_info("Server is listening to :%d (%d workers)", server->port, server->workers);

    while (1)
    {
        SOCK_FD client_fd;
        struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
        int addrlen = sizeof(*address);
        if ((client_fd = accept(server->sock_fd, (struct sockaddr *)address, (socklen_t *)&addrlen)) < 0)
        {
            log_error("Connection accepting failed");
            continue;
        }
        connection_t *conn = malloc(sizeof(connection_t));
        conn->addr = address;
        conn->conn_fd = client_fd;
        thpool_add_work(server->pool, server->connection_handler, (void *)conn);
    }
}

void tcp_server_free(tcp_server_t *server)
{
    thpool_destroy(server->pool);
}

void tcp_server_close(connection_t *connection)
{
    close(connection->conn_fd);
    free(connection->addr);
    free(connection);
}