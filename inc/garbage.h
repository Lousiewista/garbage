#ifndef __GARBAGE__H
#define __GARBAGE__H

void garbage_init(void);
void garbage_final(void);
char *garbage_category (char *category);

#define WGET_CMD     "wget http://192.168.31.134:8080/?action=snapshot -O /tmp/garbage.jpg"
#define GARBAGE_FILE "/tmp/garbage.jpg"

#endif
