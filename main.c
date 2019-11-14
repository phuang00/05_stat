#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int main() {
  printf("\n\nPrinting Stats: \n\n\n");
  struct stat info;
  char file[] = "main.c";
  stat(file, &info);
  if (errno > 0){
    printf("%s\n", strerror(errno));
  }
  printf("File: %s\n", file);
  int sizeB = info.st_size;
  printf("File size: %dB\n", sizeB);
  int others = info.st_mode % 8;
  int group = (info.st_mode / 8) % 8;
  int user = (info.st_mode / 64) % 8;
  char *time = ctime(&info.st_atime);
  time[strlen(time) - 1] = 0;
  printf("Mode: %o\n", info.st_mode);
  printf("Time of Last Access: %s\n", time);
  char buffer[50];
  double size = info.st_size;
  char *sizes[] = {"B", "KB", "MB", "GB"};
  int i = 0;
  while (size >= 1024){
    size = size / 1024.0;
    i++;
  }
  if (i == 0){
    sprintf(buffer, "%d%s", sizeB, sizes[i]);
  }
  else{
    sprintf(buffer, "%0.2lf%s", size, sizes[i]);
  }
  printf("\n\nFile size in human readable form: %s\n", buffer);
  char permissions[8][4] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
  printf("Permissions in ls -l format: %s%s%s\n\n\n", permissions[user], permissions[group], permissions[others]);

  return 0;
}
