objs=ata.c  ata_modules.c ata_conf_module.c ata_log_module.c \
	./modules/import/ata_import_cab_module.c \
	./modules/filter/ata_filter_gpserr_module.c \
	./modules/analyse/ata_analyse_conncluster_module.c


#m-objs=./modules/...
m-objs=

target: ata-bin
ata-bin: ${objs}
	gcc -g ${objs} -o ata-bin  -I./include -I/usr/src/kernels/2.6.32-71.el6.i686/include/ -lm

#ata-bin: 
#	gcc -g  ata.c  -o ata-bin -I./include -I/usr/src/kernels/2.6.32-71.el6.i686/include/ -lm







clean:
	rm -f *.o
	rm -f ./modules/*.o
	rm -f ata-bin

