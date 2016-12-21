#include "URL_DECODE.h"

String URL;
int numParameters = 0;
String dataSerial;
char *t;
char data[MAX_DATA_ARRAY_LENGTH];
const char delim_space[DELIM_ARRAY_LENGTH] = " ", delim_question_mark[DELIM_ARRAY_LENGTH] = "?", delim_and[DELIM_ARRAY_LENGTH] = "&", delim_eq[DELIM_ARRAY_LENGTH] = "=";
char *token, *q_token, *_token, *key_token, *val_token, *data_query, *data_parameter_query;
char *each_param[MAX_ARRAY_LENGTH];

struct Data_struct
{
  char *keys[MAX_ARRAY_LENGTH];
  char *vals[MAX_ARRAY_LENGTH];
  char *method[HTTP_METHOD_ARRAY_LENGTH];
  };

struct Data_struct data_struct;

URL_DECODE::URL_DECODE(String url)
{
    URL = url;
}

URL_DECODE::~URL_DECODE()
{
    /* nothing to destrct */
}

char* extract_query_string_space(const char *delim, char *data_str)
{
  token = strtok(data_str, delim);
  data_struct.method[0] = token;
  while(token != NULL)
  {
    token = strtok(NULL, delim);
    return token;
    }
  }

char* extract_query_string_qMark(const char *delim, char *data_str)
{
  q_token = strtok(data_str, delim);
  while(q_token != NULL)
  {
    q_token = strtok(NULL, delim);
    return q_token;
    }
  }

  int extract_each_parameter_set(const char *delim, char *data_params)
{
  int num = 0;
  while((_token = strtok(data_params, delim)) != NULL)
  {
    data_params = NULL;
    each_param[num] = _token;
    num += 1;
  }
  return num;
}

void extract_key_value(const char *delim, char *param, int i)
{
   key_token = strtok(param, delim);
   param = NULL;
   val_token = strtok(param, delim);
   data_struct.keys[i] = key_token;
   data_struct.vals[i] = val_token;
  }

  int URL_DECODE::decodeUrl()
{
    URL.toCharArray(data, MAX_DATA_ARRAY_LENGTH);
    data_query = extract_query_string_space(delim_space, data);
    data_parameter_query = extract_query_string_qMark(delim_question_mark, data_query);
    numParameters = extract_each_parameter_set(delim_and, data_parameter_query);
    for (int i = 0; i < numParameters; i++)
    {
      t = each_param[i];
      extract_key_value(delim_eq, t, i);
      }
    return numParameters;
}

struct Data_struct URL_DECODE::getParams(void)
{
    return data_struct;
}