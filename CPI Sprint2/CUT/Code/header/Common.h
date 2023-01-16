
#define MAX_DATA_LEN  128
#define DATA_SIZE 1000

typedef enum 
{
  MSG_CREATE_WRITE = 1,
  MSG_COPY_FILE = 2,
  MSG_DELETE_FILE = 3,
  MSG_LS_CMD = 4,
  MSG_CAT_CMD = 5,
  MSG_MAX = 6
  
} msg_type_e;


typedef struct 
{
  msg_type_e  msg_type; 
  char        msg_data[MAX_DATA_LEN];
  char        msg_add_data[MAX_DATA_LEN];

} msg_t;

typedef struct 
{
  void        (*msg_action_function) (int, msg_t *);

} msg_action_t;


int create_write();
int copy_file();
int delete_file();
int ls_cmd();
int cat_file();