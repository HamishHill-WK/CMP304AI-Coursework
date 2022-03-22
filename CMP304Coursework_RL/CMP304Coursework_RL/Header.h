#pragma once
#include <array>
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define ACTION_NUM 3
#define STATE_NUM 3
#define TOTAL_ITEM_NUM 8
#define ITEMS_VISIBLE 3

enum tag { NoTag = 0, Apparel, Computing, Jewellery, Gardening};
static const char* EnumStrings[] = { "NoTag" , "Apparel", "Computing", "Jewellery", "Gardening"};

struct item
{
	std::string name = "itemName";
	tag tags = NoTag;
};

class application
{
public:
	application();
	~application();

	std::vector<item> item1;
	std::vector<std::vector<int>> combinationCodes;
	std::vector<int> combination;
	std::vector<int> itemID;
	int numOfStates = 0;

	void setUpItems();
	void calcNumOfStates();
	int calcFactorial(int i);
	void createCombinations(int offset, int k);
	const char* getTextForEnum(int enumVal);

private:
	
};

application::application()
{

}

application::~application()
{
}

inline void application::setUpItems()
{
	for (int i = 0; i < TOTAL_ITEM_NUM; ++i)
		itemID.push_back(i );

	item1.resize(TOTAL_ITEM_NUM);

	if (TOTAL_ITEM_NUM == 4)
	{
		item1.at(0).name = "Shirt";
		item1.at(0).tags = Apparel;

		item1.at(1).name = "Keyboard";
		item1.at(1).tags = Computing;

		item1.at(2).name = "Ring";
		item1.at(2).tags = Jewellery;

		item1.at(3).name = "Shovel";
		item1.at(3).tags = Gardening;
	}

	if (TOTAL_ITEM_NUM == 8)
	{
		//apparel
		item1.at(0).name = "Shirt";
		item1.at(0).tags = Apparel;

		item1.at(1).name = "Jeans";
		item1.at(1).tags = Apparel;

		//computing
		item1.at(2).name = "Keyboard";
		item1.at(2).tags = Computing;

		item1.at(3).name = "Mouse";
		item1.at(3).tags = Computing;

		//jewellery
		item1.at(4).name = "Ring";
		item1.at(4).tags = Jewellery;

		item1.at(5).name = "Earrings";
		item1.at(5).tags = Jewellery;

		//gardening
		item1.at(6).name = "Shovel";
		item1.at(6).tags = Gardening;

		item1.at(7).name = "Garden Seeds";
		item1.at(7).tags = Gardening;
	}	
	
	if (TOTAL_ITEM_NUM == 12)
	{
		//apparel
		item1.at(0).name = "Shirt";
		item1.at(0).tags = Apparel;

		item1.at(1).name = "Jeans";
		item1.at(1).tags = Apparel;		
		
		item1.at(2).name = "Shoes";
		item1.at(2).tags = Apparel;

		item1.at(3).name = "Keyboard";
		item1.at(3).tags = Computing;

		item1.at(4).name = "Mouse";
		item1.at(4).tags = Computing;

		item1.at(5).name = "RAM sticks";
		item1.at(5).tags = Computing;

		item1.at(6).name = "Earrings";
		item1.at(6).tags = Jewellery;

		item1.at(7).name = "Ring";
		item1.at(7).tags = Jewellery;

		item1.at(8).name = "Necklace";
		item1.at(8).tags = Jewellery;

		item1.at(9).name = "Shovel";
		item1.at(9).tags = Gardening;

		item1.at(10).name = "Garden Seeds";
		item1.at(10).tags = Gardening;

		item1.at(11).name = "Hoe";
		item1.at(11).tags = Gardening;
	}
}

inline int application::calcFactorial(int i)
{
	int factNum = i;
	for (int j = 1; j < i; j++)
		factNum *= j;

	//std::cout << "factorial: " << factNum << "\n";

	return factNum;
}

inline void application::createCombinations(int offset, int i)
{
	if (i == 0) {
		combinationCodes.push_back(combination);
		return;
	}
	for (int j = offset; j <= TOTAL_ITEM_NUM- i; ++j) {
		combination.push_back(itemID[j]);
		createCombinations(j + 1, i - 1);
		combination.pop_back();
	}
}

inline const char* application::getTextForEnum(int enumVal)
{
	return EnumStrings[enumVal];
}

inline void application::calcNumOfStates()
{
	//combination calculation in order to determine the number of states
	// C(n,r) = n!/(r!(n-r)!)  
	// ! is a factiorial
	// n = total number of items
	// r = size of selection 

	int totatlFact = calcFactorial(TOTAL_ITEM_NUM);
	int selectionFact = calcFactorial(ITEMS_VISIBLE);
	int differenceFact = calcFactorial(TOTAL_ITEM_NUM - ITEMS_VISIBLE);

	numOfStates = totatlFact / (selectionFact * differenceFact);
	std::cout << "num of states: " << numOfStates << "\n";
}

