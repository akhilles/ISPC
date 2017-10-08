#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <immintrin.h>
// Include the header file that the ispc compiler generates

#include "proj1ispc.h"

/*
void sravx( float * nums,  float * roots,  int size, int tasks){
float r1[8];
float r2[8];

float e=8.0f;
float z=2.0f;


__m256 eight=_mm256_broadcast_ss(&e);
__m256 two=_mm256_broadcast_ss(&z);
int mod=0;
if (size%8 != 0){
size=size-size%8;
mod =size%8;
}
int q;
for ( q=0; q<size; q+=8){
for (int i=0; i<8; i++){
 r1[i]=rand();
 r2[i]=rand();
}
__m256 x =_mm256_mul_ps( _mm256_div_ps(_mm256_min_ps(	_mm256_load_ps(r1),_mm256_load_ps(r2)),  _mm256_max_ps(	_mm256_load_ps(r1),_mm256_load_ps(r2))),eight);
__m256 root=_mm256_sqrt_ps(x);
__m256 est =x;
int flag =8;
float temp[8];
while (flag>0){

est=_mm256_sub_ps(est,_mm256_div_ps(_mm256_sub_ps(_mm256_mul_ps(est,est),x),_mm256_mul_ps(two,est)));

_mm256_store_ps(temp,_mm256_sub_ps(root,est));
int lflag=0;
for (int j=0; j<8; j++){

if (fabs(temp[j]) > .0001){
lflag=1;
}

}
if (lflag ==0){
flag=0;
}



}
_mm256_store_ps(&nums[q],x);
_mm256_store_ps(&roots[q],est);
}
if (mod >0){
   while (q<size+mod){
    double r1=rand();
	double r2=rand();
	double x=(fmin(r1,r2)/fmax(r1,r2))*8;
	
	double root=sqrt(x);
	nums[q]=x;
	double est=x;
	while ( fabs(root-est)>.0001){
	
	   est=est-(est*est-x)/(2*est);
	   
	
	}
	roots[q]=est;
	q=q+1;
	}
}

}
struct data{
float * nums;
float * roots;
int size;
int tasks;
};

void TaskFuncX(void *data, int threadIndex, int threadCount,
                    int taskIndex, int taskCount,
                    int taskIndex0, int taskIndex1, int taskIndex2,
                    int taskCount0, int taskCount1, int taskCount2)
{
					struct data *  dat= (struct data *) data;
					int chunk = (*dat).size/taskCount;
					if (taskIndex+1< taskCount)
					{sravx((*dat).nums+taskIndex*chunk, (*dat).roots+taskIndex*chunk, chunk, taskCount);
					}else{
					  sravx((*dat).nums+taskIndex*chunk, (*dat).roots+taskIndex*chunk, (*dat).size-taskIndex*chunk, taskCount);
			        }
					
}



void sravxtasks (float  * nums, float * roots, int size, int tasks){


struct data  * dat = (struct data * ) malloc(sizeof(struct data));
(*dat).nums=nums;
(*dat).roots=roots;
(*dat).size=size;
(*dat).tasks=tasks;
void * handel;
//ISPCLaunch(&handel, (void *) TaskFuncX, dat, tasks, 0, 0);
//ISPCSync(handel);
}

*/



int main() {
    //Serial implementation to find one root
	/*srand(time(0));

	
    double r1=rand();
	double r2=rand();
	double x=(fmin(r1,r2)/fmax(r1,r2))*8;
	
	double root=sqrt(x);
	printf("sqrt %f ",x);
	double est=x;
	while ( fabs(root-est)>.0001){
	
	   est=est-(est*est-x)/(2*est);
	   printf("error =%f",est-root);
	
	}
	printf("root %f est %f", root, est);*/
	
	
	int size=20000000;
	float * nums=(float *) malloc(sizeof(float)*size);
	if (nums == NULL){
	printf("malloc error");
	return 0;}
	
	float  * roots=(float *) malloc(sizeof(float)*size);
	if (roots == NULL){
	printf("malloc error");
	return 0;}

	//Serial implementation to find all roots
	float starttime = clock();
	srand(time(0));

	for (int i=0; i<20000000; i++){
	
    float r1=rand();
	float r2=rand();
	float x=(fmin(r1,r2)/fmax(r1,r2))*8;

	
	float root=sqrt(x);
	nums[i]=x;
	float est=x;
	while ( abs(root-est)>.0001){
	
	   est=est-(est*est-x)/(2*est);
	
	}
	roots[i]=est;
	}
	float endtime = clock();
	printf("roots %f num %f ",roots[19999999],nums[19999999]);
	float elapsedtime = endtime - starttime;
	printf("elapsed time with sequential execution: %f seconds \n ",((float) elapsedtime)/CLOCKS_PER_SEC);
	
	//call sr function for plain ispc 
	//call sroot for tasks
	starttime = clock();
	sr(nums,roots, size);
	endtime = clock();
	printf("roots %f num %f ",roots[19999999],nums[19999999]);
	elapsedtime = endtime - starttime;
	printf("elapsed time with ISPC: %f seconds \n ",((float) elapsedtime)/CLOCKS_PER_SEC);
	

	for (int tsk = 1; tsk<300000; tsk=tsk*2){
	starttime = clock();
	sroot(nums, roots, size,tsk);
	// printf("num %f",roots[90]);
	//sravx(nums, roots, size, 4);
	//sravxtasks(nums, roots, size, 4);
	roots[1999];
	nums[1999];
	endtime = clock();
	printf("roots %f num %f ",roots[19999999],nums[19999999]);
	elapsedtime = endtime - starttime;
    printf("elapsed time with ISPC and %d task(s): %f milliseconds \n ",tsk,((float) elapsedtime*1000)/CLOCKS_PER_SEC);

	}
	
    return 0;
}

