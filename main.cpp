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

	for (int tasks = 1; tasks <= 20; tasks++){
		clock_gettime(CLOCK_MONOTONIC, &start);
		crack_ispc(arr, len, false, tasks);
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		cout << "tasks " << tasks << ":\t" << elapsed << " secs";
	}

	return 0;
}