#ifndef CONFIG_H
#define CONFIG_H

#define DEFAULT_TAPE_SIZE 30000
#define DEFAULT_MAX_STEPS 1000000

typedef struct {
    int tape_size;
    int max_steps;
    int debug;
    int silent;
    char log_file[256];
    char tape_dump_file[256];
} Config;

void config_set_defaults(Config *config);
int config_load(Config *config, const char *filename);

#endif