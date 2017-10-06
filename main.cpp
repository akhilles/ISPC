#include <string>
#include <iostream>
#include <ctime>
#include "md5.h"
#include "md5_ispc.h"

using namespace std;

int main(int argc, char *argv[]) {
	clock_t start;
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
	
	//start = clock();
	//crack_serial(arr, len);
	//std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	
	start = clock();
	crack_ispc(arr, len);
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;

	return 0;
}