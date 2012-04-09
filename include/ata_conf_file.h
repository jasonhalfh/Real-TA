#ifndef _ATA_CONF_FILE_
#define _ATA_CONF_FILE_

/*typedef struct {
	unsigned int len;
	char data[256]; // 256???
}ata_str_t;
*/

#include  <ata_core.h>


#define DEFAULT_CONF "./default.conf"
#define MAX_CONFIG 15
#define PROCESS_STEPS 3

struct ata_command_s {
	char name[256];
	unsigned int type;
};

struct ata_log_s { // to be add...

};

struct ata_keyval_s {
	char key[256];
	char val[256];
};
typedef struct ata_kerval_s ata_kerval_t;


struct ata_conf_s {
	unsigned int conf_num;
	ata_keyval_t *conf_keyval;
	
	
	//char module_name;
};

struct ata_module_ctx {
	// to be add ...
	
};

struct ata_module_s {
	unsigned int index;
	unsigned int type;
	unsigned int version;
	ata_command_s *commands;
	
	ata_module_ctx *ctx;
	int (*handle)(struct ata_module_ctx *ctx);
	
	int (*init_module)();
	int (*exit_module)();
	list_head *flow_next;
};


struct ata_module_flow_s {
	struct ata_module_s *module;
	list_head *next;
};





extern struct ata_module_s *ata_modules[];

#endif
