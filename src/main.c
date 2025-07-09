#include "include/config.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  KvList kv_list;
  kv_list.list = malloc(100 * sizeof(Kv));
  kv_list.count = 0;

  char *file = "example.config";
  config_parse(file, &kv_list);

  config_set(&kv_list, "name", "mike");
  config_set(&kv_list, "title", "Linux");
  /* config_remove(&kv_list, "title"); */

  for (int i = 0; i < kv_list.count; ++i) {
    if (kv_list.list[i]->key && kv_list.list[i]->value)
      printf("key = '%s', value = '%s'\n", kv_list.list[i]->key,
             kv_list.list[i]->value);
  }

  config_save(kv_list, "example-save.config");

  char *title = config_get(kv_list, "title");
  printf("title = '%s'\n", title);
  char *name = config_get(kv_list, "name");
  printf("name = '%s'\n", name);
}
