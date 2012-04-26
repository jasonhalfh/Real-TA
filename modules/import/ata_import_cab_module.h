#ifndef _ATA_IMPORT_CAB_MODULE_H_
#define _ATA_IMPORT_CAB_MODULE_H_ 1

#include <ata_keyval.h>

/* 
 * some gps data info
 */
/* some info used for GPS format */
#define A 6378136.49
#define B 6356755.00
#define OLAT 37.77328   // first item in [new_ictmuog.txt]
#define OLNG -122.40836  // chose by random
#define PI 3.1415926535897932


#define MAX_ITEMS 5000

typedef struct {
	double lng;
	double lat;
	unsigned int nid;
	double time;
}gps_data;


extern struct ata_module_s ata_import_cab_module ;


#endif
