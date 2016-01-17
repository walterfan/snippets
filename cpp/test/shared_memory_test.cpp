/* This program locks the virtual memory address that */
/* was returned from the mmap() function into memory. */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int fd;
	caddr_t pg_addr;

int size = 5000;
int mode =  S_IRWXO|S_IRWXG|S_IRWXU;

     /* Create a file */

fd = shm_open("example", O_RDWR|O_CREAT, mode);
if(fd < 0){
   perror("open error ");
   exit();
}

     /* Set the size */

if((ftruncate(fd, size)) == -1){
     perror("ftruncate failure");
     exit();
}

     /* Map the file into the address space of the process */
pg_addr = (caddr_t) mmap(0, size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED,
                         fd, 0);

if(pg_addr == (caddr_t) -1){
  perror("mmap failure");
  exit();
}

     /* Lock the mapped region into memory */

if(mlock(pg_addr,size) != 0){
  perror("mlock failure");
  exit();
}

     /* Unmap of the address region removes the memory lock */
     /* established on the address region by this process   */

if(munmap(pg_addr, size) < 0)
   perror("unmap error");
close(fd);
shm_unlink("example");
exit();
}

