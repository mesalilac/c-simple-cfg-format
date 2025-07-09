#include "config.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool prefix(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}

int config_parse(char *file, KvList *kv_list) {
  FILE *fptr;
  fptr = fopen(file, "r");

  if (fptr == NULL) {
    fprintf(stderr, "ERROR: File does not exists!");
    exit(1);
  }

  char line[100];

  while (fgets(line, 100, fptr)) {
    if (prefix("#", line)) {
      Kv *kv = (Kv *)malloc(sizeof(Kv));

      kv->key = NULL;
      kv->value = NULL;
      kv->comment = (char *)malloc(strlen(line) + 1);
      strcpy(kv->comment, line);

      kv_list->list[kv_list->count] = kv;
      kv_list->count++;

      continue;
    }

    size_t cursor = 0;
    bool reading_value = false;
    char *key = (char *)malloc(100 * sizeof(char));
    int key_cursor = 0;
    char *value = (char *)malloc(100 * sizeof(char));
    int value_cursor = 0;

    while (line[cursor] != '\n') {
      // Start reading value
      // key value
      //     ^
      if (line[cursor] == ' ' && reading_value == false) {
        ++cursor; // skip the empty space
        reading_value = true;
      }

      if (reading_value == true) {
        value[value_cursor] = line[cursor];
        ++value_cursor;
      }

      if (reading_value == false) {
        key[key_cursor] = line[cursor];
        ++key_cursor;
      }
      ++cursor;
    }

    key[key_cursor] = '\0';
    value[value_cursor] = '\0';

    Kv *kv = (Kv *)malloc(sizeof(Kv));
    kv->key = malloc(strlen(key) + 1);
    strcpy(kv->key, key);
    kv->value = malloc(strlen(value) + 1);
    strcpy(kv->value, value);
    kv_list->list[kv_list->count] = kv;
    kv_list->count += 1;
  }

  fclose(fptr);

  return 0;
}

char *config_get(KvList kv_list, char *key) {
  for (int i = 0; i < kv_list.count; ++i) {
    if (kv_list.list[i]->key == NULL)
      continue;

    if (strcmp(key, kv_list.list[i]->key) == 0) {
      return kv_list.list[i]->value;
    }
  }

  return NULL;
}

int config_set(KvList *kv_list, char *key, char *value) {
  // Change value if `key` already exists
  for (int i = 0; i < kv_list->count; i++) {
    // NOTE: strcmp Segmentation fault when kv_list->list[i]->key is null
    if (kv_list->list[i]->key != NULL &&
        strcmp(key, kv_list->list[i]->key) == 0) {
      kv_list->list[i]->value = value;
      return 0;
    }
  }

  // resize kv_list->list
  if (kv_list->count >= 100) {
    printf("about to realloc\n");
    int new_size = kv_list->count * sizeof(Kv *);

    Kv **new_list = realloc(kv_list->list, new_size);

    if (new_list == NULL) {
      fprintf(stderr,
              "ERROR: Failed to reallocate memory for kv_list->list.\n");
      exit(1);
    }

    kv_list->list = new_list;
  }

  // Insert a new kv
  Kv *kv = (Kv *)malloc(sizeof(Kv));
  kv->key = key;
  kv->value = value;
  kv_list->list[kv_list->count] = kv;
  kv_list->count += 1;

  return 0;
}

void config_remove(KvList *kv_list, char *key) {
  int i;

  for (i = 0; i < kv_list->count; ++i) {
    if (kv_list->list[i]->key != NULL &&
        strcmp(kv_list->list[i]->key, key) == 0) {
      free(kv_list->list[i]);
      break;
    }
  }

  if (i < kv_list->count) {
    for (; i < kv_list->count; ++i)
      kv_list->list[i] = kv_list->list[i + 1];

    kv_list->count--;
  }
}

int config_save(KvList kv_list, char *file) {
  FILE *fptr = fopen(file, "w");

  for (int i = 0; i < kv_list.count; ++i) {
    if (kv_list.list[i]->comment == NULL) {
      fprintf(fptr, "%s %s\n", kv_list.list[i]->key, kv_list.list[i]->value);
    } else {
      fprintf(fptr, "%s", kv_list.list[i]->comment);
    }
  }

  fclose(fptr);
  return 0;
}
