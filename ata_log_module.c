#include <ata_core.h>
#include <ata_conf_file.h>

#include "ata_log_module.h"


struct ata_module_s ata_log_module = {
	.name = "log",
        .type = 0,
        .version = 0,
        .commands = NULL,
        .ctx = NULL,
        .handle = NULL,
        .init_module = NULL,
        .exit_module = NULL,
};



