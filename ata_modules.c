
#include <ata_core.h>
#include <ata_conf_file.h>


extern struct ata_module_s ata_log_module;
extern struct ata_module_s ata_conf_module;

extern struct ata_module_s ata_import_cab_module;


extern struct ata_module_s ata_filter_gpserr_module;

extern struct ata_module_s ata_analyse_conncluster_module;


struct ata_module_s *ata_modules[] = {
	&ata_log_module,   // not now
	&ata_conf_module,

	/* uniq for every dataset */
	&ata_import_cab_module,

	&ata_filter_gpserr_module,

	&ata_analyse_conncluster_module,


	NULL,
};
