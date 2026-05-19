#include "common.h"
#include "scanner.h"
#include "input.h"
#include "helper.h"
#include "output.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("Usage: crecon <target> [target2 ...] [-p port|range] [-o h|t|..]\n", stderr);
        exit(EXIT_FAILURE);
    }

    int count, i, j;
    char format;
    format = get_format(argc, argv);
    Target *targets = get_targets(argc, argv, &count);

    printf("Proceeding to scan...\n");
    for (i = 0; i < count; i++) {
        for (j = 0; j < targets[i].ip_count; j++) {
            char *ip = targets[i].ip_addrs[j].ip;
            printf("Scanning %s (%s)...\n", targets[i].hostname, ip);
            scan_ports(ip, targets[i].ip_addrs[j].ports, targets[i].ip_addrs[j].port_count);
            printf("Done.\n");
        }
    }

    report(targets, count, format);
    cleanup(targets, count);
    printf("Program Exited\n");
    return 0;
}