//based off something I found somewhere, probably StackOverflow
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int
main(int argc, char* argv[]) {
  if(argc != 2){
    fprintf(stderr, "Usage: %s interface\n", argv[0]);
    return 255;
  }
  int fd, rc;
  struct ifreq ifr;
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET; //ipv4
  char* interface = argv[1];
  strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
  rc = ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);
  if(rc != 0) {
    fprintf(stderr, "Something went wrong. Does the interface exist?\n");
    return 1;
  }
  else 
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  return 0;
}
