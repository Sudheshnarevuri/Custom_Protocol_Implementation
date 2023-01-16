//THIS IS THE SERVER PROGRAM WHERE EXECUTION OF COMMANDS ARE BEING PERFORMED 

/*************************************************************************************************************
 ** FILENAME	:	Source code for Server.c
 **
 ** DESCRIPTON   :	Implemention of  Custom protocol
 *************************************************************************************************************/

/*************************************************************************************************************
 					HEADER FILES
***************************************************************************************************************/

#include <stdio.h>		//INCLUDES INPUT OUTPUT RELATED FUNCTIONS 
#include <stdlib.h>		//INCLUDES FUNCTIONS INVOLVING MEMORY ALLOCATION, 

//UTILITY FUNCTIONS FOR TYPE CONVERSIONS

#include <string.h>		//INCLUDES ALL FUNCTIONS OF STRING HANDLING
#include <unistd.h>		//PROVIDES ACCESS TO THE POSIX OPERATION SYSTEM API
#include <dirent.h>       //facilitate directory traversing.ls
#include <sys/types.h>	//INCLUDES TYPEDEF SYMBOLS AND STRUCTURES
#include <sys/socket.h>	//INCLUDES SOCKADDR STRUCTURE
#include <netinet/in.h>	//INCLUDES THE INTERNET ADDRESS FAMILY
#include <arpa/inet.h>	//INCLUDES THE DEFINITION FOR INTERNET OPERATIONS
#include <pthread.h>      //function declarations and mappings for threading                            interfaces

#include "common.h"
#include "server.h"


int cl_count = 0;
msg_action_t  msg_actions[MSG_MAX];
user_info_t  *user_list_start = NULL;


/***********create_write function************/

int create_write()

{
    /* Variable to store user content */
    char data[DATA_SIZE];

    /* File pointer to hold reference to our file */
    FILE * fPtr;


    /* 
     * Open file in w (write) mode. 
     * "file1.txt" is complete path to create file
     */
    fPtr = fopen("file1.txt", "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }


    /* Input contents from user to store in file */
    printf("Enter contents to store in file : \n");
    fgets(data, DATA_SIZE, stdin);


    /* Write data to file */
    fputs(data, fPtr);


    /* Close file to save file data */
    fclose(fPtr);


    /* Success message */
    printf("File created and saved successfully. :) \n");


    return 0;
}

/***********copy_file function************/


int copy_file()
{
	FILE *fptr1, *fptr2;
	char filename[100], c;

	printf("Enter the filename to open for reading \n");
	scanf("%s", filename);

	// Open one file for reading
	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	printf("Enter the filename to open for writing \n");
	scanf("%s", filename);

	// Open another file for writing
	fptr2 = fopen(filename, "w");
	if (fptr2 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

	// Read contents from file
	c = fgetc(fptr1);
	while (c != EOF)
	{
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}

	printf("\nContents copied to %s", filename);

	fclose(fptr1);
	fclose(fptr2);
	return 0;
}

/***********delete_file function************/


int delete_file()
{
  int status;
  char file_name[50];

  printf("Enter name of a file you wish to delete\n");
  scanf("%s",file_name);

  status = remove(file_name);

  if (status == 0)
    printf("%s file deleted successfully.\n", file_name);
  else
  {
    printf("Unable to delete the file\n");
    perror("Following error occurred");
  }

  return 0;
}

/***********ls_cmd function************/


int ls_cmd()

{
    DIR *d;
    struct dirent *dir;
//character pointer d_name, which points to a string that gives the name of a file in the directory
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}

/***********cat_cmd function************/

int cat_cmd()
{
	FILE *fptr;

	char filename[100], c;

	printf("Enter the filename to open \n");
	scanf("%s", filename);

	// Open file
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	// Read contents from file
	c = fgetc(fptr);
	while (c != EOF)
	{
		printf ("%c", c);
		c = fgetc(fptr);
	}

	fclose(fptr);
	return 0;
}




/***********handle_create_write function************/


void handle_create_write(int sockfd, msg_t *msg)
{
	printf("Command name : %s\n", msg->msg_data);
	if(msg->msg_data != NULL)
	{
		create_write();
		
	}
	else 
	{
		printf("Invalid\n");
	}		

}


/***********handle_copy_file function************/


void handle_copy_file(int sockfd, msg_t *msg)
{
	printf("Command name : %s\n", msg->msg_data);
	if(msg->msg_data != NULL)
	{
		copy_file();
		
	}
	else 
	{
		printf("Invalid\n");
	}		

}

/***********handle_delete_file function************/


void handle_delete_file(int sockfd, msg_t *msg)
{
	printf("Command name : %s\n", msg->msg_data);
	if(msg->msg_data != NULL)
	{
		delete_file();
		
	}
	else 
	{
		printf("Invalid\n");
	}		

}

/***********handle_ls_cmd function************/


void handle_ls_cmd(int sockfd, msg_t *msg)
{
	printf("Command name : %s\n", msg->msg_data);
	if(msg->msg_data != NULL)
	{
		ls_cmd();
		
	}
	else 
	{
		printf("Invalid\n");
	}		

}

/***********handle_cat_cmd function************/


void handle_cat_cmd(int sockfd, msg_t *msg)
{
	printf("Command name : %s\n", msg->msg_data);
	if(msg->msg_data != NULL)
	{
		cat_cmd();
		
	}
	else 
	{
		printf("Invalid\n");
	}		

}

/***********setup_message_handlers()************/
/***********setup_message_handlers()************/


void setup_message_handlers()
{
  
  msg_actions[MSG_CREATE_WRITE].msg_action_function = handle_create_write;

  msg_actions[MSG_COPY_FILE].msg_action_function = handle_copy_file;

  msg_actions[MSG_DELETE_FILE].msg_action_function = handle_delete_file;

  msg_actions[MSG_LS_CMD].msg_action_function = handle_ls_cmd;

  msg_actions[MSG_CAT_CMD].msg_action_function = handle_cat_cmd;

}

/***********handle_client_close************/
/***********handle_client_close************/


void handle_client_close(int sock_fd)
{

  printf("Client on socket %d closed \n", sock_fd);

  /* TODO */
  close(sock_fd);

}

/***********process_client_messages************/
/***********process_client_messages************/


void process_client_messages(int sockfd, char *recv_buffer)
{
  

  msg_t *m = (msg_t *) recv_buffer;

  switch (m->msg_type)
  {

    case MSG_CREATE_WRITE:
                  printf("Received msg type %d socket = %d ... \n", m->msg_type, sockfd);
                  msg_actions[m->msg_type].msg_action_function(sockfd, m);
                  break;
    case MSG_COPY_FILE:
                  printf("Received msg type %d socket = %d ... \n", m->msg_type, sockfd);
                  msg_actions[m->msg_type].msg_action_function(sockfd, m);
                  break;
    case MSG_DELETE_FILE:
                  printf("Received msg type %d socket = %d ... \n", m->msg_type, sockfd);
                  msg_actions[m->msg_type].msg_action_function(sockfd, m);
                  break;
    case MSG_LS_CMD:
                  printf("Received msg type %d socket = %d ... \n", m->msg_type, sockfd);
                  msg_actions[m->msg_type].msg_action_function(sockfd, m);
                  break;
    case MSG_CAT_CMD:
                  printf("Received msg type %d socket = %d ... \n", m->msg_type, sockfd);
                  msg_actions[m->msg_type].msg_action_function(sockfd, m);
                  break;

    default:
                  printf("Received invalid msg type ... \n");
                  break;
  }

  return;

}

/***********client_handler************/
/***********client_handler************/


/* Thread to handle clients */
void* client_handler(void *client_sock_fd)
{
  int *cl_sock_fd = (int *) client_sock_fd;
  int ret = 0;

  char send_buffer[SEND_BUFFER_SIZE];
  char recv_buffer[RECV_BUFFER_SIZE];

  printf("%s():%d Client Fd = %d\n",__FUNCTION__, __LINE__, *cl_sock_fd);

  while(1)
  {
    printf("%s():%d Waiting on recv for fd = %d \n",
           __FUNCTION__, __LINE__, *cl_sock_fd);

    ret = recv(*cl_sock_fd, recv_buffer, sizeof(recv_buffer), 0);

    if (ret == 0)
    {
      printf("%s():%d Client has closed on socket fd = %d \n",
           __FUNCTION__, __LINE__, *cl_sock_fd);

      /* TODO: 
       * client has closed the connection, do any cleanup required and exit */

      handle_client_close(*cl_sock_fd);

      cl_count--;
      /* END: */
      pthread_exit(NULL);
    }

    process_client_messages(*cl_sock_fd, recv_buffer);


  }

  pthread_exit(NULL);
}


/***********main function************/
/***********main function************/

int main()
{

  int server_fd, ret;

  struct sockaddr_in server_addr;
  
  int cl_sock_fd[MAX_CLIENTS];  
  
  setup_message_handlers();

  pthread_t cl_threads[MAX_CLIENTS];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_fd < 0) 
  {
    printf("Error in connection.\n");
    exit(1);
  }

  printf("TCP Server Socket is created.\n");

  //SETTING MEMORY ADDRESS TO \0
  memset(&server_addr, '\0',  sizeof(server_addr));

  //BUILD THE STRUCTURE FOR SERVER ADDRESS
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  //BIND THE SOCKET TO THE ADDRESS AND PORT NUMBER SPECIFIED IN THE STRUCTURE
  ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

  if (ret < 0) 
  {
    printf("Error in binding.\n");
    exit(1);
  }
   
  //LISTEN TO ANY INCOMING CLIENT
  if (listen(server_fd, 10) == 0) 
  {
    printf("Listening...\n\n");
  }

  while (1) 
  {
    ret = accept(server_fd, NULL, NULL);

    //CHECK IF THE CLIENT SOCKET IS CREATED PROPERLY
    if (ret < 0) 
    {
      perror("accept failed: ");
      exit(1);
    }

    cl_sock_fd[cl_count] = ret;
      
    printf("cl_count = %d fd = %d clfd = %d \n",
             cl_count, ret, cl_sock_fd[cl_count]);

    ret = pthread_create(&cl_threads[cl_count], NULL, client_handler,
                         &cl_sock_fd[cl_count]);
   
    if (ret == 0)
    {
      cl_count++;

      printf("A new thread is created for client on fd: %d \n",
             cl_sock_fd[cl_count]);
      printf("Total clients connected : %d\n\n", cl_count);
    }  

    if (cl_count == MAX_CLIENTS)
    {
      printf("Max clients %d are connected..No more connections will be accepted\n", 
             cl_count);
      break;
    }
  }

  for (int i = 0; i < cl_count; i++)
  {  
    pthread_join(cl_threads[i], NULL);
  }

  return 0;
}



