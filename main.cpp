#include <string>
#include <iostream>
#include <time.h>
#include "md5.h"
#include "md5_ispc.h"

using namespace std;

int main(int argc, char *argv[]) {
	struct timespec start, finish;
	double elapsed;
	uint8_t arr[8];

	string password = argv[1];
	int len = password.length();

	for (int i = 0; i < 8; i++){
		if (i >= len){
			arr[i] = 0;
		} else {
			arr[i] = password[i];
		}
	}
	
    // Serial
    clock_gettime(CLOCK_MONOTONIC, &start);
    crack_ispc(arr, len, true, 0);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout  << " Sequential Implementation.";
    cout <<"Time elapsed "<< elapsed << " secs" << endl;
    
    // ISPC with 0 task
    clock_gettime(CLOCK_MONOTONIC, &start);
    crack_ispc(arr, len, false, 0);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "ISPC implementation with no task.";
    cout <<"Time elapsed "<< elapsed << " secs" << endl;
    // ISPC with 1 task
	clock_gettime(CLOCK_MONOTONIC, &start);
	crack_ispc(arr, len, false, 1);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "1" << " tasks are implemented.";
	cout << elapsed << " secs" << endl;
    
    // ISPC with 10 tasks
    clock_gettime(CLOCK_MONOTONIC, &start);
    crack_ispc(arr, len, false, 10);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "10" << " tasks are implemented.";
    cout << elapsed << " secs" << endl;
    // ISPC with 100 tasks
    clock_gettime(CLOCK_MONOTONIC, &start);
    crack_ispc(arr, len, false, 100);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "100" << " tasks are implemented.";
    cout << elapsed << " secs" << endl;
    // ISPC with 1000 task
    clock_gettime(CLOCK_MONOTONIC, &start);
    crack_ispc(arr, len, false, 1000);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "1000" << " tasks are implemented.";
    cout << elapsed << " secs" << endl;
    
	return 0;
}
