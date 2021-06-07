#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdbool.h>
#include <getopt.h>

//#define SERV_PORT 20001
//#define BUFSIZE 1024
#define SADDR struct sockaddr
#define SLEN sizeof(struct sockaddr_in)

int main(int argc, char **argv) {
  //-------------start
  char ip_address[255];
  int buff_size = -1;
  int server_port = -1;
  
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"ip_address", required_argument, 0, 0},
                                      {"buff_size", required_argument, 0, 0},
                                      {"server_port", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0: {
      switch (option_index) {
      case 0:
        // IP-адрес
        strcpy(ip_address, optarg);
        break;
      case 1:
        // Размер буфера
        buff_size = atoi(optarg);
        if (buff_size <= 0)
        {
            printf("Size of buffer must be positive number.\n");
            return 1;
        }
        break;
      case 2:
        // Порт сервера
        server_port = atoi(optarg);
        if (server_port <= 1024)
        {
            printf("Port of the server must be > 1024.\n");
            return 1;
        }
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    } break;

    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (!strlen(ip_address) || buff_size == -1 || server_port == -1) {
    fprintf(stderr, "Using: %s --ip_address 0.0.0.0 --buff_size 1024 --server_port 20001\n",
            argv[0]);
    return 1;
  }
//--------------------------end
  int sockfd, n;
  char sendline[buff_size], recvline[buff_size + 1];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(server_port);

  if (inet_pton(AF_INET, ip_address, &servaddr.sin_addr) < 0) {//ip address
    perror("inet_pton problem");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }

  write(1, "Enter string\n", 13);

  while ((n = read(0, sendline, buff_size)) > 0) {


    if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }

    if (recvfrom(sockfd, recvline, buff_size, 0, NULL, NULL) == -1) {
      perror("recvfrom problem");
      exit(1);
    }

    printf("REPLY FROM SERVER= %s\n", recvline);
  }
  close(sockfd);
}