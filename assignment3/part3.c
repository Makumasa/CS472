#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>

#define CACHE_PATH "/sys/devices/system/cpu/cpu0/cache/"

/* Adapted from https://stackoverflow.com/questions/1121383/counting-the-number-of-files-in-a-directory-using-c */
uint8_t cache_count() {
    uint8_t count = 0;
    DIR* cache_dir;
    struct dirent* entry;

    cache_dir = opendir(CACHE_PATH);
    if (cache_dir == NULL) {
        fprintf(stderr, "Error: could not open cache directory.\n");
        exit(-1);
    }
    while ((entry = readdir(cache_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            count++;
        }
    }

    closedir(cache_dir);
    return count;
}

char* cache_type(uint8_t i) {
    static char type[64];
    char filename[256];
    FILE* f;
    sprintf(filename, "%s%s%u%s", CACHE_PATH, "index", i, "/type");
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: could not open cache type file.\n");
        exit(-1);
    }
    memset(type, 0, sizeof(type));
    fscanf(f, "%s", type);
    fclose(f);
    return type;
}

uint8_t cache_level(uint8_t i) {
    uint8_t level;
    char filename[256];
    FILE* f;
    sprintf(filename, "%s%s%u%s", CACHE_PATH, "index", i, "/level");
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: could not open cache level file.\n");
        exit(-1);
    }
    fscanf(f, "%hhu", &level);
    fclose(f);
    return level;
}

uint64_t cache_line_size(uint8_t i) {
    uint64_t line_size;
    char filename[256];
    FILE* f;
    sprintf(filename, "%s%s%u%s", CACHE_PATH, "index", i, 
            "/coherency_line_size");
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: could not open cache line size file.\n");
        exit(-1);
    }
    fscanf(f, "%lu", &line_size);
    fclose(f);
    return line_size;
}

uint64_t cache_sets(uint8_t i) {
    uint64_t sets;
    char filename[256];
    FILE* f;
    sprintf(filename, "%s%s%u%s", CACHE_PATH, "index", i,
        "/number_of_sets");
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: could not open cache sets file.\n");
        exit(-1);
    }
    fscanf(f, "%lu", &sets);
    fclose(f);
    return sets;
}

uint64_t cache_ways(uint8_t i) {
    uint64_t ways;
    char filename[256];
    FILE* f;
    sprintf(filename, "%s%s%u%s", CACHE_PATH, "index", i,
        "/ways_of_associativity");
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Error: could not open cache ways file.\n");
        exit(-1);
    }
    fscanf(f, "%lu", &ways);
    fclose(f);
    return ways;
}

uint64_t cache_size(uint8_t i) {
    return cache_line_size(i) * cache_ways(i) * cache_sets(i) / 1024;
}

int main() {
    uint8_t num_caches = cache_count();
    printf("Number of caches:              %u\n\n", num_caches);
    for (int i = 0; i < num_caches; ++i) {
        printf("Cache %d level:                 %u\n", i, cache_level(i));
        printf("Cache %d type:                  %s\n", i, cache_type(i));
        printf("Cache %d line size:             %lu\n", i, cache_line_size(i));
        printf("Cache %d ways of associativity: %lu\n", i, cache_ways(i));
        printf("Cache %d number of sets:        %lu\n", i, cache_sets(i));
        printf("Cache %d size:                  %luK\n\n", i, cache_size(i));
    }
    return 0;
}
