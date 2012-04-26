#include <ata_core.h>
#include <ata_conf_file.h>

#include "ata_import_cab_module.h"

/*
 *  For GPS data handle
 *  [lat : lng : c : time]
 */
void gps_to_loc(double lat, double lng, double ox, double oy,
		double *x, double *y)
{
	double tmp_x = (double)(A * A);
	tmp_x /= sqrt(tmp_x + B * B * pow((sin(lat * PI / 180) / cos(lat * PI / 180)), 2));
	
	double tmp_y = (double)(B * B);
	tmp_y /= sqrt(tmp_y + A * A * pow((cos(lat * PI / 180) / sin(lat * PI / 180)), 2));
	
	if(ox == 0 && oy == 0) {
		*x = tmp_x;
		*y = tmp_y;
	} else {
		*x = sqrt((tmp_x - ox) * (tmp_x - ox) + (tmp_y - oy) * (tmp_y - oy));
		*y = ox * (lng - OLNG) * PI /180 ;
	}
}


void read_cabfile(struct ata_standitem_s *items, char *file, double ox, double oy, unsigned int nid)
{
	FILE *fp;
	double lng, lat, time;
	int flag;
	int i;
	struct ata_standitem_s *tmp = items;

	fp = fopen(file, "r");
	//IS_PTR_ERR(fp, "Open file err\n");
	
	i = 0;
	while (fscanf(fp, "%lf\t%lf\t%d\t%lf\n", 
		      &lat, &lng, &flag, &time) != EOF) {
		tmp->nid = nid;
		tmp->time = time;
		gps_to_loc(lat, lng, ox, oy, &(tmp->x), &(tmp->y));
		tmp ++;
		i ++;
	}
	fclose(fp);
}

int files_in_dir(char *path)
{
	int cnt;
	DIR *dp;
	struct dirent *file;
	
	dp = opendir(path);
        if(!dp) {
                printf("open dir error in density_in_area\n");		
	}
	cnt = 0;
	while(file = readdir(dp)) {
		if(file->d_type != 8) { // not a normal file
			continue;
		}
		
		cnt ++;
	}

	closedir(dp);
	
	return cnt;
}


void get_snapshot(struct ata_standitem_s *snapshot,struct ata_standitem_s *tracks, struct ata_conf_s *conf)
{
	unsigned int start = conf->snapshot_start;
	unsigned int time = conf->snapshot_time;
	unsigned int peroid = conf->snapshot_peroid;
	
	
}

int import_cab(struct ata_module_ctx *ctx)
{
	DIR *dp;
	struct dirent *file;
	struct ata_conf_s *conf = ctx->gconf;
	int i;
	char *indir = find_val_by_key(conf->conf_keyval, INDIR, conf->conf_nr);
	char *outdir = find_val_by_key(conf->conf_keyval, OUTDIR, conf->conf_nr);
	char infile[256];
	char outfile[256];
	struct ata_standitem_S **tracks, **snapshot;
	
	double ox, oy;
	gps_to_loc(OLAT, OLNG, 0, 0, &ox, &oy);
	
	conf->node_nr = files_in_dir(indir);
		
	tracks = (struct ata_standitem_s **)
		malloc(sizeof(struct ata_standitem_s*) * conf->node_nr);
	//IS_PTR_ERR(tracks, "Malloc tracks err\n");
	
	i = 0;
	while (i < conf->node_nr) {
		*(tracks + i) = (struct ata_standitem_s*)
			malloc(sizeof(struct ata_standitem_s) * MAX_ITEMS);
		//IS_PTR_ERR(*(tracks+i), "malloc track + i failed\n");
	}
		
	/* Read data from indir */
	dp = opendir(indir);
        if(!dp) {
                printf("open dir error in density_in_area\n");
		dp = opendir(indir);
	}
	i = 0;
	while(file = readdir(dp)) {
		if(file->d_type != 8) { // not a normal file
			continue;
		}
		memset(infile, 0, sizeof(infile));
		memset(outfile, 0, sizeof(outfile));
		strcat(infile, indir);
		strcat(infile, file->d_name);
		strcat(outfile, outdir);
		strcat(outfile, file->d_name);
		memset(*(tracks + i), 0, sizeof(struct ata_standitem_s) * MAX_ITEMS);
		
		read_cabfile(*(tracks+i), infile, ox, oy, i);
		i ++;
	}
	closedir(dp);
	
	snapshot_nr = conf->snapshot_time / conf->snapshot_peroid ;
	snapshot = (struct ata_standitem_s **)malloc(sizeof(struct ata_standitem_s*) * snapshot_nr);
	
	i = 0;
	while (i < snapshot_nr) {
		*(snapshot + i) = (struct ata_standitem_s *)malloc(sizeof(struct ata_standitem_s) * conf->node_nr);
		i++;
	}
	
	get_snapshot(snapshot, tracks);
	
	conf->tracks = tracks;
	conf->snapshot = snapshot;
}



int init()
{

}


int exit()
{

}


struct ata_module_s ata_import_cab_module = {
	.name = "cab",
        .type = IMPORT,
        .version = 0.1,
	.handle = import_cab,
        .init_module = init,
        .exit_module = exit,
};


