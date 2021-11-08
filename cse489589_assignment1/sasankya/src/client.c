#include "../include/logger.h"
#include "../include/global.h"
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#incliude "../include/client.h"
#define MAX_MESSAGE 1024

void allocmemory(char **temp){
   *temp =  (char*)(malloc(sizeof(char)) * MAX_MESSAGE);
}

int clientCaller(struct clientSide **clientPointer, int port, int listen_file_d){

    char* command;
    allocmemory(&command);
    char* r_buffer;
    allocmemory(&r_buffer);
    char *s_buffer, *inputs, *message, *server, *client, *command1;
    allocmemory(&s_buffer);
    allocmemory(&inputs);
    allocmemory(&message);
    allocmemory(&server);
    allocmemory(&client);


    size_t nbyte_rcv;
    fd_set list_main;
    FD_ZERO(&list_main);
    fd_set list_track;
    FD_ZERO(&list_track);
    FD_ZERO(0, &list_main);

    int temp, server_save, server_file_d;
    server_save = listen_file_d;
    server_file_d = 0;
    struct sockaddr_in serverAdd;
    for(;;){
        list_track = list_main;
        int returns = select(temp+1, &list_track, NULL, NULL, NULL);
        if(returns < 0){
            perror("select");
        }
        if(returns > 0){
            for(int i=0; i<=temp; i++){
                if(FD_ISSET(i, &list_track)){
                    memset(r_buffer, '\0', MAX_MESSAGE);
                    memset(command, '\0', MAX_MESSAGE);
                    // i==0
                    if(!i){
                        if(fgets(command, 99, stdin) == NULL){
                            exit(-1);
                        }
                        strcpy(command1, command);
                        inputs = strtok(command, " ");

                        if(!(strcmp(cmd, "AUTHOR\n"))){
                            cse4589_print_and_log("[%s:SUCCESS]\n","AUTHOR");
                            cse4589_print_and_log("I, %s, have read and understood the course academic integrity policy.\n", "Sasank");
                            cse4589_print_and_log("[%s:END]\n","AUTHOR");
                        }
                        if(!(strcmp(command, "IP\n"))){
                            char string_ip[INET_ADDRSTRLEN];
                            strcpy(string_ip, print_ip(string_ip));
                            //print_ip(string_ip);
                        }
                        else if(!(strcmp(command, "LIST\n"))){
                            cse4589_print_and_log((char *)"[%s:SUCCESS]\n", "LIST");
                            struct clientSide* ref = *clientPointer;
                            int count = 1;
                            sort(ref);
                            for(;ref;){
                                if(ref->cstatus == 1){
                                    cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", count,ref->host, ipOfClient[ref->count], ref->port);
                                }
                                ref = ref->next;
                                count += 1;
                            }
                            cse4589_print_and_log((char *)"[%s:END]\n", "LIST");
                        }
                        else if(!(strcmp(command, "PORT\n"))){
                            cse4589_print_and_log("[%s:SUCCESS]\n","PORT");
                            cse4589_print_and_log("PORT:%d\n",port_no);
                            cse4589_print_and_log("[%s:END]\n","PORT");
                        }
                        else if(!(strcmp(inputs, "LOGIN"))) {
                            server_file_d = socket(AF_INET, SOCK_STREAM, 0);
                            if (server_file_d < 0) {
                                exit(8);
                            } else {
                                FD_SET(server_file_d, &list_main);
                                temp = temp < server_file_d : server_file_d : temp;
                            }

                            int res = 1;
                            for (int countvar=0;countvar < 2;) {
                                char* temp_store = (char*) malloc(sizeof(char)*100);
                                if(!countvar) {
                                    inputs = strtok(NULL, " ");
                                    strcpy(temp_store, inputs);
                                    server = temp_store;
                                }else{
                                    inputs = strtok(NULL, " ");
                                    if(inputs == NULL)
                                        res = 0;
                                    else{
                                        strcpy(temp_store, inputs);
                                        input_port = temp_store;
                                        break;
                                    }
                                }
                                countvar = countvar + 1;
                            }
                            char* store = server;
                            if(res == 0){
                                print_login();
                            } else {
                                serverAdd.sin_family = AF_INET;
                                unsigned int hold_port = atoi(input_port);
                                serverAdd.sin_port = htons(hold_port);
                                inet_pton(AF_INET, server, &(serverAdd.sin_addr));

                                if(connect(server_file_d, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) < 0){
                                    print_login();
                                }
                                else{
                                    char send[100];
                                    char client_ip_field[INET_ADDRSTRLEN];
                                    struct sockaddr_in unrel_data_prot;
                                    int temp_seg_udp, length, res;
                                    temp_seg_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                                    length = sizeof(unrel_data_prot);
                                    memset((char *) &unrel_data_prot, 0, sizeof(unrel_data_prot));
                                    unrel_data_prot.sin_family = AF_INET;
                                    unrel_data_prot.sin_port = htons(EPHEMERAL_PORT);
                                    inet_pton(AF_INET, "8.8.8.8", &unrel_data_prot.sin_addr);

                                    if(connect(temp_seg_udp, (struct sockaddr *)&unrel_data_prot, sizeof(unrel_data_prot)) < 0)
                                        res = 0;
                                    if(getsockname(temp_seg_udp, (struct sockaddr_in *)&uunrel_data_prot, (unsigned int *)&len) == -1){
                                        res = 0;
                                        perror("getsockname");
                                    }
                                    inet_ntop(AF_INET, &(unrel_data_prot.sin_addr), client_ip_field, length);

                                    char port_number[INET_ADDRSTRLEN];
                                    stringConvertor(port_number, port);

                                    strcat(send, "Port");
                                    strcat(send, " ");
                                    strcat(send, client_ip_field);
                                    strcat(send, " ");
                                    strcat(send, poport_number);
                                    strcat(send, "\n");

                                    if(send(server_file_d, send, strlen(send), 0) == -1)
                                        perror("send");

                                }
                                print_login();
                            }

                        }

                        else if(!(strcmp(inputs, "SEND"))){
                            for(int var=0, var < 2; var++){
                                char *temp;
                                temp = (char *)malloc(sizeof(char) * MAX_MESSAGE);
                                strcpy(temp, inputs);
                                if(count == 0){
                                    inputs = strtok(NULL, " ");
                                    strcpy(temp, inputs);
                                    client = temp;
                                } else if(count == 1){
                                    inputs = strtok(NULL, "\n");
                                    strcpy(temp, inputs);
                                    message = temp;
                                    break;
                                }
                                count += 1;
                            }
                            memset(s_buffer, '\0', MAX_MESSAGE);
                            serverAdd.sin_family = AF_INET;
                            serverAdd.sin_port = port;
                            inet_pton(AF_INET, client, &(serverAdd.sin_addr));
                            strcat(s_buffer, client);
                            strcat(s_buffer, " ");
                            strcat(s_buffer, message);
                            strcat(s_buffer, "\n");

                            send(server_file_d, s_buffer, strlen(s_buffer), 0);
                        }
                        else if(!(strcmp(inputs, "BROADCAST"))){
                            char *temp = (char*)(malloc(sizeof(char) * MAX_MESSAGE));
                            for(;;){
                                if(!inputs){
                                    break;
                                }
                                inputs = strtok(NULL, "\n");
                                if(!inputs) break;
                                strcpy(temp, inputs);
                                broadcast(*clientPointer,temp, server_file_d);
                            }
                        }
                        else if(!strcmp(inputs, "BLOCK")){
                            char *temp = (char*)(malloc(sizeof(char) * MAX_MESSAGE));
                            struct clientSide *temp1;
                            temp = *clientPointer;
                            int count;
                            count = 0;
                            inputs = strtok(NULL, "\n");
                            for(;;){
                                if(!temp) break;

                                if(!strcmp(inputs, client[temp1->id_list])){
                                    temp1->bstatus = 1;
                                    count = count + 1;
                                }
                                struct clientSide *hold = temp1->next;
                                temp1 = hold;
                            }

                            if(count > 0)
                            {
                                cse4589_print_and_log((char *)"[%s:SUCCESS]\n","BLOCK");
                                cse4589_print_and_log((char *)"[%s:END]\n","BLOCK");
                            }
                            else{
                                cse4589_print_and_log((char *)"[%s:ERROR]\n","BLOCK");
                                cse4589_print_and_log((char *)"[%s:END]\n","BLOCK");
                            }
                        }
                        else if(!strcmp(input, "UNBLOCK")) {
                            char *temp = (char*)(malloc(sizeof(char) * MAX_MESSAGE));
                            struct clientSide *temp1;
                            temp = *clientPointer;
                            int count;
                            count = 0;
                            inputs = strtok(NULL, "\n");
                            for(;;){
                                if(!temp) break;

                                if(!strcmp(inputs, client[temp1->id_list])){
                                    temp1->bstatus = 0;
                                    count = count + 1;
                                }
                                struct clientSide *hold = temp1->next;
                                temp1 = hold;
                            }

                            if(count > 0)
                            {
                                cse4589_print_and_log((char *)"[%s:SUCCESS]\n","UNBLOCK");
                                cse4589_print_and_log((char *)"[%s:END]\n","UNBLOCK");
                            }
                            else{
                                cse4589_print_and_log((char *)"[%s:ERROR]\n","UNBLOCK");
                                cse4589_print_and_log((char *)"[%s:END]\n","UNBLOCK");
                            }
                        }
                        else if(!strcmp(command,"LOGOUT\n")){
                            cse4589_print_and_log((char *)"[%s:SUCCESS]\n","LOGOUT");
                            close(server_file_d );
                            cse4589_print_and_log((char *)"[%s:END]\n","LOGOUT");
                            return 0;
                        }

                        else if(!strcmp(command, "EXIT\n"))
                        {
                            cse4589_print_and_log((char *)"[%s:SUCCESS]\n", (char*)"EXIT");
                            close(server_file_d);
                            cse4589_print_and_log((char *)"[%s:END]\n", (char*)"EXIT");
                            exit(0);
                        }

                    }
                    else {
                        memset(recv_buf, '\0', MAX_MESSAGE);
                        if(i == 0 && i==listen_file_d)
                            break;
                        else
                        {
                            nbyte_rcv = recv(i, r_buffer, MAX_MESSAGE, 0);
                            recv_buf[nbyte_recvd] = '\0';
                            char *input;
                            allocmemory(&input);
                            strcpy(input, r_buffer);
                            struct client *temp = *c_ref;
                            char *identify;
                            allocmemory(&identify);
                            strcpy(identify,r_buffer);
                            identify = strtok(identify, " ");
                            if(!strcmp(identify, "List")) {
                                char *string[256];
                                int i =0;
                                string[i]=strtok(r_buffer,"\n");
                                while(string[i]) {
                                    i++;
                                    string[i]=strtok(NULL,"\n");
                                }
                                for (int j=0;j<i;j++) {
                                    char *val = strtok(string[j], " ");
                                    int counter = 0;
                                    struct client *new_node = (struct client*) malloc(sizeof(client));
                                    while (val) {
                                        if(j == 0)
                                        {
                                            if(counter == 1)
                                                new_node->id_list = atoi(val);
                                            else if(counter ==2) {  
                                                new_node->port = atoi(val);
                                            }
                                            else if(counter == 3)
                                            {
                                                new_node->host = (char*)malloc(sizeof(MAX_MESSAGE));
                                                strcpy(new_node->host,val);
                                            }
                                            else if(counter == 4)
                                            {
                                                new_node->ip = (char*)malloc(sizeof(MAX_MESSAGE));
                                                strcpy(new_node->ip, val);
                                                strcpy(client_ip[new_node->id_list],val);
                                            }
                                        }
                                        else
                                        {

                                            if(counter == 0)
                                                new_node->id_list = atoi(val);
                                            else if(counter ==1){ 
                                                new_node->port = atoi(val);
                                            }
                                            else if(counter == 2)
                                            {
                                                new_node->host = (char*)malloc(sizeof(MAX_MESSAGE));
                                                strcpy(new_node->host,val);
                                            }
                                            else if(counter == 3)
                                            {
                                                new_node->ip = (char*)malloc(sizeof(MAX_MESSAGE));
                                                strcpy(new_node->ip, val);
                                                strcpy(client_ip[new_node->id_list],val);
                                            }
                                        }
                                        val = strtok(NULL, " ");
                                        counter +=1;
                                    }
                                    if(*clientPointer==NULL){
                                        *clientPointer = new_node;
                                        new_node->next = NULL;
                                    }
                                    else{
                                        new_node->next = *clientPointer;
                                        *clientPointer = new_node;
                                    }
                                }
                            }
                            else {
                                char *from, *msg;
                                allocmemory(&from);
                                allocmemory(&msg);
                                int count = 0;
                                if(r_buffer!=NULL) {
                                    input = strtok(input, " ");
                                    strcpy(from, input);
                                    while(input != NULL){
                                        input= strtok(NULL, " ");
                                        if(input!=NULL)
                                            strcpy(msg,input);
                                    }
                                    cse4589_print_and_log("[RECEIVED:SUCCESS]\n");
                                    cse4589_print_and_log("msg from:%s\n[msg]:%s\n",from,msg);
                                    cse4589_print_and_log("[RECEIVED:END]\n");

                                }
                                else {
                                    cse4589_print_and_log("[RECEIVED:ERROR]\n");
                                    cse4589_print_and_log("msg from:%s\n[msg]:%s\n",from,msg);
                                    cse4589_print_and_log("[RECEIVED:END]\n");
                                }
                            }
                        }
                        fflush(stdout);
                    }
                }
            }
        }
    }

}
