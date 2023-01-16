#define MAX_CLIENTS 1
#define MAX_USERS   5
#define PORT 4444
#define SEND_BUFFER_SIZE 512
#define RECV_BUFFER_SIZE 512
typedef struct user_info
{
  struct user_info *next;
} user_info_t;

