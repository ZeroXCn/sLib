/**
*
*	SCodeHelper库
*	编码类-各种编码解码转换
*	@author 徐敏荣
*	@version v0.5 2012-07-17
*
*/
#ifndef _SCODEHELPER_H
#define _SCODEHELPER_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdint.h>

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

class SCodeHelper
{
private:
	SCodeHelper(){}

	static const uint32_t k[64];

	// r specifies the per-round shift amounts
	static const uint32_t r[];

	// leftrotate function definition
private:
	static void to_bytes(uint32_t val, uint8_t *bytes)
	{
		bytes[0] = (uint8_t)val;
		bytes[1] = (uint8_t)(val >> 8);
		bytes[2] = (uint8_t)(val >> 16);
		bytes[3] = (uint8_t)(val >> 24);
	}

	static uint32_t to_int32(const uint8_t *bytes)
	{
		return (uint32_t)bytes[0]
			| ((uint32_t)bytes[1] << 8)
			| ((uint32_t)bytes[2] << 16)
			| ((uint32_t)bytes[3] << 24);
	}

	//默认输出时需要将每一位进行16进制输出
	static void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {

		// These vars will contain the hash
		uint32_t h0, h1, h2, h3;

		// Message (to prepare)
		uint8_t *msg = NULL;

		size_t new_len, offset;
		uint32_t w[16];
		uint32_t a, b, c, d, i, f, g, temp;

		// Initialize variables - simple count in nibbles:
		h0 = 0x67452301;
		h1 = 0xefcdab89;
		h2 = 0x98badcfe;
		h3 = 0x10325476;

		//Pre-processing:
		//append "1" bit to message    
		//append "0" bits until message length in bits ≡ 448 (mod 512)
		//append length mod (2^64) to message

		for (new_len = initial_len + 1; new_len % (512 / 8) != 448 / 8; new_len++)
			;

		msg = (uint8_t*)malloc(new_len + 8);
		memcpy(msg, initial_msg, initial_len);
		msg[initial_len] = 0x80; // append the "1" bit; most significant bit is "first"
		for (offset = initial_len + 1; offset < new_len; offset++)
			msg[offset] = 0; // append "0" bits

		// append the len in bits at the end of the buffer.
		to_bytes(initial_len * 8, msg + new_len);
		// initial_len>>29 == initial_len*8>>32, but avoids overflow.
		to_bytes(initial_len >> 29, msg + new_len + 4);

		// Process the message in successive 512-bit chunks:
		//for each 512-bit chunk of message:
		for (offset = 0; offset<new_len; offset += (512 / 8)) {

			// break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
			for (i = 0; i < 16; i++)
				w[i] = to_int32(msg + offset + i * 4);

			// Initialize hash value for this chunk:
			a = h0;
			b = h1;
			c = h2;
			d = h3;

			// Main loop:
			for (i = 0; i<64; i++) {

				if (i < 16) {
					f = (b & c) | ((~b) & d);
					g = i;
				}
				else if (i < 32) {
					f = (d & b) | ((~d) & c);
					g = (5 * i + 1) % 16;
				}
				else if (i < 48) {
					f = b ^ c ^ d;
					g = (3 * i + 5) % 16;
				}
				else {
					f = c ^ (b | (~d));
					g = (7 * i) % 16;
				}

				temp = d;
				d = c;
				c = b;
				b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
				a = temp;

			}

			// Add this chunk's hash to result so far:
			h0 += a;
			h1 += b;
			h2 += c;
			h3 += d;

		}

		// cleanup
		free(msg);

		//var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
		to_bytes(h0, digest);
		to_bytes(h1, digest + 4);
		to_bytes(h2, digest + 8);
		to_bytes(h3, digest + 12);
	}
public:
	static std::string MD5(std::string content,bool is16=false){
		uint8_t digestA[16];
		uint8_t digestB[3];
		std::string ret;
		md5((uint8_t *)content.c_str(), content.size(), digestA);
		for (int i = 0; i < 16; i++){
			//需要将每以为转为16进制才能输出
			sprintf_s((char *)digestB, 3, "%2.2x", (uint8_t)digestA[i]);
			ret += (char *)digestB;
		}
		if (is16)ret = ret.substr(8,16);	//提取中间16即为16进制输出
		return ret;
	}

	///////////////////////以下函数用于字符串加密///////////////////////////
	//各种编码方式
	/**
	*最简单的异或法:A^B=C;C^B=A;
	*
	*/
	static std::string XOR(std::string str, std::string key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			int j = i%key.length();
			char tch = str.at(i) ^ key.at(j);

			Code += tch;
		}
		return Code;
	}
	static std::string EnXOR(std::string str, std::string key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			int j = i%key.length();
			char tch = str.at(i) ^ key.at(j);

			Code += tch;
		}
		return Code;
	}

	static std::string XOR(std::string str, int key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			char tch = str.at(i) ^ key;

			Code += tch;
		}
		return Code;
	}
	static std::string EnXOR(std::string str, int key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			char tch = str.at(i) ^ key;

			Code += tch;
		}
		return Code;
	}
	/**
	*偏移法:A+B+C=D;D-B-C=A
	*
	*/
	static std::string Offset(std::string str, std::string key, int offset = 0){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			int j = i%key.length();
			char tch = str.at(i) + key.at(j) + offset;

			Code += tch;
		}
		return Code;
	}
	static std::string EnOffset(std::string str, std::string key, int offset = 0){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			int j = i%key.length();
			char tch = str.at(i) - key.at(j) - offset;

			Code += tch;
		}
		return Code;
	}

	static std::string Offset(std::string str, int key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			char tch = str.at(i) + key;

			Code += tch;
		}
		return Code;
	}
	static std::string EnOffset(std::string str, int key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			char tch = str.at(i) - key;

			Code += tch;
		}
		return Code;
	}

	/*
	*其他算法应满足F(a,b)=c	其中a,b,c属于[33,126]
	*/

	/**
	*折半法:(a+b)/2=c,a=2c-b
	*因为有小数的关系,采用转义法输出转义字符代表这个为小数,计算时应加上0.5
	*(33+34)/2=33.5 先输出转义"/"在输出33字符,读入时则先读"/"表示有转移加上0.5在计算
	*如果恰巧为转义字符,则替换为不可见31(概率应该很小),读到31表示与转义字符相等
	*本函数采用key[j]做转义字符
	*
	*/
	static std::string Binary(std::string str, std::string key){
		std::string Code = "";
		for (int i = 0; i<str.length(); i++){
			int j = i%key.length();
			char tch; float result;

			result = (str.at(i) + key.at(j)) / 2.0;
			tch = (int)result;
			if ((float)((float)result - (int)result)>0){	//折半有小数
				Code += key.at(j);//取key第j个做转义
			}
			else{
				//不用转义,但若恰好为转义字符,再转义
				if (tch == key.at(j))tch = 31;	//换成31不可见,下次碰见31直译(在文本中不可见,但实际存在)
			}
			Code += tch;
		}
		return Code;
	}

	static std::string EnBinary(std::string str, std::string key){
		std::string Code = ""; int k = 0;
		for (int i = 0; i<str.length(); i++){
			int j = k%key.length();
			char tch; float result = 0;

			//转义字符直接等于它了
			if (str.at(i) != 31){
				//遇到转义字符时
				if (str.at(i) == key.at(j)){
					i++;
					result += 0.5 + str.at(i);//还原
				}
				else result += str.at(i);//没有转义下还原				
				tch = (int)(2 * result - key.at(j));
			}
			else tch = key.at(j);
			Code += tch;
			k++;
		}

		return Code;
	}
};

const uint32_t SCodeHelper::k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

const uint32_t SCodeHelper::r[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

#endif