#ifndef _ata_analyse_conncluster_module_h_ 
#define _ata_analyse_conncluster_module_h_ 1


struct cluster_head {
	unsigned int cid;
	int node_cnt;
	struct ata_standitem_s *n;
};

extern struct ata_module_s ata_analyse_conncluster_module;

#endif
