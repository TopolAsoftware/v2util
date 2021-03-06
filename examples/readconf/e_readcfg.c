/* Autor Oleg Vlasenko */

/* Example config file reading */

/*
 * Read configuration from the file "e.cfg" to next structure
 *
 */

#include "v2_util.h"
#include <errno.h>

#define MY_CONFIG_FILE "e.cfg"

struct my_config_s {
    char *name;
    char *color;

    int counter;
} my_config;

/* ============================================================= */
int e_read_str(char *in_str, void *my_data) {
    struct my_config_s *mcfg=my_data;
    char *st_str=in_str+strspn(in_str, " \t");

    // Skip trailed spaces

    if(v2_cf_var(&mcfg->name,    st_str, "name"))    return(0);
    if(v2_cf_var(&mcfg->color,   st_str, "color"))   return(0);
    if(v2_cf_int(&mcfg->counter, st_str, "counter")) return(0);

    // here in_str contains domething what is not expected config value
    // you can register it or just ignore
    printf("WRN! Config file contains string: %s\n", st_str);

    return(0);
}
/* ============================================================= */
int main() {
    int rc=0;

    /* Just read file and call e_read_str() for each string */
    /* Symbol '#' at start file name means skip comments and empty strings */
    if((rc=sfread(&e_read_str, &my_config, "#" MY_CONFIG_FILE))) {
	printf("ERROR! Fuction returns[rc=%d]: %s (%s)\n", rc, v2_xrc(rc), strerror(errno));
	return(0);
    }

    /* Print all out variables */

    printf("Red config file \""MY_CONFIG_FILE"\" next values:\n");

    printf("name    = '%s'\n", v2_st(my_config.name,    "-=none=-"));
    printf("color   = '%s'\n", v2_st(my_config.color,   "-=none=-"));
    printf("counter =  %d\n", my_config.counter);

    return(0);
}
/* ============================================================= */

