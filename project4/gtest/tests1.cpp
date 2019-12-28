#include "gtest/gtest.h"
#include "Wordset.hpp"
#include "proj4.hpp"
#include <string>
#include <fstream>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.


TEST(HashFunctionTest, Hf1)
{
	int hv = hashFunction("dbc", 37, 100000);
	int shouldBe = 3*37*37 + 1*37 + 2;
	EXPECT_TRUE(hv == shouldBe);
}


TEST(TableTest, Tab1)
{
	WordSet ws;
	ws.insert("dbc");
	EXPECT_TRUE(ws.contains("dbc"));
}

TEST(ResizeTest, Tab2)
{
	WordSet ws;
	ws.insert("sleepy");
	ws.insert("happy");
	EXPECT_TRUE(ws.getCapacity() == 11);
	ws.insert("dopey");
	EXPECT_TRUE(ws.getCapacity() == 23);
	ws.insert("sneezy");
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	EXPECT_TRUE(ws.contains("happy"));
	EXPECT_TRUE(ws.contains("dopey"));
	// 23
}


TEST(ResizeTest, Tab3)
{
	WordSet ws;
	ws.insert("sleepy");
	ws.insert("happy");
	EXPECT_TRUE(ws.getCapacity() == 11);
	ws.insert("dopey");
	ws.insert("sneezy");
	EXPECT_TRUE(ws.getCapacity() == 23);
	ws.insert("datalink");
	ws.insert("australia");
	ws.insert("guacamole");
	ws.insert("phylum");
	EXPECT_TRUE(ws.contains("happy"));
	EXPECT_TRUE(ws.contains("dopey"));
	ws.insert("one");
	ws.insert("two");
	ws.insert("three");
	ws.insert("four");
	ws.insert("five");
	EXPECT_TRUE(ws.getCapacity() == 83);
}

TEST(SampleTest, Abandoning)
{
	WordSet words;
	words.insert("abandoning");
	EXPECT_TRUE(words.contains("abandoning"));
}


TEST(ConvertWords, AntToArt)
{
	WordSet words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::string r = convert("ant", "art", words);
 	EXPECT_TRUE(r == "ant --> art");
}



TEST(ConvertWords, AntToEat)
{
	WordSet words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);

 	std::string r = convert("ant", "eat", words);
 	EXPECT_TRUE(r == "ant --> aft --> oft --> oat --> eat");
 	// of course, if yours outputs a way to do this with exactly 5 words, it is also correct.
 	// So maybe confirm if yours is right or not if this test appears to be failing.
 	// I will be verifying it differently when I grade this assignment.
}






}