/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file Utilities.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef Utilities_hpp
#define Utilities_hpp

#include <boost/multiprecision/integer.hpp>
#include <fstream>
using namespace std;

typedef boost::multiprecision::checked_int256_t BigNumber;

class Utilities {
public:
    std::ofstream debugStream;
    
    /**
     Formats bytes for output to file
     @param byte the byte to be formatted
     @return the formatted byte
     */
    std::string formatByte(const unsigned char byte);
};

#endif /* Utilities_hpp */
