/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER01_H
#define CIPHER01_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher01 : public Cipher
{
    char valueMinimum = ' ';
    char valueMaximum = '~';
    char sizeAlphabet = valueMaximum - valueMinimum;
    std::string key = "";

public:

    virtual std::string getPseudoAuth() { return "Coleen Hull"; }
    virtual std::string getCipherName() { return "Vigenere Cipher"; }
    virtual std::string getEncryptAuth() { return "Corbin Hughes"; }
    virtual std::string getDecryptAuth() { return "Sam Wirhtlin"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string s;
        s + "Bruen, A.A., & amp; Forcinito, M.A. (2005).The Vigenere Cipher.In Cryptography, ";
        s += "information theoryand error - correction: A handbook for the 21st century(pp. 21 - 22).Hoboken ";
        s += ": Wiley.doi : https ://books.google.com/books?id=fd2LtVgFzoMC&amp;pg=PA21#v=onepage&amp;q&amp;f=false";
        return s;
        
    }

    /**********************************************************
     * GET PSEUDOCODE
     * Returns the pseudocode as a string to be used by the caller.
     **********************************************************/
    virtual std::string getPseudocode()
    {
        std::string str;

        // TODO: please format your pseudocode
        // The encrypt pseudocode
        str = "encrypt(plainText, password)\n";
        str += "   ciperText\n";
        str += "   key <- createKey(plainText, password)\n";
        str += "   FOR i = 0 to size of plainText\n";
        str += "      temp <- plainText[i] + key[i] % alphabet size\n";
        str += "      temp += minimum alphabet value\n";
        str += "      ciperText.push_back(temp)\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += "   plainText\n";
        str += "   FOR all of cipherText\n"; 
        str += "      temp <- cipherText[i] - key[i] + alphabest size  + alphabet minvalue) % alphabet size\n";
        str += "      temp += alphabet min value\n";
        str += "      plainText.push_back(temp)\n";
        str += "   RETURN plainnText\n\n";

        // helper the make key the same size as the text
        str += "createKey(plainText, password)\n";
        str += "   key\n";
        str += "   FOR i = 0 to size of plainText\n";
        str += "      char <- password[i% password size]\n";
        str += "      key.push_back(char)\n";
        str += "   RETURN key\n\n";


        return str;
    }


    
    /**********************************************************
     * ENCRYPT
     * PARAMETERS: takes a string plaiText and string password
     * RETURNS: encrypted text
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {
        std::string cipherText = "";
        key = createKey(plainText, password);
        // loop trough entire plain text
        for (int i = 0; i < plainText.size(); i++)
        {
            // converting in range  
            char x = (plainText[i] + key[i]) % sizeAlphabet;
            assert(x >= 0 && x < sizeAlphabet);

            // starts at the alphabest minimum value
            x += valueMinimum;
            // add to string
            cipherText.push_back(x);
        }
        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * PARAMETERS: takes a string encrpyted or cipher text and string password
     * RETURNS: plain text
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText = "";
        // loop through entire encrypted text
        for (int i = 0; i < cipherText.size(); i++)
        {
            // converting in range 0-94 total alpahbet range
            char x = (cipherText[i] - key[i] + '|' ) % sizeAlphabet;

            // move to first alphabet value
            x += valueMinimum;
            // add to string
            plainText.push_back(x);
        }
        
        return plainText;
    }
    /**********************************************************
    * CREATEKEY
    * PARAMETERS: takes a string encrpyted or cipher text and string password
    * RETURNS: key to create encrypted and plain text
    **********************************************************/
    std::string createKey(const std::string& cipherText, const std::string& password) {
        std::string createdKey = "";
        // create a key based on password that is the same size as the text to be encrypted
       for (int i = 0; i < cipherText.size(); i++) {
           char temp = password[i % password.size()];
             createdKey.push_back(temp);
       }
       return createdKey;
    }
};

#endif // CIPHER01_H
