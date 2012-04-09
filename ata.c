#include <ata_conf_file.h>


#define IS_PTR_ERR(ptr, ctx) if(ptr == NULL) \
	{ printf(ctx); return NULL}


struct ata_conf_s *ata_conf_init()
{
	struct ata_conf_s *conf;
	struct ata_keyval_s *keyval;
	FILE *fp;
	int i;
	conf = (struct ata_conf_s*)malloc(sizeof(struct ata_conf_s));
	IS_PTR_ERR (conf, "Malloc conf err\n");
	memset(conf, 0, sizeof(struct ata_conf_s));
	
	keyval = (struct ata_keyval_s*)malloc(sizeof(struct ata_keyval_s) * MAX_CONFIG);
	IS_PTR_ERR(keyval, "Malloc keyval failed\n");
	memset(keyval, 0, sizeof(struct ata_keyval_s) * MAX_CONFIG);
		
	fp = fopen(DEFAULT_CONF, "r");
	IS_PTR_ERR (fp, "Open conf file failed\n");
	
	i = 0;
	while (fscanf(fp, "%s\t%s", (keyval+i).key, (keyval+i).val) != EOF && i < MAX_CONFIG) {
		i ++;
	}
	
	conf->conf_num = i;
	conf->conf_keyval = keyval;
	
	return conf;
}

int ata_modules_init(struct ata_module_s **m)
{
	int i;
	
	for (i = 0; m[i]; i++) {
		m[i]->index = i;
		m[i]->init_module;	
	}

	return i;
}

void ata_modules_clean(struct ata_module_s **m)
{
	for (i = 0; m[i]; i++) {
		m[i]->exit_module;
	}		
}

void ata_conf_clean(struct ata_conf_s *conf)
{
	if (conf != NULL) {
		free(conf);
		conf = NULL;
	}
}

struct list_head *module_flow_init(struct ata_conf_s *conf,
				   struct ata_module_s **m, int nr)
{
	int i;
	struct ata_keyval_s *kv = conf->conf_keyval;
	
	LIST_HEAD(process_flow);
	
	
	for (i = 0; i < PROCESS_STEPS; i++) {
		list_add(find_module_by_kv(kv+i , m)->flow_next,
			 process_flow);	
	}
	
	//list_add(m[nr], process_flow);
	
	return process_flow;	
}

int start(struct ata_conf_s *conf, struct list_head *flow)
{
	int i;
	struct list_head *pos;
	struct ata_module_s *tmp;
	list_for_each_entry(tmp, pos, flow) {
		tmp->handle;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct ata_command_s *commands;
	struct ata_log_s *log;
	struct ata_conf_s *conf;
	struct ata_module_flow_s *module_flow;
	struct list_head *process;
	int module_nr;

	conf = ata_conf_init();	

	//commands = ata_command_parse(conf);
	//log = ata_log_init(conf);	
	
	module_nr = ata_modules_init(ata_modules);
	
		
	process = module_flow_init(conf, ata_modules, module_nr);
	
	start(conf, process);

	ata_conf_clean(conf);

	//ata_log_clean();
	//ata_command_clean();
	ata_modules_clean(ata_modules);
}
