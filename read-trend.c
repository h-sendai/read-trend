#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "my_signal.h"
#include "my_socket.h"
#include "set_timer.h"
#include "set_cpu.h"
#include "get_num.h"

volatile sig_atomic_t has_alarm = 0;

int usage(void)
{
    char msg[] = "Usage: ./read-trend [-p port] [-b bufsize] [-i interval] ip_address\n"
                 "default: port 24, read bufsize 1024kB, interval 1 second\n"
                 "suffix k for kilo, m for mega to speficy bufsize\n"
                 "socket rcvbufsize is not implemented yet";
    // not yet [-r socket_rcvbufsize] 
    fprintf(stderr, "%s\n", msg);

    return 0;
}

void sig_alrm(int signo)
{
    has_alarm = 1;
    return;
}

int print_pid()
{
    pid_t pid = getpid();
    fprintf(stderr, "pid: %d\n", pid);

    return 0;
}

int main(int argc, char *argv[])
{
    int rcvbuf __attribute__((unused)) = 0;
    int bufsize  = 1*1024*1024;
    int port     = 24;
    int interval = 1;
    char *buf    = NULL;
    int cpu_num  = -1;

    int c;
    while ( (c = getopt(argc, argv, "c:hPp:r:b:")) != -1) {
        switch (c) {
            case 'h':
                usage();
                exit(0);
                break;
            case 'c':
                cpu_num = get_num(optarg);
                break;
            case 'P':
                print_pid();
                break;
            case 'p':
                port = strtol(optarg, NULL, 0);
                break;
            case 'r':
                rcvbuf = get_num(optarg);
                break;
            case 'b':
                bufsize = get_num(optarg);
                break;
            default:
                break;
        }
    }
    argc -= optind;
    argv += optind;
    if (argc != 1) {
        usage();
        exit(1);
    }

    char *ip_address = argv[0];

    if (cpu_num != -1) {
        if (set_cpu(cpu_num) < 0) {
            fprintf(stderr, "set_cpu: %d fail\n", cpu_num);
            exit(1);
        }
    }

    my_signal(SIGALRM, sig_alrm);

    buf = malloc(bufsize);
    if (buf == NULL) {
        err(1, "malloc for buf");
    }
    memset(buf, 0, bufsize);

    int sockfd = tcp_socket();
    if (sockfd < 0) {
        errx(1, "tcp_socket()");
    }

    if (connect_tcp(sockfd, ip_address, port) < 0) {
        errx(1, "tcp_connect");
    }

    set_timer(interval, 0, interval, 0);
    struct timeval start;
    gettimeofday(&start, NULL);

    int read_bytes = 0;
    int read_count = 0;
    for ( ; ; ) {
        if (has_alarm) {
            has_alarm = 0;
            struct timeval now, elapse;
            gettimeofday(&now, NULL);
            timersub(&now, &start, &elapse);
            fprintf(stderr, "%ld.%06ld %.3f MB %d\n", elapse.tv_sec, elapse.tv_usec, read_bytes/1024.0/1024.0, read_count);
            read_bytes = 0;
            read_count = 0;
        }
        int n = read(sockfd, buf, bufsize);
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            else {
                err(1, "read socket");
            }
        }
        read_bytes += n;
        read_count ++;
    }

    return 0;
}
