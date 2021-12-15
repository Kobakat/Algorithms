#include <iostream>

//This implementation is only going to use lowercase ANSI char values
//If we wanted to change that we would need to alter these values
//For example, 52 would enable capital letters but would require us to change
//START_CHAR to 'A'. We would also have to deal with chars between upper/lower cases
//probably by parsing our key string and removing them
#define CHAR_LIMIT 26
#define START_CHAR 'a'

struct TrieNode
{
    TrieNode* children[CHAR_LIMIT];

    bool isTail;

    TrieNode()
    {
        //We choose to maintain a bool here because determing if the node is an end node otherwise would require us
        //to iterate over every node in children and verify they are null. This would be incredibly slow
        //There is a memory 
        isTail = false;

        for (int i = 0; i < CHAR_LIMIT; i++)
        {
            this->children[i] = nullptr;
        }
    }

    ~TrieNode()
    {
        //This will cleanup any child nodes which will subsequently clean up their children
        for (int i = 0; i < CHAR_LIMIT; i++)
        {
            if (children[i] != nullptr)
            {
                delete children[i];
            }
        }
    }

    void Insert(std::string key)
    {
        TrieNode* current = this;

        for (int i = 0; i < key.length(); i++)
        {
            //We need to account for the fact that 'a' does not evaluate to 0, but rather the integral ANSI number which is 97
            //This would of course throw an access exception because our array is sized to 26!
            int correctedIndex = key[i] - START_CHAR;

            //If this letter's node has yet to be populated we create a new one
            if (current->children[correctedIndex] == nullptr)
            {
                current->children[correctedIndex] = new TrieNode();
            }

            // go to the next node
            current = current->children[correctedIndex];
        }

        current->isTail = true;
    }

    bool Search(std::string key)
    {
        TrieNode* current = this;

        for (int i = 0; i < key.length(); i++)
        {
            int correctedIndex = key[i] - START_CHAR;

            //If at any point the next character is missing from our key string, we know this string cannot exist
            if (current->children[correctedIndex] == nullptr)
            {
                return false;
            }

            //Continue to the next element
            current = current->children[correctedIndex];
        }

        //We have reached the end of the string and are not missing any charcters which means this string does exist
        return true;
    }
};

int main()
{
    TrieNode* root = new TrieNode();

    root->Insert("hello");

    std::cout << (root->Search("hello") ? "True" : "False") << std::endl; //should be true since we added this
    std::cout << (root->Search("hel") ? "True" : "False") << std::endl; //should be true because hello is comprised of hello
    std::cout << (root->Search("greetings") ? "True" : "False") << std::endl; //should be false we did not insert this key

    delete root;
    return 0;
}
