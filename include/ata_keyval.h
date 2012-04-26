#ifndef _ata_keyval_h_
#define _ata_keyval_h_ 1

#include <ata_core.h>
#include <ata_conf_file.h>

char *find_val_by_key(struct ata_keyval_s *kv, unsigned int key, 
		      unsigned int size);


#endif
