//bin/cat /dev/null; mkdir -p $TMPDIR; HASH="`md5sum $0`"; FILE="$TMPDIR/$0_$HASH"; gcc -o "$FILE" "$0" && ORIGINAL_ZERO="$0" "$FILE" "$@"; exit
// ^ this lets one run this file directly
//based off something I found somewhere, probably StackOverflow
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

char* get_called_executable();

int
main(int argc, char* argv[]) {
  char* called_executable = get_called_executable(argv[0]);
  if(argc != 2){
    fprintf(stderr, "Usage: %s interface\n", called_executable);
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

char*
get_called_executable(char* argv0) {
  char* original_zero = getenv("ORIGINAL_ZERO");
  if(original_zero){
    return original_zero;
  } else {
    return argv0;
  }
}
