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

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (int iter = 0; iter < 5; iter++){
		crack_ispc(arr, len, false, 16);
	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << elapsed << " secs" << endl;

	return 0;
}