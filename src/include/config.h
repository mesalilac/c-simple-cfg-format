#ifndef H_CONFIG
#define H_CONFIG

typedef struct
{
    char *key;
    char *value;
    char *comment;
} Kv;

typedef struct
{
    Kv **list;
    int count;
} KvList;

int config_parse(char *file, KvList *KvList);
char *config_get(KvList KvList, char *key);
int config_set(KvList *kv_list, char *key, char *value);
void config_remove(KvList *kv_list, char *key);
int config_save(KvList kv_list, char *file);

#endif // !H_CONFIG
