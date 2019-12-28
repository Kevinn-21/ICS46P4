#include "proj4.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l',
        'm','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    std::map<std::string,std::string> M;    //stores all one letter difference from previous word.
                                            //will have keys that have the same value.
                                            //Somewhat works like Breadth-First Search

    std::queue<std::string> Q;

    Q.push(s1);

    /*
        @lewisCarroll is the solution.
        @currWord stores the current word being looked at.
        @oneSubWord stores the a word one sub away from currWord.
    */
    std::string lewisCarroll, currWord, oneSubWord;

    while(!Q.empty())
    {
        currWord = Q.front();
        Q.pop();

        if(currWord == s2)
        {
            //produce path and return;
            std::string lewisCarrollPart = s2;
            while(lewisCarrollPart != s1)
            {
                lewisCarroll = " --> " + lewisCarrollPart + lewisCarroll;
                lewisCarrollPart = M[lewisCarrollPart];
            }
            lewisCarroll = s1 + lewisCarroll;
            return lewisCarroll;
        }
        else
        {

            for(int i=0; i<currWord.size(); i++)    //these loops makes all the strings one sub
            {                                       //away from current word being looked at
                for(int j=0; j<26; j++)
                {
                    oneSubWord = currWord;
                    oneSubWord[i] = alphabet[j];

                    if(words.contains(oneSubWord))  //check if its a word.
                    {

                        if(!M.count(oneSubWord))    //check if we've seen it before
                        {
                            M[oneSubWord] = currWord;
                            Q.push(oneSubWord);

                        }//end inner-if
                    }//end outer-if
                }
            }

        }//end else
    }
	return "zot zot zot";  // The above body of code should work, so...
	               //left for compiling reasons.
}
