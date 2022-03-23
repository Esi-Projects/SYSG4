#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


void displayDirAndChildren(char filename[]){
    struct dirent *entry;

    DIR *dirp;
    dirp = opendir(filename);

    struct stat inode;
    while ((entry = readdir(dirp)) != NULL){       
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            printf("%8d - %s\n", (int)entry->d_ino, entry->d_name);
                
            int stat_res;
            stat_res = stat(entry->d_name, &inode);
            if (stat_res == -1) {
                perror("Error during stat");
            }
            
            if (S_ISDIR(inode.st_mode)) {
                struct dirent *childEntry;
                DIR *childDirp;
                childDirp = opendir(entry->d_name);
                while ((childEntry = readdir(childDirp)) != NULL){   
                    if(strcmp(childEntry->d_name, ".") != 0 && strcmp(childEntry->d_name, "..") != 0){    
                        printf("%8d - %s\n", (int)childEntry->d_ino, childEntry->d_name); 
                    }
                }
                closedir(childDirp);
            }
        }
    }
    closedir(dirp);
}

int main()
{
    displayDirAndChildren(".");
}