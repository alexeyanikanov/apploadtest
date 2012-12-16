// #include <stdlib.h>
// #include <sys/time.h>
// #include <pthread.h>
#include <curl/curl.h> 
#include <string.h>
#include <jansson.h>
#define NUMT 20
#define DEBUG true


// const char * const url="http://192.168.222.18:11400";
//const char * const url="http://192.168.222.10:11400";

struct thread_attrs{
  char url[255];
  char username[255];
  char password[255];
};

static size_t writer(void *ptr, size_t size, size_t nmemb, void *stream);
char* curl_send_query(char* url, char* query);
json_t* send_users_login(char *url, char *username, char *password);
json_t* send_settings_list(char *url, char* session);
json_t* send_variables_list(char *url, char* session);
json_t* send_event_list_light(char *url, char* session);
json_t* send_sites_list(char *url, char* session);
json_t* send_shift(char *url, char* session);
//json_t* send_chats_get_all_unread_message(char *url, char* session);
json_t* send_users_logout(char *url, char* session);
bool check_packet(json_t *packet, const char* packet_name);
json_t* send_chats_get_all_unread_message(char *url, char* session);

//{"session":"ALU609fvz6bUglQgb0ihoQGMOpy4tUu3","gps":{"rssi":99,"long":0,"alt":0,"lat":0,"cell":"132308"},"cmd":"chats\/get_all_unread_message"}
