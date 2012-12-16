#include "test.h"



static size_t writer(void *ptr, size_t size, size_t nmemb, void *stream)
{
  strcpy((char*)stream, (char*)ptr);
  return size * nmemb;
}

char* curl_send_query(char* url, char* query){
  CURL *curl;
  char* response = (char*)malloc(10240*sizeof(char));
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_HEADER, false);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10000);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, false);
  curl_easy_setopt(curl, CURLOPT_POST, true);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  if (DEBUG) fprintf(stderr,"request: %s\n",query);
  if (DEBUG) fprintf(stderr,"response: %s\n",response);
  return response;
}

bool check_packet(json_t *packet, const char* packet_name){
  if (!packet) {
      if (DEBUG) fprintf(stderr, "%s error\n", packet_name);
  }
  else {
    if (!json_is_object(packet)) {
      if (DEBUG) fprintf(stderr, "%s error, is not an object!\n",packet_name);
    }
    else {
      if (!json_is_true(json_object_get(packet,"status"))){
        if (DEBUG) fprintf(stderr,"Status:not true\n");
      }
      else return true;
    }
  }
  return false;
}


json_t* send_users_login(char *url, char *username, char *password){
  json_t *root;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query, "query={\"cmd\":\"users/login\",\"params\":{\"device\":\"351863048093054\",\"passwd\":\"");
  strcat(query, password);
  strcat(query, "\",\"login\":\"");
  strcat(query,username);
  strcat(query, "\",\"version\":\"9.0.9\"}}");
  
  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response); 
  free(query);
  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

json_t* send_users_logout(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query, "\",\"cmd\":\"users/logout\"}");

  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response);
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

json_t* send_settings_list(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query, "\",\"cmd\":\"settings/list\"}");

  char *response;
  // = (char*)malloc(10240*sizeof(char));
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response); 
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

json_t* send_shift(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query,"\",\"gps\":{\"rssi\":99,\"long\":0.0,\"alt\":0.0,\"lat\":0.0,\"cell\":\"12345\"}");
  strcat(query, ",\"cmd\":\"shift\"");
  strcat(query, ",\"params\":{\"status\":\"true\"}}");

  // {"session":"ALU609fvz6bUglQgb0ihoQGMOpy4tUu3","gps":{"rssi":99,"long":0,"alt":0,"lat":0,"cell":"131486"},"cmd":"shift","params":{"status":"true"}}

  char *response;
  // = (char*)malloc(10240*sizeof(char));
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response); 
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}


json_t* send_variables_list(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query, "\",\"cmd\":\"variables/list\"}");

  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response);
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}


json_t* send_event_list_light(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query,"\",\"gps\":{\"rssi\":99,\"long\":0.0,\"alt\":0.0,\"lat\":0.0,\"cell\":\"12345\"},");
  strcat(query, "\"cmd\":\"events/list/light\"");
  strcat(query, ",\"params\":{\"date\":\"2012-12-11 00:18:25 +0900\"}}");

  //fprintf(stdout,"\n\n\n%s\n\n\n",query);
  //exit(0);


  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response);
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

json_t* send_sites_list(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query, "{\"session\":\"");
  strcat(query, session);
  strcat(query, "\",\"cmd\":\"sites/list\"}");

  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response);
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

json_t* send_chats_get_all_unread_message(char *url, char* session){
  json_t *root, *json_status;
  json_error_t error;

  char *query = (char*)malloc(1024*sizeof(char));
  strcpy(query,"query={\"session\":\"");
  strcat(query,session);
  strcat(query,"\",\"gps\":{\"rssi\":99,\"long\":0.0,\"alt\":0.0,\"lat\":0.0,\"cell\":\"12345\"},");
  strcat(query, "\"cmd\":\"chats/get_all_unread_message\"");
  strcat(query, ",\"params\":{\"date\":\"2012-12-11 00:18:25 +0900\"}}");;

  char *response;
  response = curl_send_query(url, query);
  root = json_loads(response, 0, &error); 
  free(response);
  free(query);

  if (check_packet(root,__FUNCTION__)) return(root); else return NULL;
}

int main(int argc, char **argv)
{
  char *port = (char*)malloc(5*sizeof(char));
  char *host = (char*)malloc(255*sizeof(char));

  if (argc < 3){
    fprintf(stderr, "USAGE: %s hostname port\n",argv[0]);
    return(-1);
  }
  else{
    host=(char *)argv[1];
    port=(char *)argv[2];
  //  return(0);
  }

  struct timeval start, end;
  long mtime, seconds, useconds; 
  char *session = (char*)malloc(255*sizeof(char));

  thread_attrs* attrs = (thread_attrs*)malloc(sizeof(thread_attrs));

  strcpy(attrs->url,"http://");
  strcat(attrs->url, host);
  strcat(attrs->url,":");
  strcat(attrs->url,port);
  if (DEBUG) fprintf(stderr,"url:%s\n",attrs->url);

  sprintf(attrs->username,"devadmin");
  sprintf(attrs->password,"devadmin");

  while(1){
    
    json_t *json_object;

    json_object = send_users_login(attrs->url,attrs->username,attrs->password);
    if (!json_object) {
      if (DEBUG) fprintf(stderr, "Login packet fail");
      return -1;
    }
    else {
      
      json_object = json_object_get(json_object, "session");
      session = (char*)json_string_value(json_object);
      if (session) {
        json_object = send_settings_list(attrs->url,session);
        json_object = send_variables_list(attrs->url,session);
        json_object = send_event_list_light(attrs->url,session);
        json_object = send_sites_list(attrs->url,session);
        json_object = send_shift(attrs->url,session);
        json_object = send_chats_get_all_unread_message(attrs->url,session);
        json_object = send_users_logout(attrs->url,session);
      } else {
        if (DEBUG) fprintf(stdout,"Error in packet\n");
      }
      json_decref(json_object);
      if (DEBUG) {
        free(attrs);
        free(session);
        return 0;
      }
    }
  }

  free(attrs);
  free(session);
  return 0;
}
