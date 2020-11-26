/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file AffineCodec.cpp
 @author Russell Taylor
 @date 11/20/20
*/

#include "AffineCodec.hpp"
#include "BlockReader.hpp"
#include "BlockWriter.hpp"

/**
 Constructs an AffineCodec object
 @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
 @param p the first RSA large prime number
 @param q the second RSA large prime number
 @param e the RSA public exponent
 @param a the first affine cipher key number
 @param b the second affine cipher key number
 */
AffineCodec::AffineCodec(Utilities* utilities, const BigNumber& p, const BigNumber& q, const BigNumber& e, const BigNumber& a, const BigNumber& b) : utilities(utilities), affineAlgorithm_(utilities, a, b), p(p), q(q), e(e), a(a), b(b) {
}

/**
 Reads unencrypted data from a binary input file stream, encrypts the data, and writes the result to an output file stream
 @param fin the input file stream
 @param fout the output file stream
 */
void AffineCodec::encryptStream(ifstream& fin, ofstream& fout) {
    BlockReader blockReader(utilities, fin);
    BigNumber plaintext = 0;
    
    blockMaxLength = calculateBlockMaxLength(p * q);
    
    for (int i = 0; ; ++i) {
        utilities->debugStream << "--- AffineCodec::encryptStream block #" << dec << i << ", max length " << blockMaxLength << " ---\n\n" << flush;

        int blockLength = blockReader.readData(plaintext, blockMaxLength);
        if (blockLength == 0)
            break;
        BigNumber ciphertext = affineAlgorithm_.encrypt(plaintext, blockMaxLength);

        fout << hex << blockLength <<  " " << hex << ciphertext << "\n";
    }
}

/**
 Decrypts the file stream
 @param fin the input file stream
 @param fout the output file stream
 */
void AffineCodec::decryptStream(ifstream& fin, ofstream& fout) const {
    int blockLength;
    BigNumber ciphertext;
    BlockWriter blockWriter(utilities, fout);

    for (int i = 0; fin >> hex >> blockLength >> hex >> ciphertext; ++i) {
        utilities->debugStream << "--- AffineCodec::decryptStream block #" << i << ", length " << blockLength << " ---\n\n" << flush;

        BigNumber plaintext = affineAlgorithm_.decrypt(ciphertext, blockMaxLength);
        blockWriter.writeData(plaintext, blockLength);
    }
}

/**
 Calculates the block maximum length
 @param n the crypto modulus
 */
unsigned int AffineCodec::calculateBlockMaxLength(const BigNumber& n) const {
    unsigned int blockMaxLength = 0;
    
    while (BigNumber(pow(16, blockMaxLength * 2)) < n)
        ++blockMaxLength;
    
    if (blockMaxLength < 1) {
        stringstream e;
        e << "calculateChunkSize - Modulus " << n << " is too small";
        throw runtime_error(e.str());
    }
    return blockMaxLength - 1;
}
