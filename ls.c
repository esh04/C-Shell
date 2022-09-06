#include "headers.h"

void display_dir(char *path, bool flagA, bool flagL, struct stat buf){

    if (flagL)
    {
        struct dirent *d;
        char temp[MAX_SIZE];

        DIR *dh = opendir(path);
        if (!dh)
        {
            fprintf(stderr, "ls: Can't open directory.\n");
            return;
        }

        long total = 0;
    
        // print total on top
        while ((d = readdir(dh)) != NULL) 
        {
            strcpy(temp, path);
            strcat(temp, "/");
            strcat(temp, d->d_name);
            stat(temp, &buf);
            total += buf.st_blocks;
        }
        
        printf("total %ld\n", total / 2);
    }
    
    struct dirent *d;
    char temp[MAX_SIZE];
    DIR *dh = opendir(path);
    if (!dh)
    {
        fprintf(stderr, "ls: Can't open directory.\n");
        return;
    }


    while ((d = readdir(dh)) != NULL)
    {

        if(S_ISDIR(buf.st_mode)){
            printf("\033[0;34m");
        }
        else if(S_ISREG(buf.st_mode)) 
        {
            printf("\033[0;37m");
        }
        else if(S_IXUSR & buf.st_mode)
            printf("\033[0;33m");

        if (flagA == 0 && d->d_name[0] == '.')
        {
            continue;
        }
        if (flagL)
        {

            struct passwd *pw;
            struct group *gid;

            char datetime[MAX_SIZE];
            strcpy(temp, path);
            strcat(temp, "/");
            strcat(temp, d->d_name);
            stat(temp, &buf);
            stat(temp, &buf);

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

            fileperms(temp);
            printf("%ld ", buf.st_nlink);


            pw = getpwuid(buf.st_uid);
            if(pw == NULL) {
                perror("getpwuid");
                printf("%d ", buf.st_uid);
            }
            else {
                printf("%s ", pw->pw_name);
            }

            gid = getgrgid(buf.st_gid);

            if(gid == NULL) {
                perror("getgrgid");
                printf("%d ", buf.st_gid);
            }
            else  {
                printf("%s ", gid->gr_name);
            }

            printf("%5.ld ", buf.st_size);
            strftime(datetime, 14, "%b %d %H:%M", localtime(&(buf.st_mtime)));
            printf("%s ", datetime);
        }




        printf("%s  ", d->d_name);
        if (flagL)
            printf("\n");
    }
    if (flagL == 0)
    {
        printf("\n");
    }

    printf("\033[0m");


}

void display_file(char *path, bool flag_l, struct stat buf){
    printf("\033[0;37m");

    if (flag_l)
    {
        char datetime[MAX_SIZE];
        fileperms(path);
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

// void sort_list(int count, char **list){
//     for(int x=0;x<count;x++)
//     {
//         for(int y=0;y<count-1-x;y++)
//         {
//             if(strcmp(list[y],list[y+1])>0)
//             {
//                 // swap strings
//                 char *temp = NULL;
//                 temp=list[y];
//                 list[y]=list[y+1];
//                 list[y+1]=temp;
//             }
//         }
//     }    
// }

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
        int r = stat('.', &buf);
        if (r == -1)
        {
            fprintf(stderr, "ls: Error\n");
        }
        display_dir('.', flag_a, flag_l, buf);
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
                    print("%s:\n", pathsArray[i]);

                if(strcmp(pathsArray[i],'~'))
                    display_dir(home, flag_a, flag_l, buf);
                else
                    display_dir(pathsArray[i], flag_a, flag_l, buf);
           
                if (i < num - 1)
                {
                    printf("\n");
                }  
            
            }
            else    
            {
              display_file(pathsArray[i],flag_l,buf); 
            }
        }
    }
    return;
}