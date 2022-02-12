#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h> // pout PRIu64
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// le mbr du disque ( LBA0 )
typedef struct
{
    char data[512];
} __attribute__((packed)) mbr_t;

// l ’ entete GPT du disque ( LBA1 ou LBA -1)
typedef struct
{
    char filler1[32];
    uint64_t autreGPT_lba; // adresse de l ’ autre GPT
    char filler2[472];
} __attribute__((packed)) headerGpt_t;

// le type d ’ un guid id ou du type de la partition
typedef struct
{
    unsigned char guid[16];
} __attribute__((packed)) guid_t;

typedef struct
{
    guid_t type;        // type de la partition
    guid_t id;          // son id unique dans la table GPT
    uint64_t first_lba; // adresse du 1 er secteur
    uint64_t last_lba;  // adresse du dernier secteur
    char revision[8];   // espace reserv é
    char name[72];      // nom de la partition
} __attribute__((packed)) entryGpt_t;

void print72(char name[72])
{ // name est un tableau de 72 caratct è re
    printf(" name : ");
    for (int i = 0; i <72; i++)
        printf("% c", name[i]);
    printf("\n");
}
void printguid(guid_t guid)
{ // identifiant ou type
    printf(" guid : ");
    for (int car = 0; car <16; car++)
        printf("%1x ", guid.guid[car]);
    printf("\n");
}
void printEntry(entryGpt_t entry, int num)
{ // entry est un descripteur de partition
    printf("\n Entry %d\n ", num);
    printf(" ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----\n");
    // print72 ( entry . name );
    // printguid ( entry . id );
    // afficher des entiers non signés sur 64 bits
    // avec l ’ include inttypes.h
    printf(" first lba : %" PRIu64 " byte ( s) , last lba %" PRIu64 " , size =% " PRIu64 " \n ",
           entry.first_lba, entry.last_lba, entry.last_lba - entry.first_lba + 1);
}
void LireAfficherEntry(int fd, int num)
{
    entryGpt_t entry;
    read(fd, &entry, sizeof(entryGpt_t));
    if(entry.first_lba != 0)
    {
        // 0 signifie inutilis é
        printEntry(entry, num);
    }
}
int main(int argc, char *argv[])
{
    int fd;
    int i;
    headerGpt_t headerGPT;
    uint64_t position;
    if(argc <2)
    {
        printf(" usage %s <chemin device> ", argv[0]);
        exit(2);
    }
    fd = open(argv[1], O_RDONLY);
    if(fd <0)
    {
        printf(" device impossible à lire ou inexistant \n");
        exit(1); // pas le bon peripherique ou pas les droits
    }
    // lecture de LBA -1 : ent ê te secondaire de la GPT
    position = lseek(fd, -(1 * 512), SEEK_END); // revenir au secteur fin -1
    read(fd, &headerGPT, sizeof(headerGpt_t));
    printf(" Selon l’entête secondaire , l’entète primaire est au secteur % " PRIu64 " \n ", headerGPT.autreGPT_lba);
    // lecture de LBA1 : ent è te primaire GPT
    lseek(fd, 512, SEEK_SET); // positionnement apr ès MBR
    read(fd, &headerGPT, sizeof(headerGpt_t));
    printf(" Selon l’entête primaire , l’entète secondaire est au secteur %" PRIu64 " \n", headerGPT.autreGPT_lba);
    // afficher les entr é es des partition pr é sentes
    for (i = 0; i <128; i++)
    { // 128 entr é es sur LBA3
        LireAfficherEntry(fd, i);
    }
    // afficher le descripteur secondaire de la partition1
    position = lseek(fd, -(33 * 512), SEEK_END); // revenir aux descripteurs
    printf("\n\n\nLe Entry 1 secondaire se trouve au byte %" PRIu64 " \n ", position);
    // lire l ’ entr ée 1 en LBA -33
    LireAfficherEntry(fd, -1);
    close(fd);
    return 0;
}