/*THIS IS THE CLIENT PROGRAM WHERE WE SENT THE USER INFORMATION TO SERVER AND 
  GETTING THE REQUESTED SERVICE FROM THE SERVER

********************************************************************************
 ** FILENAME          :    client.c
 **
 ** DESCRIPTION       :    Implementation of Custom Protocol 
 **
********************************************************************************
                               HEADER FILES
********************************************************************************
*/

#include<stdio.h>           //INCLUDES INPUT OUTPUT RELATED FUNCTIONS
#include<stdlib.h>          //INCLUDES FUNCTIONS INVOLVING MEMORY ALLOCATION,UTILITY FUNCTIONS FOR TYPE CONVERSION
#include<string.h>          //INCLUDES FUNCTIONS TO PERFORM STRING OPERATIONS 
#include<unistd.h>          //PROVIDES ACCESS TO POSIX OS API
#include<sys/types.h>       //INCLUDES TYPEDEF SYMBOLS AND STRUCTURES
#include<sys/socket.h>      //INCLUDES SOCKADDR STRUCTURE
#include<netinet/in.h>      //INCLUDES THE INTERNET ADDRESS FAMILY
#include<arpa/inet.h>       //INCLUDES THE DEFENITONS FOR INTERNET OPERATIONS

#include"common.h"

/******************************************************************************
                                 MACROS
******************************************************************************/

#define PORT 4444
#define SEND_BUFFER_SIZE 512
#define RECV_BUFFER_SIZE 512

#define MSG_SUCCESS  1
#define MSG_FAIL     2
#define MSG_INVALID  3
#define MAX_INPUT_LEN   32


int cl_sock_fd;

char send_buffer[SEND_BUFFER_SIZE];
char recv_buffer[RECV_BUFFER_SIZE];



/*******************Custom impelmentation of messages*****************/

/*******************handle_server_close*****************/
/*******************handle_server_close*****************/


void handle_server_close (int sockfd)
{

  close(sockfd);

}

/*******************create*****************/

int create(char *str)
{
	int ret;
	msg_t msg;
	
	memset(msg.msg_data, '\0', sizeof(msg.msg_data));
	
	printf("Enter yes to create\n");
	scanf("%s", str);
	
	msg.msg_type = MSG_CREATE_WRITE;
	strncpy(msg.msg_data, str, strlen(str));
	
	
	ret =send(cl_sock_fd, (char *) &msg, sizeof(msg), 0);
	printf("Sent bytes = %d \n", ret);

		
	
}

/*******************copy*****************/

	
int copy(char *str)
{
	int ret;
	msg_t msg;
	
	memset(msg.msg_data, '\0', sizeof(msg.msg_data));
	
	printf("Enter yes to copy\n");
	scanf("%s", str);
	
	msg.msg_type = MSG_COPY_FILE;
	strncpy(msg.msg_data, str, strlen(str));
	
	
	ret =send(cl_sock_fd, (char *) &msg, sizeof(msg), 0);
	printf("Sent bytes = %d \n", ret);

		
	
}


/*******************delete*****************/


int delete(char *str)
{
	int ret;
	msg_t msg;
	
	memset(msg.msg_data, '\0', sizeof(msg.msg_data));
	
	printf("Enter yes to delete\n");
	scanf("%s", str);
	
	msg.msg_type = MSG_DELETE_FILE;
	strncpy(msg.msg_data, str, strlen(str));
	
	
	ret =send(cl_sock_fd, (char *) &msg, sizeof(msg), 0);
	printf("Sent bytes = %d \n", ret);

		
	
}

/*******************ls*****************/


int ls(char *str)
{
	int ret;
	msg_t msg;
	
	memset(msg.msg_data, '\0', sizeof(msg.msg_data));
	
	printf("Enter yes to ls\n");
	scanf("%s", str);
	
	msg.msg_type = MSG_LS_CMD;
	strncpy(msg.msg_data, str, strlen(str));
	
	
	ret =send(cl_sock_fd, (char *) &msg, sizeof(msg), 0);
	printf("Sent bytes = %d \n", ret);

		
	
} 


/*******************cat*****************/


int cat(char *str)
{
	int ret;
	msg_t msg;
	
	memset(msg.msg_data, '\0', sizeof(msg.msg_data));
	
	printf("Enter yes to cat\n");
	scanf("%s", str);
	
	msg.msg_type = MSG_CAT_CMD;
	strncpy(msg.msg_data, str, strlen(str));
	
	
	ret =send(cl_sock_fd, (char *) &msg, sizeof(msg), 0);
	printf("Sent bytes = %d \n", ret);

		
	
} 



/*******************handle_client_close*****************/
/*******************handle_client_close*****************/


void handle_client_close(int sock_fd)
{

  /* TODO */
  close(sock_fd);

}

/*******************main*****************/
/*******************main*****************/


int main()
{
  int ret;
  int i, option;

  struct sockaddr_in server_addr;

  int  menu_data_int;
  char menu_data_string1[MAX_INPUT_LEN];
  char menu_data_string2[MAX_INPUT_LEN];


  cl_sock_fd = socket(AF_INET,SOCK_STREAM, 0);

  //CHECK IF SOCKET IS CREATED PROPERLY
  if (cl_sock_fd < 0) 
  {
    printf("Error in connection.\n");
    exit(1);
  }

  printf("Client Socket is created.\n");

  memset(send_buffer, '\0', sizeof(send_buffer));
  memset(recv_buffer, '\0', sizeof(recv_buffer));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  //NOW TRY TO CONNECT WITH SERVER

  ret = connect(cl_sock_fd, (struct sockaddr*)&server_addr,
      sizeof(server_addr));

  if (ret < 0) 
  {
    printf("Error in connection.\n");
    exit(1);
  }

  printf("Connected to Server.\n");

  while (1) 
  {
    //PRINTING MENU OPTIONS FOR USER SELECTION

    printf("\t\t****************==============****************\n");
    printf("\t\t\t\tMenu Interface\t\t\n");
    printf("\t\t****************==============****************\n");

    printf("\t\t1.create_file  \n");
    printf("\t\t2.copy_file  \n");
    printf("\t\t3.delete_file  \n");
    printf("\t\t4.ls_cmd  \n");
    printf("\t\t5.cat_cmd \n");
    printf("\t\t6.Exit \n");
    scanf("%d", &option);
  
    memset(menu_data_string1, '\0', sizeof(menu_data_string1));
    
    switch(option)
    {
      
			case 1:create(menu_data_string1);
			       break;
			case 2:copy(menu_data_string1);
				 break;
			case 3:delete(menu_data_string1);
				 break;
			case 4:ls(menu_data_string1);
				 break;
			case 5:cat(menu_data_string1);
				 break;
     		      case 6:
                   exit(0);

                  default:
                  printf("Invalid Option .. \n");
                  break;
    }

  }

  return 0;
}

