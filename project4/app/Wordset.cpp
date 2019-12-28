#include "Wordset.hpp"
#include <string>

const int BASE_TO_USE = 37;
const double LOAD_LIMIT = 0.25;

// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
    int hash;
    unsigned long key=0;    //holds individual letter's digit value
    for(int i=0; i<s.length(); i++)
    {

        int oneLet = s[i] - 'a';    //returns digit value of that letter
        int pow = s.length()-i-1;

        unsigned long partKey=oneLet;
        for(int i=0; i<pow; i++)
        {
            partKey *= base;
        }
        key += partKey;

    }   //end outer for-loop

    hash = key % mod;
    return hash;
}


WordSet::WordSet()
{
    m = 0;  //array-size
    A = new std::string[ SIZES[m] ];
    count = 0;  //number of strings
}

WordSet::~WordSet()
{
    delete[] A;
}

void WordSet::insert(std::string s)
{
    int hashKey = hashFunction(s, BASE_TO_USE, SIZES[m]);
    bool spotFound = false;

    /*
        Keep looping until we find an empty spot to put our string s into the hash table
    */
    for(int i=0; spotFound == false; i++)
    {
        int spot = (hashKey + i*i) % SIZES[m];

        if(A[spot] == s)
        {
            return;     //if the word is in the Hash Table, exit insert(s)
                        //No duplicates.
        }

        if(A[spot].empty())
        {   //place s here if empty
            A[spot] = s;
            spotFound = true;
            count++;
        }
    }//end inserting into A

    //check Load Factor, make a bigger Hash Table if over load factor
    double loadFactor = (double)count/SIZES[m];
    if( loadFactor > LOAD_LIMIT)
    {
        m++;
        std::string* biggerA = new std::string[ SIZES[m] ];
        count = 0;
        for(int i=0; i<SIZES[m-1]; i++)    //loop through to get each string
        {
            spotFound = false;

            if(!A[i].empty())   //if string is not empty, insert into biggerA
            {

                s = A[i];

                hashKey = hashFunction(s, BASE_TO_USE, SIZES[m]);
                for(int k=0; spotFound == false; k++)
                {
                    int spot = (hashKey + k*k) % SIZES[m];
                    if(biggerA[spot].empty())
                    {
                        biggerA[spot] = s;
                        spotFound = true;
                        count++;    //don't need to check for distinct strings because
                    }               //we are just moving the strings to the new array and
                                    //we already check for distinct strings before

                }   //end finding the spot

            }//end if-body that checks for empty
        }//end reinserting all the strings from old A

        delete[] A;     //the old, small Hash Table
        A = biggerA;
    }   //end checking Load Limit

}//End insert(s)

/*
    Checks to see if the strin is in the Hash Table
*/
bool WordSet::contains(std::string s) const
{
    int hash = hashFunction(s, BASE_TO_USE, SIZES[m]);
    bool spotFound = false;

    for(int i=0; spotFound == false; i++)
    {
        int spot = (hash + i*i) % SIZES[m];
        if(A[spot] == s)
        {
            spotFound = true;
            return true;
        }
        else if(A[spot].empty())    //This checks for a spot that is not filled where the string could've gone.
        {                           //Which means the string is not in the Hash Table because we already past all
                                    //of the indexes where it would've been. So I exit the loop-statement and return false.
            spotFound = true;
        }
    }
	return false;
}   //end contains(s)

// return how many distinct strings are in the set
int WordSet::getCount() const
{
    return count;
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
    return SIZES[m];
}

