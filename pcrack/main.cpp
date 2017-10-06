#include <string>
#include <iostream>
#include "md5.h"
#include "md5_ispc.h"

using namespace std;

int main(int argc, char *argv[]) {
	string password = argv[1];
	int len = password.length();
	uint8_t arr[4];

	for (int i = 0; i < password.length(); i++){
		arr[i] = password[i];
	}
	
	//crack_serial(arr);
	crack_ispc(arr);

	return 0;
}