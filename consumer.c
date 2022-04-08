// Consumer
// Nicholas Whitman
// 7 April 2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

int main()
{
	const char * name = "shared memory";
	const char * semaphore1 = "fill";
	const char * semaphore2 = "use";
	const char * semaphore3 = "mutex";
	
	int shmFD;
	int * shelf;
	int loop=10;
	
	sem_t * fill, * use, * mutex;

	//shared memory
	shmFD = shm_open(name, O_RDWR, 0666);

	shelf = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmFD, 0);
	
	fill = sem_open(semaphore1, O_CREAT, 0666, 0);
	use = sem_open(semaphore2, O_CREAT, 0666, 3);
	mutex = sem_open(semaphore3, O_CREAT, 0666, 1);

	while(loop--)
	{
		sem_wait(fill);
		sleep(rand()%2+1);
		sem_wait(mutex);
		(* shelf)--;
		sem_post(mutex);
		printf("Consumed an item. \n");
		sem_post(use);
	}

	sem_close(fill);
	sem_close(use);
	sem_close(mutex);
	sem_unlink(semaphore1);
	sem_unlink(semaphore2);
	sem_unlink(semaphore3);

	munmap(shelf, sizeof(int));
	close(shmFD);
	shm_unlink(name);
	
	return 0;
}
