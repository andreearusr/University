#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);

        if(c < 0)
        {
                printf("Eroare\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));

        server.sin_port = htons(8888);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0)
        {
                printf("Eroare \n");
                return 1;
        }

        int16_t ok = 1, id, player, l, litera_ascii;
        char* cuvant;
        char litera, prop[30];

        recv(c, &id, sizeof(id), 0);
        recv(c, &player, sizeof(player), 0);
        id = ntohs(id);
        player = ntohs(player);
        if(player == 1)
        {
                recv(c, &litera_ascii, sizeof(litera_ascii), 0);
                litera_ascii = ntohs(litera_ascii);
                litera = (char)litera_ascii;
                printf("Esti player 1. Cuvantul tau trebuie sa inceapa cu %c\n", litera);
                scanf("%s", prop);
                l = strlen(prop);
                l = htons(l);
                send(c, &l, sizeof(l), 0);
                send(c, prop, strlen(prop), 0);
        }
        else if(player == 2)
                printf("Esti player 2 !!\n");

        while(ok)
        {

                recv(c, &l, sizeof(l), 0);
                l = ntohs(l);
                if(l == -1)
                        break;

                cuvant = calloc(l + 1, sizeof(char));
                recv(c, cuvant, l, 0);

                printf("Ai primit %s\n", cuvant);
                printf("Da un cuvant: ");
                scanf("%s", prop);
                l = strlen(prop);
                l = htons(l);

                send(c, &l, sizeof(l), 0);
                send(c, prop, strlen(prop), 0);
                free(cuvant);
        }

        recv(c, &ok, sizeof(ok), 0);
        ok = ntohs(ok);

        if(ok == player)
                printf("Ai castigat!\n");
        else
                printf("Ai pierdut!\n");
        return 0;
}