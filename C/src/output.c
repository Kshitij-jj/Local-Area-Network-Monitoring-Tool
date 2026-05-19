#include "output.h"


static const char *HTML_STYLE =
    "<style>"
    "body{font-family:monospace;background:#0d1117;color:#c9d1d9;padding:2rem;}"
    "h1{color:#58a6ff;border-bottom:1px solid #30363d;padding-bottom:.5rem;}"
    "h2{color:#79c0ff;margin-top:2rem;}"
    "h3{color:#8b949e;margin:.25rem 0;}"
    "table{border-collapse:collapse;width:100%;max-width:500px;margin:.5rem 0 1.5rem;}"
    "th{background:#161b22;color:#58a6ff;padding:.5rem 1rem;text-align:left;border:1px solid #30363d;}"
    "td{padding:.4rem 1rem;border:1px solid #21262d;}"
    ".open{color:#3fb950;font-weight:bold;}"
    ".filtered{color:#d29922;font-weight:bold;}"
    ".summary{background:#161b22;border:1px solid #30363d;border-radius:6px;padding:1rem;margin:1rem 0;display:flex;gap:2rem;}"
    ".summary span{font-size:1.1rem;}"
    ".open-count{color:#3fb950;}"
    ".filtered-count{color:#d29922;}"
    "</style>";

void report_text(Target *targets, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < targets[i].ip_count; j++) {
            Ip_var *ip = &targets[i].ip_addrs[j];
            printf("\nScan Report For: %s (%s)\n", targets[i].hostname, ip->ip);
            printf("\t%-6s\t%s\n", "PORT", "STATUS");
            for (int k = 0; k < ip->port_count; k++) {
                switch (ip->ports[k].status) {
                    case PORT_OPEN:     printf("\t%-6d\tOPEN\n",     ip->ports[k].port); break;
                    case PORT_FILTERED: printf("\t%-6d\tFILTERED\n", ip->ports[k].port); break;
                    default: break;
                }
            }
        }
    }
}

void report_html(Target *targets, int count) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char filename[64], date[32];
    strftime(filename, sizeof(filename), "crecon_%Y%m%d_%H%M%S.html", tm_info);
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_info);

    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("fopen"); return; }

    fprintf(fp,
        "<!DOCTYPE html>\n<html>\n<head>\n"
        "<meta charset='UTF-8'>\n"
        "<title>CRecon Report</title>\n"
        "%s\n"
        "</head>\n<body>\n"
        "<h1>🔍 CRecon Scan Report</h1>\n"
        "<p>Scan Date: <strong>%s</strong></p>\n",
        HTML_STYLE, date);

    for (int i = 0; i < count; i++) {
        fprintf(fp, "<h2>🎯 %s</h2>\n", targets[i].hostname);

        for (int j = 0; j < targets[i].ip_count; j++) {
            Ip_var *ip = &targets[i].ip_addrs[j];

            int open_count = 0, filtered_count = 0;
            for (int k = 0; k < ip->port_count; k++) {
                if (ip->ports[k].status == PORT_OPEN)     open_count++;
                if (ip->ports[k].status == PORT_FILTERED) filtered_count++;
            }

            fprintf(fp,
                "<h3>%s</h3>\n"
                "<div class='summary'>"
                "<span class='open-count'>Open: %d</span>"
                "<span class='filtered-count'>Filtered: %d</span>"
                "</div>\n"
                "<table>\n"
                "<tr><th>PORT</th><th>STATUS</th></tr>\n",
                ip->ip, open_count, filtered_count);

            for (int k = 0; k < ip->port_count; k++) {
                switch (ip->ports[k].status) {
                    case PORT_OPEN:
                        fprintf(fp, "<tr><td>%d</td><td class='open'>OPEN</td></tr>\n",
                            ip->ports[k].port); break;
                    case PORT_FILTERED:
                        fprintf(fp, "<tr><td>%d</td><td class='filtered'>FILTERED</td></tr>\n",
                            ip->ports[k].port); break;
                    default: break;
                }
            }
            fputs("</table>\n", fp);
        }
    }

    fputs("</body>\n</html>\n", fp);
    fclose(fp);
    printf("Report saved to: %s\n", filename);
}

void report(Target *targets, int count, char format) {
    if      (format == 'h') report_html(targets, count);
    else if (format == 't') report_text(targets, count);
    else                    fprintf(stderr, "Invalid format: %c\n", format);
}