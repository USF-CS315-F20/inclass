#ifndef _MAP_H
#define _MAP_H

#define MAP_KEY_LEN 64
#define MAP_VALUE_LEN 64
#define MAP_TABLE_LEN 128

struct map_pair_st {
    char key[MAP_KEY_LEN];
    char value[MAP_VALUE_LEN];
};

struct map_st {
    struct map_pair_st table[MAP_TABLE_LEN];
    int count;
};

void map_init(struct map_st *map);
void map_add(struct map_st *map, char *key, char *value);
char * map_lookup(struct map_st *map, char *key);

#endif
