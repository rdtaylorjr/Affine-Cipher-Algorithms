/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file AffineAlgorithm.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef AffineAlgorithm_hpp
#define AffineAlgorithm_hpp

#include <iostream>
#include "Utilities.hpp"

class AffineAlgorithm {
public:
    /**
     Constructs an AffineAlgorithm object
     @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
     @param a first key number
     @param b second key number
     */
    AffineAlgorithm(Utilities* utilities, const BigNumber& a, const BigNumber& b);

    /**
     Encrypts plaintext using an Affine Cipher
     @param plaintext the plaintext number to be encrypted
     @return the encrypted ciphertext
     */
    BigNumber encrypt(const BigNumber& plaintext, const int count) const;

    /**
     Decrypts plaintext using an Affine Cipher
     @param ciphertext the ciphertext number to be decrypted
     @return the decrypted plaintext
     */
    BigNumber decrypt(const BigNumber& ciphertext, const int count) const;
    
private:
    Utilities* utilities;
    const BigNumber& a;
    const BigNumber& b;
    
    /**
     Calculates the modular multiplicative inverse using the extended Euclidean algorithm
     @return the modular multiplicative inverse d
     */
    const BigNumber modInverse(const BigNumber& a, const BigNumber& m) const;
    
    /**
     Corrects the erroneous C++ modulus behavior for negative numbers
     @return the modulus
     */
    const BigNumber mod(const BigNumber& a, const BigNumber& b) const;
};

#endif /* AffineAlgorithm_hpp */
