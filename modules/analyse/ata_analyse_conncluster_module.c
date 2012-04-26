#include <ata_core.h>
#include <ata_conf_file.h>

#include "ata_analyse_conncluster_module.h"

doublet get_distance(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 -x2) * (x1 - x2) + (y1 - y2) * (y1 -y2));
}



void conn_cluster_handle(struct cluster_head *chead, struct ata_standitem_s **tracks,
			 char *infofile)
{
	int i;
	
}

int conn_cluster(struct ata_module_ctx *ctx)
{
	struct ata_conf_s *conf = ctx->gconf;
	struct ata_standitem_s **tracks = conf->tracks;
	struct cluster_head *chead = 
		(struct cluster_head*)malloc(MAX_NODE_NUM * sizeof(struct cluster_head));
	if (chead == NULL) {
		printf("malloc for struct cluster_head failed\n");
		return 0;
	}
	
	//cluster_handle(chead, tracks, indir, outdir, infofile, flag);

	free(chead);
	return 0;
}


int init()
{}

int exit()
{}



struct ata_module_s ata_analyse_conncluster_module = {
	.name = "connCluster",
        .type = ANALYSE,
        .version = 0,
        .commands = NULL,
        .ctx = NULL,
        .handle = conn_cluster,
        .init_module = init,
        .exit_module = exit,
};



