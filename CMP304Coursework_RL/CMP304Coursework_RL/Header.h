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

	item item1[TOTAL_ITEM_NUM];
	int numOfStates = 0;

	void setUpItems();
	void calcNumOfStates();
	int calcFactorial(int i);

private:
	
};

application::application()
{
	//item1[0].name = "Shirt";
	//item1[0].tags = Apparel;

	//item1[1].name = "Keyboard";
	//item1[1].tags = Computing;

	//item1[2].name = "Ring";
	//item1[2].tags = Jewellery;

	//item1[3].name = "Shovel";
	//item1[3].tags = Gardening;
}

application::~application()
{
}

inline void application::setUpItems()
{
	if (TOTAL_ITEM_NUM == 4)
	{
		item1[0].name = "Shirt";
		item1[0].tags = Apparel;

		item1[1].name = "Keyboard";
		item1[1].tags = Computing;

		item1[2].name = "Ring";
		item1[2].tags = Jewellery;

		item1[3].name = "Shovel";
		item1[3].tags = Gardening;
	}

	if (TOTAL_ITEM_NUM == 8)
	{
		item1[0].name = "Shirt";
		item1[0].tags = Apparel;

		item1[1].name = "Jeans";
		item1[1].tags = Apparel;

		item1[2].name = "Keyboard";
		item1[2].tags = Computing;

		item1[3].name = "Mouse";
		item1[3].tags = Computing;

		item1[4].name = "Ring";
		item1[4].tags = Jewellery;

		item1[5].name = "Earrings";
		item1[5].tags = Jewellery;

		item1[6].name = "Shovel";
		item1[6].tags = Gardening;

		item1[7].name = "Garden Seeds";
		item1[7].tags = Gardening;
	}
}

inline int application::calcFactorial(int i)
{
	int factNum = i;
	for (int j = 1; j < i; j++)
		factNum *= j;

	std::cout << "factorial: " << factNum << "\n";

	return factNum;
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

