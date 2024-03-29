#include "stdio.h"
#include "stdlib.h"
#include "argp.h"
#include "time.h"

#include "utils/logging/log.h"

#include "settings.h"
#include "network/tcp_server.h"

static char doc[] = "Node Sync platform";
const char *argp_program_version = "Node Sync 0.1.0";
const char *argp_program_bug_address = "dev.dehghanpour@gmail.com";

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    settings_t *settings = state->input;
    switch (key)
    {
    case 'n':
        settings->node_name = arg;
        break;
    case 'p':
        settings->port = atoi(arg);
        break;
    case 'w':
        settings->workers = atoi(arg);
        break;
    case ARGP_KEY_END:
        // error format: argp_error(state, "Missing required argument: --required");
        int has_error = 0;
        if (settings->port == 0)
        {
            settings->port = 1212;
        }
        if (settings->workers == 0)
        {
            settings->workers = 16;
        }
        if (settings->node_name == NULL)
        {
            // Allocate space for node_name
            settings->node_name = "unnamed node";
        }

        if (has_error == 1)
        {
            exit(1);
        }
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp_option options[] = {
    {"node-name", 'n', "example", 0, "Produce verbose output", 0},
    {"port", 'p', "1212", 0, "TCP port", 0},
    {"workers", 'w', "16", 0, "Server workers", 0},
    {0}};

static struct argp argp = {options, parse_opt, NULL, doc};

void *__handler(void *conn_ptr)
{
    connection_t *conn = (connection_t *)conn_ptr;
    dprintf(conn->conn_fd, "Hello World!\n");
    tcp_server_close(conn);
}

int main(int argc, char *argv[])
{
    // ========== Server ==========
    settings_t settings;
    settings.node_name = NULL;

    if (argp_parse(&argp, argc, argv, 0, 0, &settings) != 0)
    {
        log_error(stderr, "Invalid arguments");
        return 1;
    }

    log_info("NodeSync \"%s\" node is ready", settings.node_name);

    tcp_server_t *server = tcp_server_init(settings.port, settings.workers, (void *)&__handler);
    tcp_server_listen(server);

    return 0;
}