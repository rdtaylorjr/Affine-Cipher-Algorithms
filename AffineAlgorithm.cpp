/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file AffineAlgorithm.cpp
 @author Russell Taylor
 @date 11/20/20
*/

#include <numeric>
#include "AffineAlgorithm.hpp"
using namespace std;

/**
 Constructs an AffineAlgorithm object
 @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
 @param a first key number
 @param b second key number
 */
AffineAlgorithm::AffineAlgorithm(Utilities* utilities, const BigNumber& a, const BigNumber& b) : utilities(utilities), a(a), b(b) {
    utilities->debugStream << "--- AffineAlgorithm" << "\n a " << a << "\n b " << b << "\n\n" << flush;
}

/**
 Encrypts plaintext using an Affine Cipher
 @param plaintext the plaintext number to be encrypted
 @return the encrypted ciphertext
 */
BigNumber AffineAlgorithm::encrypt(const BigNumber& plaintext, const int count) const {
    BigNumber r = 0, ciphertext = 0;
    for (int i = 0, offset = count * 8 - 8; offset >= 0; ++i, offset -= 8) {
        unsigned char plainByte = (unsigned char) ((plaintext >> offset) - (r << 8));
        r = (plaintext >> offset);
    
        BigNumber cipherByte = (a * plainByte + b) % 256;
        
        ciphertext <<= 8;
        ciphertext |= BigNumber(cipherByte);
    }
    
    utilities->debugStream << "AffineAlgorithm::encrypt 0x" << hex << plaintext << " -> 0x" << hex << ciphertext << "\n\n";

    return ciphertext;
}

/**
 Decrypts plaintext using an Affine Cipher
 @param ciphertext the ciphertext number to be decrypted
 @return the decrypted plaintext
 */
BigNumber AffineAlgorithm::decrypt(const BigNumber& ciphertext, const int count) const {
    BigNumber r = 0, plaintext = 0;
    for (int i = 0, offset = count * 8 - 8; offset >= 0; ++i, offset -= 8) {
        unsigned char cipherByte = (unsigned char) ((ciphertext >> offset) - (r << 8));
        r = (ciphertext >> offset);
    
        BigNumber plainByte = mod(modInverse(a, 256) * (cipherByte - b), 256);
        
        plaintext <<= 8;
        plaintext |= BigNumber(plainByte);
    }
    
    utilities->debugStream << "AffineAlgorithm::decrypt 0x" << hex << ciphertext << " -> 0x" << hex << plaintext << "\n\n";

    return plaintext;
}

/**
 Calculates the modular multiplicative inverse using the extended Euclidean algorithm
 Algorithm based on https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 @return the modular multiplicative inverse d
 */
const BigNumber AffineAlgorithm::modInverse(const BigNumber& a, const BigNumber& m) const {
    BigNumber s = a % m;
    for (int x = 1; x < m; ++x)
        if ((s * x) % m == 1)
            return x;
    throw runtime_error("Inverse doesn't exist");
}

/**
 Corrects the erroneous C++ modulus behavior for negative numbers
 @return the modulus
 */
const BigNumber AffineAlgorithm::mod(const BigNumber& a, const BigNumber& b) const {
    BigNumber result = a % b;
    return result >= 0 ? result : result + b;
}
