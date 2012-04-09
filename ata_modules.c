#include <ata_core.h>
#include <ata_conf_file.h>


extern struct ata_module_s ata_log_module;
extern struct ata_module_s ata_conf_module;

extern struct ata_module_s ata_pre_gps_module;


extern struct ata_module_s ata_filter_gpserr_module;

extern struct ata_module_s ata_analyse_conncluster_module;


struct ata_module_s *ata_modules[] = {
	&ata_log_module,
	&ata_conf_module,


	&ata_pre_gps_module,

	&ata_filter_gpserr_module,

	&ata_analyse_conncluster_module,


	NULL,
};
