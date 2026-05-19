#include "helper.h"

int find_flag(int argc, char *argv[], const char *flag) {
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], flag) == 0) return i;
    return -1;
}

PortRange get_ports(int p_index, char *argv[]) {
    PortRange Port = {NULL, MAX_PORT};
    ++p_index;

    if (!argv[p_index]) return Port;

    if (strchr(argv[p_index], '-')) {
        int start, end;
        if (sscanf(argv[p_index], "%d-%d", &start, &end) != 2 || start > end)
            return Port;
        Port.count  = end - start + 1;
        Port.ports  = malloc(Port.count * sizeof(int));
        for (int i = 0; i < Port.count; i++)
            Port.ports[i] = start + i;
    } else {
        int i = p_index;
        while (argv[i] && argv[i][0] != '-') i++;
        Port.count = i - p_index;
        Port.ports = malloc(Port.count * sizeof(int));
        for (int i = 0; i < Port.count; i++)
            Port.ports[i] = (int)strtol(argv[p_index + i], NULL, 10);
    }

    return Port;
}

void init_ports(Ip_var *target, PortRange Port) {
    for (int i = 0; i < Port.count; i++)
        target->ports[i].port = Port.ports ? Port.ports[i] : i + 1;
}

void cleanup(Target *targets, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < targets[i].ip_count; j++)
            free(targets[i].ip_addrs[j].ports);
        free(targets[i].ip_addrs);
    }
    free(targets);
}
