#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int soc, ret, ifindex;
    struct sockaddr_ll addr;
    struct ifreq ifr;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <ifname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    soc = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (soc == -1) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    // set promiscuous mode
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);
    ret = ioctl(soc, SIOCGIFFLAGS, &ifr);
    if (ret == -1) {
        perror("failed to get interface flag");
        close(soc);
        exit(EXIT_FAILURE);
    }
    ifr.ifr_flags |= IFF_PROMISC;
    ret = ioctl(soc, SIOCSIFFLAGS, &ifr);
    if (ret == -1) {
        perror("failed to set interface flag");
        close(soc);
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    strncpy(ifr.ifr_name, argv[1], IFNAMSIZ);
    ret = ioctl(soc, SIOCGIFINDEX, &ifr);
    if (ret == -1) {
        perror("failed to get interface index");
        close(soc);
        exit(EXIT_FAILURE);
    }
    ifindex = ifr.ifr_ifindex;

    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_ifindex = ifindex;
    ret = bind(soc, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("bind failed");
        close(soc);
        exit(EXIT_FAILURE);
    }

    close(soc);

    return 0;
}
