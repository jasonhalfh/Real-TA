objs=ata.o 
#m-objs=./modules/...
m-objs=

target: ata-bin
ata-bin: 
	gcc -g  ata.c  -o ata-bin -I./include -lm







clean:
	rm -f *.o
	rm -f ./modules/*.o
	rm -f ata-bin

