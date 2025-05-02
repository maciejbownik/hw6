#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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

        unsigned long long w[5] = {0};

        int numGroups = (k.length() + 5) / 6;

        for(int group = 0; group < numGroups; group++){
            int startPos = k.length() - (group + 1) * 6;
            if(startPos < 0) startPos = 0;

            int groupSize;
            if(k.length() < 6){
                groupSize = k.length();
            } else if(group == numGroups - 1 and k.length() % 6 != 0){
                groupSize = k.length() % 6;
            } else {
                groupSize = 6;
            }

            unsigned long long value = 0;

            for(int i = 0; i < groupSize; i++){
                int charPos = startPos + i;
                unsigned long long charValue = letterDigitToNumber(k[charPos]);
                value = value * 36 + charValue;
            }

            w[4 - /* numGroups + */ group] = value;
        }

        unsigned long long result = 0;
        for(int i = 0; i < 5; i++){
            result += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
				/*
				for(int i=0; i < 5; i++){
					std::cout << w[i] << std::endl;
				} */

        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter <= 57) return (letter - 22);

        return (std::tolower(letter) - 97);

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
