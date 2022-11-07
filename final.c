#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex;

//structure for arguments
typedef struct{
    int *arr;   //array
    int n;      //size of array
}arguments;

void printArray(arguments *arg){
    for(int i=0; i<arg->n; i++){
        printf("%d ", arg->arr[i]);
    }
    printf("\n");
}

void *bubble_asc(void *arg){
	arguments *array=(arguments*)arg;
    pthread_mutex_lock(&mutex);
    printf("\nBubble sort ascending:\n");
    printArray(array);
    sleep(1);
    // loop to access each array element
  for (int step = 0; step < array->n - 1; ++step) {
      
    // loop to compare array elements
    for (int i = 0; i < array->n - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array->arr[i] > array->arr[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array->arr[i];
        array->arr[i] = array->arr[i + 1];
        array->arr[i + 1] = temp;
        sleep(1);
        printArray(array);
      }
    }
  }
    pthread_mutex_unlock(&mutex);
}

void *bubble_dsc(void *arg){

 	arguments *array=(arguments*)arg;
    pthread_mutex_lock(&mutex);
    printf("\nBubble sort descending:\n");
    printArray(array);
    sleep(1);
    // loop to access each array element
  for (int step = 0; step < array->n - 1; ++step) {
      
    // loop to compare array elements
    for (int i = 0; i < array->n - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      if (array->arr[i] < array->arr[i + 1]) {
        
        // swapping occurs if elements
        // are not in the intended order
        int temp = array->arr[i];
        array->arr[i] = array->arr[i + 1];
        array->arr[i + 1] = temp;
        sleep(1);
        printArray(array);
      }
    }
  }
    pthread_mutex_unlock(&mutex);
}

//func to swap 2 variables
void swap(int *a, int *b) {
  int temp=*a;
  *a=*b;
  *b=temp;
}


//sorts array in ascending using insertion sort
void *insertion_asc(void *arg){

    pthread_mutex_lock(&mutex);
    printf("\nInsertion sort ascending:\n");
    arguments *a=(arguments*)arg;
    sleep(1);
    printArray(a);
    int i, key, j;
    for (i = 1; i < (a->n); i++) {
        key = a->arr[i];
        j = i - 1;
           /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && a->arr[j] > key) {
            a->arr[j + 1] = a->arr[j];
            j = j - 1;
        }
        a->arr[j + 1] = key;
        sleep(1);
        printArray(a);
    }
    pthread_mutex_unlock(&mutex);
}

//sorts array in descending using insertion sort
void *insertion_dsc(void *arg){

    pthread_mutex_lock(&mutex);
    printf("\nInsertion sort descending:\n");
    arguments *a=(arguments*)arg;
    sleep(1);
    printArray(a);

    int i, key, j;
    for (i = 1; i < (a->n); i++) {
        key = a->arr[i];
        j = i - 1;
           /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && a->arr[j] < key) {
            a->arr[j + 1] = a->arr[j];
            j = j - 1;
        }
        a->arr[j + 1] = key;
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

//sorts array in ascending using selection sort
void *sel_asc(void *arg){

    pthread_mutex_lock(&mutex);
    printf("\nSelection sort ascending:\n");
    arguments *a=(arguments*)arg;
    sleep(1);
    printArray(a);

    for(int step=0; step<(a->n)-1; step++) {
        int min=step;
        for(int i=step+1; i<a->n; i++) {
            if (a->arr[i] < a->arr[min])
                min=i;
        }
    
        swap(&a->arr[min], &a->arr[step]);
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

//sorts array in descending using selection sort
void *sel_dsc(void *arg){

    pthread_mutex_lock(&mutex);
    printf("\nSelection sort descending:\n");
    arguments *a=(arguments*)arg;
    sleep(1);
    printArray(a);

    for(int step=0; step<(a->n)-1; step++) {
        int min=step;
        for(int i=step+1; i<a->n; i++) {
            if(a->arr[i] > a->arr[min])
                min=i;
        }

        swap(&a->arr[min], &a->arr[step]);
        sleep(1);
        printArray(a);
    }

    pthread_mutex_unlock(&mutex);
}

int main()
{
	int ch;
	while(1)
	{
		printf("\n1. Bubble\n2. Insertion\n3. Selection\n4. Exit\n\nEnter Choice\n");
		scanf("%d",&ch);
		if(ch==4)
		{
			printf("Exiting\n");
			break;
		}
		arguments arg;
		pthread_t thread[2];
		pthread_mutex_init(&mutex,0);

		printf("Number of elements: ");
		scanf("%d", &arg.n);

		arg.arr=(int*)malloc(arg.n*sizeof(int));

		printf("\nEnter the elements: \n");

		for(int i=0; i<arg.n; i++){
			printf("Element %d: ",i+1);
			scanf("%d", &arg.arr[i]);        
		}
		if(ch==1)
		{
			pthread_create(&thread[0],NULL,&bubble_asc,(void*)&arg);
			pthread_create(&thread[1],NULL,&bubble_dsc,(void*)&arg);
			pthread_join(thread[0],NULL);
			pthread_join(thread[1],NULL);    
			pthread_mutex_destroy(&mutex);
		}
		else if(ch==2)
		{
			pthread_create(&thread[0],NULL,&insertion_asc,(void*)&arg);
			pthread_create(&thread[1],NULL,&insertion_dsc,(void*)&arg);
			pthread_join(thread[0],NULL);
			pthread_join(thread[1],NULL);
			pthread_mutex_destroy(&mutex);
		}
		else if(ch==3)
		{
			pthread_create(&thread[0],NULL,&sel_asc,(void*)&arg);
			pthread_create(&thread[1],NULL,&sel_dsc,(void*)&arg);
			pthread_join(thread[0],NULL);
			pthread_join(thread[1],NULL);
			pthread_mutex_destroy(&mutex);
		}
		else
			printf("Invalid Choice\n");
	}
}