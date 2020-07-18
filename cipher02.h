/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER02_H
#define CIPHER02_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher02 : public Cipher
{
public:
    virtual std::string getPseudoAuth() { return "Herman Kravchenko"; }
    virtual std::string getCipherName() { return "ROT 13"; }
    virtual std::string getEncryptAuth() { return "Coleen Hull"; }
    virtual std::string getDecryptAuth() { return "Corbin Hughes"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
        return std::string("https://blog.didierstevens.com/2006/07/24/rot13-is-used-in-windows-you%E2%80%99re-joking/");
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
        str += "   cipherText\n";
        str += "   FOR i = 0 to size of plainText\n";
        str += "      if plainText.tolower(i)\n";
        str += "        cipherText.append(plainText[i] + 13)\n";
        str += "      else\n";
        str += "        cipherText.append(plainText[i] - 13);\n";
        str += "   cipherText = password[0] + cipherText + password[password.length() -1];\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += "   plainText\n";
        str += "   cipherText = cipherText.substr(cipherText.size() - 2);\n";
        str += "   FOR i = 0 to size of cipherText\n";
        str += "      if cipherText.tolower(i)\n";
        str += "        plainText.append(plainText[i] + 13)\n";
        str += "      else\n";
        str += "        plainText.append(plainText[i] - 13);\n";
        str += "   RETURN plainText\n\n";

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

        for (int i = 0; i < plainText.length(); ++i) {
            if (tolower(plainText[i])) {
                if ((tolower(plainText[i]) - 'a') < 14)
                    cipherText.append(1, plainText[i] + 13);
                else
                    cipherText.append(1, plainText[i] - 13);
            }
            else {
                cipherText.append(1, plainText[i]);
            }
        }
        cipherText = password[0] + cipherText + password[password.length() - 1];

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

        if ((password[0] == cipherText[0]) && (password.back() == cipherText.back())) {

            std::string cipherText2 = cipherText.substr(1, cipherText.size() - 2);
            std::cout << cipherText2;

            for (int i = 0; i < cipherText2.size(); ++i) {
                if (tolower(cipherText2[i])) {
                    if ((tolower(cipherText2[i]) - 'a') < 13)
                        plainText.append(1, cipherText2[i] + 13);
                    else
                        plainText.append(1, cipherText2[i] - 13);
                }
                else {
                    plainText.append(1, cipherText2[i]);
                }
            }
        }
        return plainText;
    }
};

#endif // CIPHER02_H
