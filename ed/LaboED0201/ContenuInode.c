/*
NOM    	: ContenuInode.c
CLASSE 	: FS - LaboFS 02-01
#OBJET  : réservé au makefile
AUTEUR	: J.C. Jaumain, 07/2011 revu mba 1/2015
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

void detail(struct stat inode){
	printf("Numéro d'inode : %d\n", (int)inode.st_ino);
	printf("Nombre de liens hardware : %d\n", (int)inode.st_nlink);
	printf("Propriétaire du fichier : %d\n", (int)inode.st_uid);
	printf("Groupe du propriétaire du fichier : %d\n", (int)inode.st_gid);
	printf("Taille (en bytes) : %d\n", (int)inode.st_size);
	printf("Nombre de blocs (en secteurs) : %d\n", (int)inode.st_blocks);
}

int main(int argc, char *argv[]){
	int r;
	struct stat inode;
	if (argc != 2){
		printf("Vous devez donner un nom de fichier \n");
		exit(1);
	}
	r = lstat(argv[1], &inode);
	if (r < 0){
		perror(argv[1]);
		exit(1);
	}

	if(S_ISREG(inode.st_mode)){
		printf("Le fichier %s est un fichier régulier\n", argv[1]);
		detail(inode);
	}else if (S_ISLNK(inode.st_mode)){
		printf("Le fichier %s est un lien software)\n", argv[1]);
		detail(inode);
	} else{
		printf("Le fichier %s n'est pas un fichier régulier)\n", argv[1]);
		exit(1);
	}
	exit(0);
}
