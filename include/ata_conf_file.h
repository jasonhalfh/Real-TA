#ifndef _ATA_CONF_FILE_
#define _ATA_CONF_FILE_

/*typedef struct {
	unsigned int len;
	char data[256]; // 256???
}ata_str_t;
*/

#include  <ata_core.h>


#define IS_PTR_ERR(ptr, ctx) if(ptr == NULL) \
	{ printf(ctx); return NULL; }


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
	unsigned int key;
	char val[256];
};

struct ata_conf_s {
	unsigned int conf_nr; 
	struct ata_keyval_s *conf_keyval;		

	unsigned int node_nr;
	struct ata_standitem_s **tracks;

	unsigned int snapshot_peroid;
	unsigned int snapshot_time;
	struct ata_standitem_s **snapshot;
};

struct ata_module_ctx_s {
	// to be add ...	
	char *conf_file;
	struct ata_conf_s *gconf;
};

struct ata_module_s {
	unsigned int index;
	unsigned int type;
	unsigned int version;
	char *name;
	struct 	ata_command_s *commands;	
	struct ata_module_ctx_s *ctx;
	
	int (*handle)(struct ata_module_ctx *ctx);	
	int (*init_module)();
	int (*exit_module)();

	struct list_head flow_next;
};

/*
struct ata_module_flow_s {
	struct ata_module_s *module;
	list_head *next;
};
*/


struct ata_standitem_s {
	double x;
	double y;
	double time;
	unsigned int nid;
};

typedef enum {
	FIRST_TPYE = 0x110,

	INDIR,
	OUTDIR,		

	IMPORT,
	FILTER,
	ANALYSE,
	
	LAST_TYPE,
} MODULE_TYPE;

extern struct ata_module_s *ata_modules[];

#endif
