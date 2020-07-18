/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER04_H
#define CIPHER04_H

using namespace std;
string makeSquare(const string& password);
/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher04 : public Cipher
{
public:
    virtual string getPseudoAuth() { return "Corbin Hughes"; }
    virtual string getCipherName() { return "Polybius Square"; }
    virtual string getEncryptAuth() { return "Sam Wirthlin"; }
    virtual string getDecryptAuth() { return "Herman Kravchenko"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual string getCipherCitation()
    {
        return string("http://practicalcryptography.com/ciphers/classical-era/polybius-square/");
    }

    /**********************************************************
     * GET PSEUDOCODE
     * Returns the pseudocode as a string to be used by the caller.
     **********************************************************/
    virtual string getPseudocode()
    {
        string str;

        // The encrypt pseudocode
        str = "ENCRYPT\ntoLower(plainText, password);\nmakeSquare(password)";
        str +=   "\nloop(...){cipherText += findCharacterInSquare(plainText[i]);}\nreturn cipherText;\n";

        // The decrypt pseudocode
        str += "\n\nDECRYPTtoLower(cipherText, password);\nmakeSquare(password)";
        str +=    "\nloop(...){plainText += findPositionInSquare(cipherText[i]), cipherText[i + 1];}\nreturn plainText;\n";

        return str;
    }

    
    /**********************************************************
     * ENCRYPT
     * Converts all toLower, makes a square out of the password,
     * then loops through and converts each character to its position
     * in the square. (Polybius Square Cipher)
     **********************************************************/
    virtual string encrypt(const string& plainText,
         const string& password)
    {
        //make the square out of the password: both Bob and Alice need same password to converse    
        string square = makeSquare(password);

        int row, col;
        string cipherText;


        for (int i = 0; i < plainText.size(); i++) {
            //find the row and column where each character lies in the table
            size_t found = square.find(plainText[i]);
            if (found != string::npos) {
                //a new row starts every 8 (it's an 8 x 8 table)
                row = found / 8;
                //modulus finds the index on the row, i.e. the column
                col = found % 8;
            }
            //add the indexes to cipherText
            cipherText += to_string(row);
            cipherText += to_string(col);
        }
        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * Converts all toLower, makes a square out of the password,
     * then loops through and uses each digraph of numbers as row
     * and column to locate the correct char in the square.
     * (Polybius Square Cipher)
     **********************************************************/
    virtual string decrypt(const string& cipherText,
       const string& password)
    {
        string plainText = "";
        string square = makeSquare(password);
        int positionInSquare, col, row;

        //move two after reading in two, until done
        for (int i = 0; i < cipherText.size(); i += 2) {
            //row, then column
            row = cipherText[i] - 48;
            col = cipherText[i + 1] - 48;

            //basically just the opposite of the encryption
            positionInSquare = col + (row * 8);
            plainText += square[positionInSquare];
        }

        return plainText;
    }
};

/************
 * Makes a square by starting with the password,
 * then removing all "used up" chars from the list
 * and adding the unused ones in.
 ************/
string makeSquare(const string& password) {
    //put password at beginning of square
    string square = password;

    //obviously list could be adjusted as desired
    string acceptedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*,.-_=+~\\/<>:;\"\'?(| ";

    //put rest of letters into square (check if they are not part of password)
    bool putInSquare;
    for (int i = 0; i < acceptedChars.size(); i++) {
        putInSquare = true;
        for (int j = 0; j < password.size(); j++) {
            if (acceptedChars[i] == password[j])
                putInSquare = false;
        }
        if (putInSquare)
            square += acceptedChars[i];
    }

    return square;
}

#endif // CIPHER04_H