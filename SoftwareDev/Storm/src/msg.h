#ifndef MSG
#define MSG

typedef enum{
    MSG_CFG,
    MSG_PATTERN,
    MSG_LED_SET
}msg_type;

typedef struct 
{
    msg_type type;
    void * data;
}msg_t;

#endif