#include <ata_keyval.h>

char *find_val_by_key(struct ata_keyval_s *kv, unsigned int key, unsigned int size)
{
	int i;
	
	i = 0;
	while (i < size) {
		if ((kv+i)->key == key) {
			return (kv+i)->val;
		}
		i ++;
	}
	return NULL;
}
