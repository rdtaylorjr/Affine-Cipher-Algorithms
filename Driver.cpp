/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file Driver.cpp
 @author Russell Taylor
 @date 11/20/20
*/

#include "Driver.hpp"

/**
 Constructs a Driver object
 @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
 */
Driver::Driver(Utilities* utilities) : utilities(utilities) {
}

/**
 Tests files
 @param number the file number
 */
void Driver::testFile(const string& number) {
    const string& debugFile = number + "_debug.txt";
    const string& keyFile = number + "_keymat.txt";
    const string& plainFile = number + "_in.dat";
    const string& encryptedFile = number + "_encrypted.txt";
    const string& decryptedFile = number + "_decrypted.dat";

    utilities->debugStream.open(debugFile);

    cout << "*** Testing input file " << plainFile << ", debug output file " << debugFile << " ***\n" << flush;

    BigNumber p, q, e, a, b;
    importKeyMaterials(keyFile, p, q, e, a, b);
    AffineCodec affineCodec(utilities, p, q, e, a, b);
    
    testEncryption(affineCodec, plainFile, encryptedFile);
    testDecryption(affineCodec, encryptedFile, decryptedFile);
    compareFiles(plainFile, decryptedFile);

    utilities->debugStream << ">>> Files " << plainFile << " and " << decryptedFile << " are equal.\n" << flush;
    utilities->debugStream.close();

    cout << "\nOK\n\n" << flush;
}

/**
 Tests encryption
 @param affineCodec the AffineCodec object
 @param plainFile the plaintext file name
 @param encryptedFile the encrypted file name
 */
void Driver::testEncryption(AffineCodec& affineCodec, const string& plainFile, const string& encryptedFile) { 
    ifstream fin(plainFile, ios::binary);
    if (!fin)
        throw runtime_error("Cannot open file " + plainFile + " for reading");
    ofstream fout(encryptedFile);
    if (!fout)
        throw runtime_error("Cannot open file " + encryptedFile + " for writing");
    
    utilities->debugStream << "*** Encrypting " << plainFile << ", size " << fileSize(plainFile) << " -> " << encryptedFile << " ***\n\n" << flush;
    
    affineCodec.encryptStream(fin, fout);
    
    fin.close();
    fout.close();
    
    utilities->debugStream << "Encrypted file " << encryptedFile << " size is " << fileSize(encryptedFile) << "\n\n" << flush;
}

/**
 Tests decryption
 @param affineCodec the AffineCodec object
 @param encryptedFile the encrypted file name
 @param decryptedFile the decrypted file name
 */
void Driver::testDecryption(const AffineCodec& affineCodec, const string& encryptedFile, const string& decryptedFile) {
    ifstream fin(encryptedFile);
    if (!fin)
        throw runtime_error("Cannot open file " + encryptedFile + " for reading");
    ofstream fout(decryptedFile, ios::binary);
    if (!fout)
        throw runtime_error("Cannot open file " + decryptedFile + " for writing");

    utilities->debugStream << "*** Decrypting " << encryptedFile << ", size " << fileSize(encryptedFile) << " -> " << decryptedFile << " ***\n\n" << flush;
    
    affineCodec.decryptStream(fin, fout);
    
    fin.close();
    fout.close();

    utilities->debugStream << "Decrypted file " << decryptedFile << " size is " << fileSize(decryptedFile) << "\n\n" << flush;
}

/**
 Initializes the AffineCodec with input from the key materials file
 @param keyFile the key materials file name
 @param p the first RSA large prime number
 @param q the second RSA large prime number
 @param e the RSA public exponent
 @param a the first affine cipher key number
 @param b the second affine cipher key number
 */
void Driver::importKeyMaterials(const string& keyFile, BigNumber& p, BigNumber& q, BigNumber& e, BigNumber& a, BigNumber& b) {
    ifstream fin(keyFile);
    if (!fin)
        throw runtime_error("Cannot open key material file " + keyFile + " for reading");

    while (fin) {
        string t;
        fin >> t;
        if (fin.eof())
            break;

        if (t == "p")
            fin >> p;
        else if (t == "q")
            fin >> q;
        else if (t == "e")
            fin >> e;
        else if (t == "a")
            fin >> a;
        else if (t == "b")
            fin >> b;
        else
            throw runtime_error("Invalid token " + t + " in key file " + keyFile);
    }
    
    if (p == 0)
        throw runtime_error("Missing or invalid p value in key file " + keyFile);
    if (q == 0)
        throw runtime_error("Missing or invalid q value in key file " + keyFile);
    if (e == 0)
        throw runtime_error("Missing or invalid e value in key file " + keyFile);
    if (a == 0)
        throw runtime_error("Missing or invalid a value in key file " + keyFile);
    if (b == 0)
        throw runtime_error("Missing or invalid b value in key file " + keyFile);

    fin.close();
}

/**
 Compares files to determine whether they are the same
 @param first the name of the first file to be compared
 @param second the name of the second file to be compared
 */
void Driver::compareFiles(const string& first, const string& second) {
    ifstream fin1(first, ios::binary);
    ifstream fin2(second, ios::binary);

    if (!fin1)
        throw runtime_error("Cannot open file " + first + " for reading");
    if (!fin2)
        throw runtime_error("Cannot open file " + second + " for reading");

    int blockCount = 0;
    const int BLOCKSIZE = 1024;
    char buffer1[BLOCKSIZE];
    char buffer2[BLOCKSIZE];

    while(true) {
        const int length1 = int(fin1.read(buffer1, BLOCKSIZE).gcount());
        const int length2 = int(fin2.read(buffer2, BLOCKSIZE).gcount());
        
        if (length1 != length2)
            throw runtime_error("Sizes of the files are different: file " + first  + " has size " + to_string(length1 + BLOCKSIZE * blockCount) + ", file " + second + " has size " + to_string(length2 + BLOCKSIZE * blockCount));

        for (int i = 0; i < length1; ++i)
            if (buffer1[i] != buffer2[i])
                throw runtime_error("Files are different at position " + to_string(i + BLOCKSIZE * blockCount) + ", file " + first  + " has character " + utilities->formatByte(buffer1[i]) + ", file " + second + " has character " + utilities->formatByte(buffer2[i]));

        if (length1 == 0)
            break;

        ++blockCount;
    }

    fin1.close();
    fin2.close();
}

/**
 Returns the size of a file
 @param file the name of the file
 @return the size of the file
 */
int Driver::fileSize(const string& file) {
    ifstream fin(file);
    fin.seekg(0, ios::end);
    int size = int(fin.tellg());
    fin.seekg(0, ios::beg);
    fin.close();
    return size;
}
