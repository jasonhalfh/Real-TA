#include <ata_core.h>
#include <ata_conf_file.h>

#include "ata_conf_module.h"

int conf_handle(struct ata_module_ctx *ctx, struct ata_conf_s *conf)
{
	
}


int init_module()
{}

int exit_module()
{}

struct ata_module_s ata_conf_module = {
	.name = "conf",
	.type = 0,
	.version = 0,
	.handle = conf_handle,
	.init_module = init_module,
	.exit_module = exit_module,
};


