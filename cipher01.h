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

    virtual std::string getPseudoAuth() { return "pseudocode author"; }
    virtual std::string getCipherName() { return "Vigenere Cipher"; }
    virtual std::string getEncryptAuth() { return "encrypt author"; }
    virtual std::string getDecryptAuth() { return "decrypt author"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        std::string s;
        s += "Vigenere Cipher. (n.d.).Retrieved July 16, 2020, \n";
        s += "from https ://crypto.interactive-maths.com/vigenegravere-cipher.html";
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
       // str = "insert the encryption pseudocode\n";
        str = "encrypt(plainText, password)\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        //str += "insert the decryption pseudocode\n";
        str += "decrypt(cipherText, password)\n";
        str += "   RETURN plainnText\n\n";

        // helper the make key the same size as the text
        str += "createKey(plainText, password)\n";
        str += "   FOR i = 0 to size of plainText\n";
        str += "      char <- password[i% size of password]\n";
        str += "      key push char\n";
        str += "   RETURN key\n\n";


        return str;
    }


    
    /**********************************************************
     * ENCRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {
        std::string cipherText = "";
        key = createKey(plainText, password);
            ;
        for (int i = 0; i < plainText.size(); i++)
        {
            // converting in range  
            char x = (plainText[i] + key[i]) % sizeAlphabet;
            assert(x >= 0 && x < sizeAlphabet);

            // convert into alphabets(ASCII) 
            x += valueMinimum;

            cipherText.push_back(x);
        }
 
        // TODO - Add your code here
        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * TODO: ADD description
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText = "";
       
        for (int i = 0; i < cipherText.size(); i++)
        {
            // converting in range 0-25 
            char x = (cipherText[i] - key[i] + '|' ) % sizeAlphabet;

            // convert into alphabets(ASCII) 
            x += valueMinimum;
            plainText.push_back(x);
        }
        // TODO - Add your code here
        return plainText;
    }
    /**********************************************************
    * CREATEKEY
    * TODO: ADD description
    **********************************************************/
    std::string createKey(const std::string& cipherText, const std::string& password) {
        std::string createdKey;
       for (int i = 0; i < cipherText.size(); i++) {
           char temp = password[i % password.size()];
             createdKey.push_back(temp);
       }
       return createdKey;

    }
};

#endif // CIPHER01_H
