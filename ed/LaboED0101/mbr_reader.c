#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct ETP { // Entr ée Table des Partitions
    unsigned char bootable;
    uint chsStart :24;
    unsigned char type;
    uint chsEnd :24;
    int first;                 // LBA
    int sectors;               // LBA
} __attribute__((packed)) ETP; // é viter l ’ alignement des donn é es .

typedef struct MBR {
    unsigned char code[442];
    unsigned char signature[4];
    ETP TablePart[4];
    unsigned char bootable[2];
} __attribute__((packed)) MBR;

int main(int argc, char *argv[]) {
    int fd;
    unsigned char bootable;
    int chsStart = 0; 
    unsigned char type;
    int chsEnd = 0;
    int first, sectors;
    MBR struMBR;
    if (argc != 2){
        printf("usage : LectPart < pilote >\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        perror(argv[1]);
        exit(1);
    }

    printf("Partitions primaires de %s :\n", argv[1]);
    printf("===================================\n");
    read(fd, &struMBR, 512); // Lecture du premier secteur du disque
    for (int primaire = 1; primaire <= 4; primaire++)
    {
        bootable = struMBR.TablePart[primaire - 1].bootable;
        chsStart = struMBR.TablePart[primaire - 1].chsStart;
        type = struMBR.TablePart[primaire - 1].type;
        chsEnd = struMBR.TablePart[primaire - 1].chsEnd;
        first = struMBR.TablePart[primaire - 1].first;
        sectors = struMBR.TablePart[primaire - 1].sectors;
        
        if (first > 0){
            printf("Partition %d , bootable %d chs start 0x%x type %d chs end 0x%x début %d - fin %d (%d secteurs)\n", primaire, bootable, chsStart, type, chsEnd, first, first + sectors - 1, sectors);
        }    
    }
    close(fd);
    exit(0);
}

// 21 03 00 / 52 15 01
// 4c 11 0c / 14 0e 81
// 23 04 82 / 13 4a 18
// f2 35 93 / e7 ee fe