#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int main() {
  struct stat info;
  char file[20] = "main.c";
  stat(file, &info);
  if (errno > 0){
    printf("%s\n", strerror(errno));
  }
  printf("File: %s\n", file);
  printf("File size: %lldB\n", info.st_size);
  int others = info.st_mode % 8;
  int group = (info.st_mode / 8) % 8;
  int user = (info.st_mode / 64) % 8;
  char *time = ctime(&info.st_atime);
  time[strlen(time) - 1] = 0;
  printf("Mode: %d%d%d\n", user, group, others);
  printf("Time of Last Access: %s\n", time);

  printf("\n");
  char buffer[50];
  int n = sprintf(buffer, "%lldB, %lfKB, %lfMB, %lfGB", info.st_size, (info.st_size / 1000.0), (info.st_size / 1000000.0), (info.st_size / 1000000000.0));
  printf("File size in B, KB, MB, GB: %s\n", buffer);
  printf("\n");
  char permissions[8][4] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
  printf("%s%s%s\t%u\t%u\t%lld\t%s\t%s\n", permissions[user], permissions[group], permissions[others], info.st_uid, info.st_gid, info.st_size, time, file);

  return 0;
}
