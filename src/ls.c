#include "headers.h"
#include "ls.h"

void sort_list(int count, char **list)
{
  char temp[MAX_SIZE];
  for(int i=0; i<count; i++){
    for(int j=0; j<count-1-i; j++){
      if(strcasecmp(list[j], list[j+1]) > 0){
        strcpy(temp, list[j]);
        strcpy(list[j], list[j+1]);
        strcpy(list[j+1], temp);
      }
    }
  }
}
void display_dir(char *path, bool flagA, bool flagL, struct stat buf){

    char **list = (char**)(malloc(MAX_SIZE*(sizeof(char*))));
    int idx=0;

    struct dirent *d;
    char temp[MAX_SIZE];

    DIR *dh = opendir(path);
    DIR *dh2 = opendir(path);
    if (!dh)
    {
        fprintf(stderr, "ls: Can't open directory.\n");
        return;
    }

    long total = 0;

    while ((d = readdir(dh)) != NULL) 
    {
        if (flagA == 0 && d->d_name[0] == '.')
        {
            continue;
        }
        list[idx] = (char*)malloc(sizeof(char) * MAX_SIZE);
        char *temp2 = (char*)malloc(sizeof(char) * MAX_SIZE);
        strcpy(temp2, path);
        strcat(temp2, "/");
        strcat(temp2, d->d_name);
        stat(temp2, &buf);
        total += buf.st_blocks;

        strcpy(list[idx],  d->d_name);
        idx++;

        free(temp2);
    }

    if(flagL)
        printf("total %ld\n", total / 2);

    sort_list(idx, list);

    for(int j = 0; j< idx; j++)
    {
        char *temp2 = (char*)malloc(sizeof(char) * MAX_SIZE);

        strcpy(temp2, path);
        strcat(temp2, "/");
        strcat(temp2, list[j]);
        printf("\033[0m");
        stat(temp2, &buf);

        if(S_ISDIR(buf.st_mode)){
            printf("\033[0;34m");
        }
        else if(buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP || buf.st_mode & S_IXOTH )
            printf("\033[0;33m");
        else if(S_ISREG(buf.st_mode)) 
        {
            printf("\033[0;37m");
        }


        if (flagL)
        {

            struct passwd *pw = getpwuid(buf.st_uid);
            struct group *gid = getgrgid(buf.st_gid);


            char datetime[MAX_SIZE];

            if(S_ISDIR(buf.st_mode)){
                printf("d");

            }
            else if(S_ISREG(buf.st_mode)) 
            {
                printf("-");
            }

            printf((buf.st_mode & S_IRUSR) ? "r" : "-");
            printf((buf.st_mode & S_IWUSR) ? "w" : "-");
            printf((buf.st_mode & S_IXUSR) ? "x" : "-");
            printf((buf.st_mode & S_IRGRP) ? "r" : "-");
            printf((buf.st_mode & S_IWGRP) ? "w" : "-");
            printf((buf.st_mode & S_IXGRP) ? "x" : "-");
            printf((buf.st_mode & S_IROTH) ? "r" : "-");
            printf((buf.st_mode & S_IWOTH) ? "w" : "-");
            printf((buf.st_mode & S_IXOTH) ? "x " : "- ");

            printf("%ld ", buf.st_nlink);

            if(pw == NULL) {
                fprintf(stderr,"ls: getpwuid error\n");
                printf("%d ", buf.st_uid);
            }
            else {
                printf("%s ", pw->pw_name);
            }


            if(gid == NULL) {
                fprintf(stderr,"ls: getgrgid error\n");
                printf("%d ", buf.st_gid);
            }
            else  {
                printf("%s ", gid->gr_name);
            }

            printf("%5.ld ", buf.st_size);
            strftime(datetime, 14, "%b %d %H:%M", localtime(&(buf.st_mtime)));
            printf("%s ", datetime);
        }

        printf("%s  ", list[j]);
        if (flagL)
            printf("\n");

        free(temp2);
    }
    if (flagL == 0)
    {
        printf("\n");
    }

    printf("\033[0m");

    for(int j = 0; j<idx;j++)
        free(list[j]);
    free(list);

}

void display_file(char *path, bool flag_l, struct stat buf){
    printf("\033[0;37m");

    if (flag_l)
    {
        char datetime[MAX_SIZE];
            printf("-");
            printf((buf.st_mode & S_IRUSR) ? "r" : "-");
            printf((buf.st_mode & S_IWUSR) ? "w" : "-");
            printf((buf.st_mode & S_IXUSR) ? "x" : "-");
            printf((buf.st_mode & S_IRGRP) ? "r" : "-");
            printf((buf.st_mode & S_IWGRP) ? "w" : "-");
            printf((buf.st_mode & S_IXGRP) ? "x" : "-");
            printf((buf.st_mode & S_IROTH) ? "r" : "-");
            printf((buf.st_mode & S_IWOTH) ? "w" : "-");
            printf((buf.st_mode & S_IXOTH) ? "x " : "- ");

        printf("%ld ", buf.st_nlink);
        printf("%s ", getpwuid(buf.st_uid)->pw_name);
        printf("%s ", getgrgid(buf.st_gid)->gr_name);
        printf("%5.ld ", buf.st_size);
        strftime(datetime, 14, "%b %d %H:%M", localtime(&(buf.st_mtime)));
        printf("%s ", datetime);
    }
    printf("%s  ", path);
    printf("\n");
    printf("\033[0m");

}



void ls_cmd(int argc, char **arg_list){

    bool flag_l = false;
    bool flag_a = false;
    int num = 0;

    char pathsArray[MAX_SIZE][MAX_SIZE];
    char *curPath = getcwd(NULL,0);

    strcpy(pathsArray[0], curPath);

    for(int i = 1; i<argc; i++){
        char *token = arg_list[i];

        if (token[0] == '-')
        {
            for (int i = 1; i < strlen(token); i++)
            {
                if (token[i] == 'l')
                {
                    flag_l = true;
                }
                else if (token[i] == 'a')
                {
                    flag_a = true;
                }
            }
        }
        else if (strcmp(token, "~") == 0)
        {
            strcpy(pathsArray[num],home);
            num++;
        }
        // replace ~ with home directory
        else if (token[0] == '~')
        {
            char *temp = (char*)malloc(sizeof(char) * MAX_SIZE);
            strcpy(temp, token);
            strcpy(token, home);
            strcat(token, temp+1);
            free(temp);

            strcpy(pathsArray[num], token);

        }
        else
        {
            strcpy(pathsArray[num], token);
            num++;
        }
    }

    // if only 'ls' is inputted
    if(num == 0){
        num = 1;
        struct stat buf;
        int r = stat(".", &buf);
        if (r == -1)
        {
            fprintf(stderr, "ls: Error\n");
        }
        display_dir(".", flag_a, flag_l, buf);
        return;
    }

    for (int i = 0; i < num; i++)
    {

        struct stat buf;
        int r = stat(pathsArray[i], &buf);
        if (r == -1)
        {
            fprintf(stderr, "ls: No such file or directory\n");
        }
        else
        {
            if (S_ISDIR(buf.st_mode))
            {
                if(num>1)
                    printf("%s:\n", pathsArray[i]);

                if(strcmp(pathsArray[i],"~") == 0)
                    display_dir(home, flag_a, flag_l, buf);
                else
                    display_dir(pathsArray[i], flag_a, flag_l, buf);

            }
            else    
            {
              display_file(pathsArray[i],flag_l,buf); 
            }
        }

        if (i < num - 1)
        {
            printf("\n");
        }  
    }
    return;
}