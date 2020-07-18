/********************************************************************
* Header:
*    Implement your cipher here. You can view 'example.h' to see the
*    completed Caesar Cipher example.
********************************************************************/
#ifndef CIPHER03_H
#define CIPHER03_H

/********************************************************************
 * CLASS
 *******************************************************************/
class Cipher03 : public Cipher
{

public:
    virtual std::string getPseudoAuth() { return "Sam Wirthlin"; }
    virtual std::string getCipherName() { return "Rail-Fence Cipher"; }
    virtual std::string getEncryptAuth() { return "Herman Kravchenko"; }
    virtual std::string getDecryptAuth() { return "Coleen Hull"; }

    /***********************************************************
     * GET CIPHER CITATION
     * Returns the citation from which we learned about the cipher
     ***********************************************************/
    virtual std::string getCipherCitation()
    {
       std::string str;
       str += "return std::string(Helen Fouché Gaines, Cryptanalysis,";
       str += " a study of ciphers and their solution, Dover, 1956, ISBN 0 - 486 - 20097 - 3)";
    }

    /**********;************************************************
     * GET PSEUDOCODE
     * Returns the pseudocode as a string to be used by the caller.
     **********************************************************/
    virtual std::string getPseudocode()
    {
        std::string str;

        // TODO: please format your pseudocode
        // The encrypt pseudocode
        str = "encrypt(plainText, password)\n";
        str += "   key <- password size\n";
        str += "   FOR i = 0; i < size of key\n";
        str += "      FOR c = 0; c < plainText size\n";
        str += "         fill rail with end line character at rail[i][c]\n";
        str += "      bool direciton is false\n";
        str += "   FOR i = 0; i < plainText size\n";
        str += "      IF row is 0 OR row is key - 1\n";
        str += "         swap the direction\n";
        str += "         fill rail at [row][col++] with plainText\n";
        str += "         find the next direction using row++ and row--\n";
        str += "   FOR i = 0; i < size of key\n";
        str += "      FOR c = 0; c < plainText size\n";
        str += "         IF rail position ([i][c]) does not equal an end line\n";
        str += "            fill cipherText with rail at position [i][c]\n";
        str += "   RETURN cipherText\n\n";

        // The decrypt pseudocode
        str += "decrypt(cipherText, password)\n";
        str += "   FOR i = 0; i < size of key\n";
        str += "      FOR c = 0; c < cipherText size\n";
        str += "         fill rail with end line character at rail[i][c]\n";
        str += "   FOR i = 0; i < cipherText size\n";
        str += "      IF row is 0\n";
        str += "         set direction to up (true)\n";
        str += "      IF row is key - 1\n";
        str += "         set direction to down (false)\n";
        str += "      fill rail at [row][col++] with \'*\'\n";
        str += "      find the next direction using row++ and row--\n";
        str += "   FOR i = 0; i < size of key\n";
        str += "      FOR c = 0; c < cipherText size\n";
        str += "         IF rail position ([i][c]) equals a \'*\' character\n";
        str += "          AND the index(starting at 0) is less than the cipherText length\n";
        str += "            fill the rail at [i][c] with the cipherText at position [index++]\n";
        str += "         find the next direction using row++ and row--\n";
        str += "   RETURN plainText\n\n";

        return str;
    }


    /**********************************************************
     * ENCRYPT
     * TODO: This is a transposition encryption that uses a key
     * as the spaces between characters. This is a very simple
     * transposition cipher that does not change letters.
     **********************************************************/
    virtual std::string encrypt(const std::string& plainText,
        const std::string& password)
    {

        std::string cipherText = "";
        int key = password.size(); // Get key from password size
        char rail[key][(plainText.length())];

        for (int i = 0; i < key; i++)
            for (int c = 0; c < plainText.length(); c++)
                rail[i][c] = '\n';

        bool dir_down = false; // Decide direction for rail
        int row = 0;
        int col = 0;

        for (int i = 0; i < plainText.length(); i++)
        {
            if (row == 0 || row == key - 1)
                dir_down = !dir_down; // Swap the direction if at the bottom or top

            // Fill the corresponding alphabet 
            rail[row][col++] = plainText[i];

            // Find the next row using direction flag 
            dir_down ? row++ : row--;
        }

        for (int i = 0; i < key; i++)
            for (int c = 0; c < plainText.length(); c++)
                if (rail[i][c] != '\n')
                    cipherText.push_back(rail[i][c]);

        return cipherText;
    }

    /**********************************************************
     * DECRYPT
     * TODO: To decrypt this cihper we need to first fill, the
     * rail based on the key with '*' then wherever there is an
     * '*' character we know to put a letter from the cipher.
     **********************************************************/
    virtual std::string decrypt(const std::string& cipherText,
        const std::string& password)
    {
        std::string plainText = "";
        int key = password.size();
        char rail[key][cipherText.length()];

        for (int i = 0; i < key; i++) // Fill the rail to distinguish filled from blank spaces
            for (int c = 0; c < cipherText.length(); c++)
                rail[i][c] = '\n';

        bool dir_down;
        int row = 0;
        int col = 0;

        for (int i = 0; i < cipherText.length(); i++) // Mark all letter places with *
        {
            // Get direction of flow 
            if (row == 0)
                dir_down = true;
            if (row == key - 1)
                dir_down = false;

            rail[row][col++] = '*';

            // Find the next direction 
            dir_down ? row++ : row--;
        }

        int index = 0;
        for (int i = 0; i < key; i++) // Construct the fill matrix
            for (int c = 0; c < cipherText.length(); c++)
                if (rail[i][c] == '*' && index < cipherText.length())
                    rail[i][c] = cipherText[index++];

        row = 0;
        col = 0;
        for (int i = 0; i < cipherText.length(); i++)
        {
            // Check direction of flow 
            if (row == 0)
                dir_down = true;
            if (row == key - 1)
                dir_down = false;

            // Fill 
            if (rail[row][col] != '*')
                plainText.push_back(rail[row][col++]);

            // Figure out next direction of rail 
            dir_down ? row++ : row--;
        }

        return plainText;
    }

};

#endif // CIPHER03_H
