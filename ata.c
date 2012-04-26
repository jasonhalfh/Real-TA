#include <ata_conf_file.h>


struct ata_conf_s *ata_conf_init()
{
	struct ata_conf_s *conf;
	struct ata_keyval_s *keyval;
	FILE *fp;
	char key[256];
	char val[256];
	int i;
	
	conf = (struct ata_conf_s*)malloc(sizeof(struct ata_conf_s));
	IS_PTR_ERR (conf, "Malloc conf err\n");
	memset(conf, 0, sizeof(struct ata_conf_s));
	
	keyval = (struct ata_keyval_s*)malloc(sizeof(struct ata_keyval_s) * MAX_CONFIG);
	IS_PTR_ERR(keyval, "Malloc keyval failed\n");
	memset(keyval, 0, sizeof(struct ata_keyval_s) * MAX_CONFIG);
		
	/* read conf file <default.conf> */
	fp = fopen(DEFAULT_CONF, "r");
	IS_PTR_ERR (fp, "Open conf file failed\n");
	
	i = 0;
	while (fscanf(fp, "%s\t%s", key, val) != EOF 
	       && i < MAX_CONFIG) {
		if (0 == strcmp(key, "import")) {
			(keyval + i)->key = IMPORT;
			strcpy((keyval + i)->val,val);
		} else if (0 == strcmp(key, "filter")) {
			(keyval + i)->key = FILTER;
			strcpy((keyval + i)->val,val);                        
		} else if (0 == strcmp(key, "analyse")) {
			(keyval + i)->key = ANALYSE;
			strcpy((keyval + i)->val,val);
		}
		
		i ++;
	}

	conf->conf_nr = i;
	conf->conf_keyval = keyval;
	
	return conf;
}

void free_tracks(struct ata_standitem_s **tracks, unsigned int nr)
{
	int i;
	if (tracks == NULL)
		return ;
	
	i = 0;
	while (i < nr) {
		free(*(tracks + i));
		i ++;
	}
	
	free(tracks);
	tracks = NULL;
}

void ata_conf_clean(struct ata_conf_s *conf)
{
	if (conf != NULL) {
		free(conf->conf_keyval);
		free_tracks(conf->tracks, conf->node_nr);
		free(conf);
		conf = NULL;
	}
}


int ata_modules_init(struct ata_module_s **m)
{
	int i;
	
	for (i = 0; m[i]; i++) {
		m[i]->index = i;
		if (m[i]->init_module == NULL)
			continue;
		else 
			m[i]->init_module();
	}

	return i;
}

void ata_modules_clean(struct ata_module_s **m)
{
	int i;
	for (i = 0; m[i]; i++) {
		if (m[i]->exit_module == NULL)
			continue;
		else 
			m[i]->exit_module();
	}		
}


struct ata_module_s *find_module_by_kv(struct ata_keyval_s *kv, struct ata_module_s **m, int nr)
{
	int i = 0;
	while (i < nr) {
		if (strcmp((kv+i)->val, m[i]->name)) {
			return m[i];
		}
		i ++;
	}
	return NULL;
}


int module_flow_init(struct ata_conf_s *conf,
		     struct ata_module_s **m, int nr,
		     struct list_head *list)
{
	int i;
	struct ata_keyval_s *kv = conf->conf_keyval;	
	
	for (i = 0; i < PROCESS_STEPS; i++) {
		list_add(& find_module_by_kv(kv+i , m, nr)->flow_next, list);	
	}
	
	//list_add(m[nr], process_flow);
	
	return 0;
}

int start(struct ata_conf_s *conf, struct list_head *flow)
{
	int i;
	struct list_head *pos;
	struct ata_module_s *tmp;
	struct ata_module_s *head;
	
	//head = list_entry(flow->next, struct ata_module_s, flow_next);
	
	list_for_each_entry(tmp, flow->next, flow_next) {
		if (tmp->type == IMPORT) {
			(tmp->handle)(tmp->ctx, conf);
		}
	}
	
	list_for_each_entry(tmp, flow->next, flow_next) {
		if (tmp->type == FILTER) {
			(tmp->handle)(tmp->ctx, conf);
		}
	}
	
        list_for_each_entry(tmp, flow->next, flow_next) {
                if (tmp->type == ANALYSE) {
                        (tmp->handle)(tmp->ctx, conf);
                }
        }
	
	return 0;
}

int main(int argc, char *argv[])
{
	struct ata_command_s *commands;
	struct ata_log_s *log;
	struct ata_conf_s *conf;
	struct ata_module_flow_s *module_flow;
	int module_nr;
	LIST_HEAD(process_flow);

	/* INIT the conf */
	conf = ata_conf_init();	
	/* Read the conf file <default.conf> */
	//(conf->handle)(conf->ctx);
		
	//commands = ata_command_parse(conf);
	//log = ata_log_init(conf);	
	
	module_nr = ata_modules_init(ata_modules);
			
	module_flow_init(conf, ata_modules, module_nr, &process_flow);
	
	start(conf, &process_flow);

	ata_conf_clean(conf);

	//ata_log_clean();
	//ata_command_clean();
	ata_modules_clean(ata_modules);
}
