#include "md5.h"
#include "md5_ispc.h"
#include <iostream>

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

using namespace std;


// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

inline unsigned int F(unsigned int x, unsigned int y, unsigned int z) {
	return (x&y) | (~x&z);
}
   
inline unsigned int G(unsigned int x, unsigned int y, unsigned int z) {
	return (x&z) | (y&~z);
}
   
inline unsigned int H(unsigned int x, unsigned int y, unsigned int z) {
	return x^y^z;
}
   
inline unsigned int I(unsigned int x, unsigned int y, unsigned int z) {
	return y ^ (x | ~z);
}
   
  // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
  // Rotation is separate from addition to prevent recomputation.
inline void FF(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
	a = LEFTROTATE(a+ F(b,c,d) + x + ac, s) + b;
}
   
inline void GG(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
	a = LEFTROTATE(a + G(b,c,d) + x + ac, s) + b;
}
   
inline void HH(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
	a = LEFTROTATE(a + H(b,c,d) + x + ac, s) + b;
}
   
inline void II(unsigned int &a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s, unsigned int ac) {
	a = LEFTROTATE(a + I(b,c,d) + x + ac, s) + b;
}

static inline unsigned int to_int32(uint8_t *bytes)
{
    return (unsigned int) bytes[0]
        | ((unsigned int) bytes[1] << 8)
        | ((unsigned int) bytes[2] << 16)
        | ((unsigned int) bytes[3] << 24);
}

void md5(uint8_t initial_msg[8], int initial_len, unsigned int *h0, unsigned int *h1, unsigned int *h2, unsigned int *h3) {
	
	unsigned int a, b, c, d, i;

	unsigned int w[16];
	memset(w, 0, 64);

	cout << (int)initial_msg[0] << " " << (int)initial_msg[1] << " " << (int)initial_msg[2] << endl;

	if (initial_len == 2) {
		a = 0x800000 | (initial_msg[1] << 8) | (initial_msg[0]);
	} else if (initial_len == 3) {
		w[0] = 0x80000000 | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
	} else if (initial_len == 4) {
		w[0] = (initial_msg[3] << 24) | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
		w[1] = 0x80;
	} else if (initial_len == 5) {
		w[0] = (initial_msg[3] << 24) | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
		w[1] = 0x8000 | (initial_msg[4]);
	} else if (initial_len == 6) {
		w[0] = (initial_msg[3] << 24) | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
		w[1] = 0x800000 | (initial_msg[5] << 8) | (initial_msg[4]);
	} else if (initial_len == 7) {
		w[0] = (initial_msg[3] << 24) | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
		w[1] = 0x80000000 | (initial_msg[6] << 16) | (initial_msg[5] << 8) | (initial_msg[4]);
	} else if (initial_len == 8) {
		w[0] = (initial_msg[3] << 24) | (initial_msg[2] << 16) | (initial_msg[1] << 8) | (initial_msg[0]);
		w[1] = (initial_msg[7] << 24) | (initial_msg[6] << 16) | (initial_msg[5] << 8) | (initial_msg[4]);
		w[2] = 0x80;
	}

	w[14] = 8*initial_len;

	for (i = 0; i < 16; i++){
		cout << hex << w[i] << " ";
	}
	cout << endl;


	// Initialize hash value for this chunk:
	a = 0x67452301;
	b = 0xefcdab89;
	c = 0x98badcfe;
	d = 0x10325476;

	FF (a, b, c, d, w[ 0], S11, 0xd76aa478); /* 1 */
	FF (d, a, b, c, w[ 1], S12, 0xe8c7b756); /* 2 */
	FF (c, d, a, b, w[ 2], S13, 0x242070db); /* 3 */
	FF (b, c, d, a, w[ 3], S14, 0xc1bdceee); /* 4 */
	FF (a, b, c, d, w[ 4], S11, 0xf57c0faf); /* 5 */
	FF (d, a, b, c, w[ 5], S12, 0x4787c62a); /* 6 */
	FF (c, d, a, b, w[ 6], S13, 0xa8304613); /* 7 */
	FF (b, c, d, a, w[ 7], S14, 0xfd469501); /* 8 */
	FF (a, b, c, d, w[ 8], S11, 0x698098d8); /* 9 */
	FF (d, a, b, c, w[ 9], S12, 0x8b44f7af); /* 10 */
	FF (c, d, a, b, w[10], S13, 0xffff5bb1); /* 11 */
	FF (b, c, d, a, w[11], S14, 0x895cd7be); /* 12 */
	FF (a, b, c, d, w[12], S11, 0x6b901122); /* 13 */
	FF (d, a, b, c, w[13], S12, 0xfd987193); /* 14 */
	FF (c, d, a, b, w[14], S13, 0xa679438e); /* 15 */
	FF (b, c, d, a, w[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG (a, b, c, d, w[ 1], S21, 0xf61e2562); /* 17 */
	GG (d, a, b, c, w[ 6], S22, 0xc040b340); /* 18 */
	GG (c, d, a, b, w[11], S23, 0x265e5a51); /* 19 */
	GG (b, c, d, a, w[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG (a, b, c, d, w[ 5], S21, 0xd62f105d); /* 21 */
	GG (d, a, b, c, w[10], S22,  0x2441453); /* 22 */
	GG (c, d, a, b, w[15], S23, 0xd8a1e681); /* 23 */
	GG (b, c, d, a, w[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG (a, b, c, d, w[ 9], S21, 0x21e1cde6); /* 25 */
	GG (d, a, b, c, w[14], S22, 0xc33707d6); /* 26 */
	GG (c, d, a, b, w[ 3], S23, 0xf4d50d87); /* 27 */
	GG (b, c, d, a, w[ 8], S24, 0x455a14ed); /* 28 */
	GG (a, b, c, d, w[13], S21, 0xa9e3e905); /* 29 */
	GG (d, a, b, c, w[ 2], S22, 0xfcefa3f8); /* 30 */
	GG (c, d, a, b, w[ 7], S23, 0x676f02d9); /* 31 */
	GG (b, c, d, a, w[12], S24, 0x8d2a4c8a); /* 32 */
		
	/* Round 3 */
	HH (a, b, c, d, w[ 5], S31, 0xfffa3942); /* 33 */
	HH (d, a, b, c, w[ 8], S32, 0x8771f681); /* 34 */
	HH (c, d, a, b, w[11], S33, 0x6d9d6122); /* 35 */
	HH (b, c, d, a, w[14], S34, 0xfde5380c); /* 36 */
	HH (a, b, c, d, w[ 1], S31, 0xa4beea44); /* 37 */
	HH (d, a, b, c, w[ 4], S32, 0x4bdecfa9); /* 38 */
	HH (c, d, a, b, w[ 7], S33, 0xf6bb4b60); /* 39 */
	HH (b, c, d, a, w[10], S34, 0xbebfbc70); /* 40 */
	HH (a, b, c, d, w[13], S31, 0x289b7ec6); /* 41 */
	HH (d, a, b, c, w[ 0], S32, 0xeaa127fa); /* 42 */
	HH (c, d, a, b, w[ 3], S33, 0xd4ef3085); /* 43 */
	HH (b, c, d, a, w[ 6], S34,  0x4881d05); /* 44 */
	HH (a, b, c, d, w[ 9], S31, 0xd9d4d039); /* 45 */
	HH (d, a, b, c, w[12], S32, 0xe6db99e5); /* 46 */
	HH (c, d, a, b, w[15], S33, 0x1fa27cf8); /* 47 */
	HH (b, c, d, a, w[ 2], S34, 0xc4ac5665); /* 48 */
		
	/* Round 4 */
	II (a, b, c, d, w[ 0], S41, 0xf4292244); /* 49 */
	II (d, a, b, c, w[ 7], S42, 0x432aff97); /* 50 */
	II (c, d, a, b, w[14], S43, 0xab9423a7); /* 51 */
	II (b, c, d, a, w[ 5], S44, 0xfc93a039); /* 52 */
	II (a, b, c, d, w[12], S41, 0x655b59c3); /* 53 */
	II (d, a, b, c, w[ 3], S42, 0x8f0ccc92); /* 54 */
	II (c, d, a, b, w[10], S43, 0xffeff47d); /* 55 */
	II (b, c, d, a, w[ 1], S44, 0x85845dd1); /* 56 */
	II (a, b, c, d, w[ 8], S41, 0x6fa87e4f); /* 57 */
	II (d, a, b, c, w[15], S42, 0xfe2ce6e0); /* 58 */
	II (c, d, a, b, w[ 6], S43, 0xa3014314); /* 59 */
	II (b, c, d, a, w[13], S44, 0x4e0811a1); /* 60 */
	II (a, b, c, d, w[ 4], S41, 0xf7537e82); /* 61 */
	II (d, a, b, c, w[11], S42, 0xbd3af235); /* 62 */
	II (c, d, a, b, w[ 2], S43, 0x2ad7d2bb); /* 63 */
	II (b, c, d, a, w[ 9], S44, 0xeb86d391); /* 64 */

	*h0 = 0x67452301 + a;
	*h1 = 0xefcdab89 + b;
	*h2 = 0x98badcfe + c;
	*h3 = 0x10325476 + d;

}

void crack_serial(uint8_t initial_msg[8], int len) {
	unsigned int ph0, ph1, ph2, ph3;
	md5(initial_msg, len, &ph0, &ph1, &ph2, &ph3);

	uint8_t a,b,c,d;

	for (a = 0; a < 95; a++){
		for (b = 0; b < 95; b++){
			for (c = 0; c < 95; c++){
				for (d = 0; d < 95; d++){
					uint8_t guess[4] = {a+32,b+32,c+32,d+32};
					unsigned int h0, h1, h2, h3;
					md5(guess,len,&h0,&h1,&h2,&h3);

					if ((h0 == ph0) && (h1 == ph1) && (h2 == ph2) && (h3 == ph3)) {
						cout << "CRACKED " << endl;
					}
				}
			}
		}
	}
}

void crack_ispc(uint8_t initial_msg[8], int len) {
	unsigned int h0, h1, h2, h3;
	md5(initial_msg, len, &h0, &h1, &h2, &h3);

	for (uint8_t a = 32; a < 127; a++){
		for (uint8_t b = 32; b < 127; b++){
			unsigned int aa = 0x80000000 | (a << 16) | (b << 8);
			ispc::cracked(len, aa, h0, h1, h2, h3);
		}
	}

	uint8_t *p;
	
		// display result
	
		p=(uint8_t *)&h0;
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	
		p=(uint8_t *)&h1;
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	
		p=(uint8_t *)&h2;
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	
		p=(uint8_t *)&h3;
		printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
		puts("");
}