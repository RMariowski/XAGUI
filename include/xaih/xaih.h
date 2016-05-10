/***********************************************
 * XAIH - Xandev's All In Header
 * Make it easy, just include one header.
 *
 * Author: Radosław 'Xandev' Mariowski
 *
 * GitHub: https://github.com/Xandev/xaih
 ***********************************************/

#ifndef XANDEV_ALL_IN_HEADER_H
#define XANDEV_ALL_IN_HEADER_H

/***********************************************
 * Required Headers
 ***********************************************/
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>

/***********************************************
 * Visual Leak Detector (https://vld.codeplex.com)
 * To activate VLD you need to add 'VISUAL_LEAK_DETECTOR' to preprocessors or 
 * add '#define VISUAL_LEAK_DETECTOR' before including xaih header, it's your choice!
 ***********************************************/
#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning(disable: 4996) //<< _CRT_SECURE_NO_WARNINGS 
#define sscanf sscanf_s
#if defined(VISUAL_LEAK_DETECTOR)
#include <vld.h>
#endif
#endif

/***********************************************
 * Shorter names for primitive types. 
 ***********************************************/
typedef const char cchar;

/***********************************************
 * Well, I never needed buffer greater than 256 characters for my texts etc.
 ***********************************************/
#define MAX_BUFFER 256

/***********************************************
 * Useful macros for better manage pointers.
 ***********************************************/
#define SAFE_RELEASE(x) \
    { \
        x->Release(); \
    }
#define SAFE_DELETE(x) \
    { \
        delete x; \
        x = 0; \
    }
#define SAFE_DELETE_ARRAY(x) \
    { \
        delete[] x; \
        x = 0; \
    }

/***********************************************
 * xaih class (also as namespace, because why not?)
 ***********************************************/
class xaih
{
	public:

		/**
		 * Initialize random generation with nulled time as seed.
		 * It should be called on the start of application.
		 */
		static inline void InitRandomSeed()
		{
#if defined(_WIN32)
			srand(static_cast<unsigned int>(time(0)));
#else
			srand(time(0));
#endif
		}

		/**
		 * Initialize random generation with specified seed.
		 * @param seed Your seed for random generation.
		 */
		static inline void InitRandomSeed(unsigned int seed) { srand(seed); }

		/**
		 * Generates a random number from a specific interval.
		 * @param min Your minimal value of interval.
		 * @param max Your maximal value of interval.
		 * @return Generated random number.
		 */
		static inline int Random(int min, int max) { return rand() % (max - min + 1) + min; }

		/**
		 * Rounds the value.
		 * @param Value to round.
		 * @return Rounded value
		 */
		static inline double Round(double value)
		{ return (value < 0.0) ? ceil(value - 0.5) : floor(value + 0.5); }

		/**
		 * Rounds the value.
		 * @param Value to round.
		 * @return Rounded value
		 */
		static inline float Round(float value)
		{ return (value < 0.0f) ? ceil(value - 0.5f) : floor(value + 0.5f); }

		/**
		 * Print new line
		 */
		static inline void NewLine() { printf("\n"); }

		/**
		 * Print the text
		 * @param text Text to be printed.
		 * @param additionalNewLine Adds additional new line to end of text if true.
		 */
		static inline void WriteLine(const char* text, bool additionalNewLine = false)
		{ additionalNewLine ? printf("%s\n\n", text) : printf("%s\n", text); }

		/**
		 * Print the text with "INFO: " at beginning.
		 * @param text Text to be printed.
		 * @param additionalNewLine Adds additional new line to end of text if true.
		 */
		static inline void WriteInfoLine(const char* text, bool additionalNewLine = false)
		{ additionalNewLine ? printf("INFO: %s\n\n", text) : printf("INFO: %s\n", text); }

		/**
		 * Print the text with "WARNING: " at beginning.
		 * @param text Text to be printed.
		 * @param additionalNewLine Adds additional new line to end of text if true.
		 */
		static inline void WriteWarningLine(const char* text, bool additionalNewLine = false)
		{ additionalNewLine ? printf("WARNING: %s\n\n", text) : printf("WARNING: %s\n", text); }

		/**
		 * Print the text with "ERROR: " at beginning.
		 * @param text Text to be printed.
		 * @param additionalNewLine Adds additional new line to end of text if true.
		 */
		static inline void WriteErrorLine(const char* text, bool additionalNewLine = false)
		{ additionalNewLine ? printf("ERROR: %s\n\n", text) : printf("ERROR: %s\n", text); }

		/**
		 * Converts string to integer.
		 * @param string String to be converted.
		 * @return Converted number.
		 */
		static int StrToInt(const char* string)
		{
			int variable;
			StrToInt(string, &variable);
			return variable;
		}

		/**
		 * Faster version of converting string to integer.
		 * @param string String to be converted.
		 * @param value Pointer to integer variable.
		 */
		static inline void StrToInt(const char* string, int* variable)
		{ sscanf(string, "%d", variable); }

		/**
		 * Converts string to unsigned integer.
		 * @param string String to be converted.
		 * @return Converted number.
		 */
		static unsigned int StrToUInt(const char* string)
		{
			unsigned int variable;
			StrToUInt(string, &variable);
			return variable;
		}

		/**
		 * Faster version of converting string to unsigned integer.
		 * @param string String to be converted.
		 * @param value Pointer to unsigned integer variable.
		 */
		static inline void StrToUInt(const char* string, unsigned int* variable)
		{ sscanf(string, "%u", variable); }

		/**
		 * Converts string to float number.
		 * @param string String to be converted.
		 * @return Converted number.
		 */
		static float StrToFloat(const char* string)
		{
			float variable;
			StrToFloat(string, &variable);
			return variable;
		}

		/**
		 * Faster version of converting string to float number.
		 * @param string String to be converted.
		 * @param value Pointer to float variable.
		 */
		static inline void StrToFloat(const char* string, float* variable)
		{ sscanf(string, "%f", variable); }

		/**
		 * Converts string to double number.
		 * @param string String to be converted.
		 * @return Converted number.
		 */
		static double StrToDouble(const char* string)
		{
			double variable;
			StrToDouble(string, &variable);
			return variable;
		}

		/**
		 * Faster version of converting string to double number.
		 * @param string String to be converted.
		 * @param value Pointer to double variable.
		 */
		static inline void StrToDouble(const char* string, double* variable)
		{ sscanf(string, "%lf", variable); }

		/**
		 * Converts string to boolean.
		 * @param string String to be converted.
		 * @return Converted boolean.
		 */
		static inline bool StrToBool(const char* string)
		{ return !(strcmp(string, "false") == 0 || strcmp(string, "0") == 0); }

		/**
		 * Converts integer to std::string.
		 * @param value Integer to be converted.
		 * @return Converted string.
		 */
		static std::string IntToStr(int value)
		{
			char buffer[11];
			sprintf(buffer, "%d", value);
			return buffer;
		}

		/**
		 * Faster version of converting integer to string.
		 * @param value Integer to be converted.
		 * @param buffer Buffer for string.
		 */
		static inline void IntToStr(int value, char* buffer)
		{ sprintf(buffer, "%d", value); }

		/**
		 * Converts unsigned integer to std::string.
		 * @param value Unsigned integer to be converted.
		 * @return Converted string.
		 */
		static std::string UIntToStr(unsigned int value)
		{
			char buffer[11];
			sprintf(buffer, "%u", value);
			return buffer;
		}

		/**
		 * Faster version of converting unsigned integer to string.
		 * @param value Unsigned integer to be converted.
		 * @param buffer Buffer for string.
		 */
		static inline void UIntToStr(unsigned int value, char* buffer)
		{ sprintf(buffer, "%u", value); }

		/**
		 * Clamps value due to minimal and maximal value.
		 * @param current Your current value.
		 * @param min Minimal value of interval.
		 * @param max Maximal value of interval.
		 * @return The value that fit in interval(current) or the nearest in interval(min/max). 
		 */
		template <typename type, typename type2, typename type3>
		static type Clamp(type current, type2 min, type3 max)
		{
			if (current >= max) return max;
			else if (current <= min) return min;
			return current;
		}

		/**
		 * Parse std::string.
		 * Example:
		 * std::string str = "its.mystring.";
		 * xaih::ParseString(str, "."); 
		 * will return "its" as std::string.
		 * @param string std::string to be parsed.
		 * @param separator Separator to parse.
		 * @return Parsed string.
		 */
		static std::string& ParseString(std::string &string, const char* separator)
		{
			// Static because it's much faster when you use it more than once.
			static std::string buffer;
			buffer = string;

			unsigned int separatorPosition = buffer.find(separator);
			buffer.erase(separatorPosition, buffer.length() - separatorPosition);
			string.erase(0, separatorPosition + 1);

			return buffer;
		}

		/**
		 * Checks if point is in specified rectangle.
		 * @param pointX Point's x position.
		 * @param pointY Point's y position.
		 * @param rectX Rectangle's x position.
		 * @param rectY Rectangle's y position.
		 * @param rectWidth Rectangle's width.
		 * @param rectHeight Rectangle's height.
		 * @return True if point is in rectangle, false when isn't.
		 */
		static bool IsPointInRectangle(int pointX, int pointY, int rectX, int rectY, 
			int rectWidth, int rectHeight)
		{
			if (rectX < pointX && rectY < pointY && rectX + rectWidth > pointX && 
				rectY + rectHeight > pointY) return true;
			return false;
		}

		/**
		 * Checks if point is in specified rectangle.
		 * @param pointX Point's x position.
		 * @param pointY Point's y position.
		 * @param rectX Rectangle's x position.
		 * @param rectY Rectangle's y position.
		 * @param rectWidth Rectangle's width.
		 * @param rectHeight Rectangle's height.
		 * @return True if point is in rectangle, false when isn't.
		 */
		static bool IsPointInRectangle(float pointX, float pointY, float rectX, float rectY, 
			unsigned int rectWidth, unsigned int rectHeight)
		{
			if (rectX < pointX && rectY < pointY && rectX + rectWidth > pointX && 
				rectY + rectHeight > pointY) return true;
			return false;
		}
};

/***********************************************
 * SHA1 users ONLY!
 ***********************************************/
 #if defined(SHA1)
/*
 Copyright (c) 2011, Micael Hildenborg
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Micael Hildenborg nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY Micael Hildenborg ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL Micael Hildenborg BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***********************************************
 * xsha1 class
 * Example:
 * uchar hash[20];
 * char hex[MAX_BUFFER];
 * xsha1::Calculate(password, strlen(password), hash);
 * xsha1::ToHexString(hash, hex);
 * hex - your encrypted password by sha1 algorithm
 ***********************************************/
class xsha1
{
	public: 

		/**
		 *
		 * @param src Points to any kind of data to be hashed.
		 * @param bytelength The number of bytes to hash from the src pointer.
		 * @param hash Should point to a buffer of at least 20 bytes of size for storing the 
		 * sha1 result in.
		 */
		static void Calculate(const void* src, const int byteLength, unsigned char* hash)
		{
			unsigned int result[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };
			const unsigned char* sarray = static_cast<const unsigned char*>(src);
			unsigned int buffer[80];

			// Loop through all complete 64byte blocks.
			const int endOfFullBlocks = byteLength - 64;
			int endCurrentBlock;
			int currentBlock = 0;

			while (currentBlock <= endOfFullBlocks)
			{
				endCurrentBlock = currentBlock + 64;

				// Init the round buffer with the 64 byte block data.
				for (int roundPos = 0; currentBlock < endCurrentBlock; currentBlock += 4)
				{
					// This line will swap endian on big endian and keep endian on little endian.
					buffer[roundPos++] = (unsigned int) sarray[currentBlock + 3]
							| (((unsigned int) sarray[currentBlock + 2]) << 8)
							| (((unsigned int) sarray[currentBlock + 1]) << 16)
							| (((unsigned int) sarray[currentBlock]) << 24);
				}
				InnerHash(result, buffer);
			}

			// Handle the last and not full 64 byte block if existing.
			endCurrentBlock = byteLength - currentBlock;

			ClearBuffer(buffer);

			int lastBlockBytes = 0;
			for (;lastBlockBytes < endCurrentBlock; ++lastBlockBytes)
			{
				buffer[lastBlockBytes >> 2] |= (unsigned int) sarray[lastBlockBytes + currentBlock] << 
					((3 - (lastBlockBytes & 3)) << 3);
			}

			buffer[lastBlockBytes >> 2] |= 0x80 << ((3 - (lastBlockBytes & 3)) << 3);

			if (endCurrentBlock >= 56)
			{
				InnerHash(result, buffer);
				ClearBuffer(buffer);
			}

			buffer[15] = byteLength << 3;
			InnerHash(result, buffer);

			// Store hash in result pointer, and make sure we get in in the correct order on both 
			// endian models.
			for (int hashByte = 20; --hashByte >= 0;)
				hash[hashByte] = (result[hashByte >> 2] >> (((3 - hashByte) & 0x3) << 3)) & 0xff;
		}

		/**
		 * 
		 * @param hash 20 bytes of sha1 hash. This is the same data that is the result from the calc 
		 * function.
		 * @param hexstring Should point to a buffer of at least 41 bytes of size for storing the 
		 * hexadecimal representation of the hash. A zero will be written at position 40, so the buffer
		 * will be a valid zero ended string.
		 */
		static void ToHexString(const unsigned char* hash, char* hexstring)
		{
			const char hexDigits[] = { "0123456789abcdef" };
			for (int hashByte = 20; --hashByte >= 0;)
			{
				hexstring[hashByte << 1] = hexDigits[(hash[hashByte] >> 4) & 0xf];
				hexstring[(hashByte << 1) + 1] = hexDigits[hash[hashByte] & 0xf];
			}
			hexstring[40] = 0;
		}

	private:

		/**
		 * Rotate an integer value to left.
		 * @param value .
		 * @param steps .
		 * @return . 
		 */
		static inline const unsigned int Rol(const unsigned int value, const unsigned int steps)
		{ return ((value << steps) | (value >> (32 - steps))); }
		
		/**
		 * Sets the first 16 integers in the buffer to zero.
		 * Used for clearing the buffer.
		 * @param buffer Buffer to clear.
		 */
		static inline void ClearBuffer(unsigned int* buffer)
		{
			for (int pos = 16; --pos >= 0;)
				buffer[pos] = 0;
		}

		/**
		 *
		 * @param result .
		 * @param buffer .
		 */
		static void InnerHash(unsigned int* result, unsigned int* buffer)
		{
			unsigned int a = result[0];
			unsigned int b = result[1];
			unsigned int c = result[2];
			unsigned int d = result[3];
			unsigned int e = result[4];

			int round = 0;

			#define sha1macro(func,val) \
			{ \
				const unsigned int t = Rol(a, 5) + (func) + e + val + buffer[round]; \
				e = d; \
				d = c; \
				c = Rol(b, 30); \
				b = a; \
				a = t; \
			}

			while (round < 16)
			{
				sha1macro((b & c) | (~b & d), 0x5a827999)
				++round;
			}

			while (round < 20)
			{
				buffer[round] = Rol((buffer[round - 3] ^ buffer[round - 8] ^ buffer[round - 14] ^ 
					buffer[round - 16]), 1);
				sha1macro((b & c) | (~b & d), 0x5a827999)
				++round;
			}

			while (round < 40)
			{
				buffer[round] = Rol((buffer[round - 3] ^ buffer[round - 8] ^ buffer[round - 14] ^ 
					buffer[round - 16]), 1);
				sha1macro(b ^ c ^ d, 0x6ed9eba1)
				++round;
			}

			while (round < 60)
			{
				buffer[round] = Rol((buffer[round - 3] ^ buffer[round - 8] ^ buffer[round - 14] ^ 
					buffer[round - 16]), 1);
				sha1macro((b & c) | (b & d) | (c & d), 0x8f1bbcdc)
				++round;
			}

			while (round < 80)
			{
				buffer[round] = Rol((buffer[round - 3] ^ buffer[round - 8] ^ buffer[round - 14] ^ 
					buffer[round - 16]), 1);
				sha1macro(b ^ c ^ d, 0xca62c1d6)
				++round;
			}

			#undef sha1macro

			result[0] += a;
			result[1] += b;
			result[2] += c;
			result[3] += d;
			result[4] += e;
		}
};
#endif
/***********************************************
 * End of SHA1 users ONLY!
 ***********************************************/
 
#endif
