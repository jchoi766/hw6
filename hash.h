#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
		
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

			//array of unsigned long long 
			unsigned long long w[5] = {0};

			int groups = k.length()/6; // number of full groups 
			int remainder = k.length()%6;

			for (int i = 0; i < groups; i++) {
				//std::cout << "groups " << std::endl;

				unsigned long long sum = 0;
				int startIndex = k.length() - 6*(i+1);
				for (int j = 0; j < 6; j++){
					unsigned long long a = letterDigitToNumber(k[startIndex + j]);					
					sum += a * pow(36, 5-j); // power 5 -> power 0 
				}
				w[4-i] = sum;
			}

			if (remainder) {
				//std::cout << "remainder: " << remainder << std::endl;
				unsigned long long sum = 0;
				for (int i = 0; i < remainder; i++) {
					// k[2] * 36^0 
					sum += letterDigitToNumber(k[remainder-1-i]) * pow(36, i); //power0->power5
				}
				w[4-groups] = sum;
			}

			//print out w values - for str-hash-test.cpp 
			for (int i = 0; i < 5; i++) {
				//std::cout << "w[" << i<< "] = " << w[i] << std::endl;
			}
				
			// calculate h(k) 
			unsigned long long h = 0;
			for (int i = 0; i < 5; i++) {
				h += rValues[i] * w[i];
			}
			return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
			if (letter >= 'A' && letter <= 'Z') {
				return (letter - 'A');
			}
			if (letter >= 'a' && letter <= 'z') {
				return (letter -'a');
			}
			if (letter >= '0' && letter <= '9') {
				return (letter - '0' + 26);
			}
			return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
