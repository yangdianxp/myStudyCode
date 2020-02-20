#include <stdint.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;
int num = 0;

void* func(void* arg)
{
	pthread_mutex_lock(&lock);
	printf("wait do something....\n");
	pthread_cond_wait(&cond, &lock);
	pthread_mutex_unlock(&lock);

	printf("hello, world\n");

}



int main()
{
	pthread_t ps;
	//初始化
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	
	//修改全局变量值，使func线程解除阻塞等待
	pthread_mutex_lock(&lock);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);

	//创建线程
	pthread_create(&ps, NULL, func, NULL);

	pthread_mutex_lock(&lock);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);

	while (true)
	{
		sleep(2);
	}

	return 0;
}

