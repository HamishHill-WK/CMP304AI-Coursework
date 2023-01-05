#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <chrono>
#include <fstream>

#define TOTAL_ITEM_NUM 16 //can be set to 4, 8, 12 or 16. Restricted to these values as new items must be added manually into the system
#define ITEMS_VISIBLE 3

enum tag { NoTag = 0, Apparel, Computing, Jewellery, Gardening, Sport};
static const char* EnumStrings[] = { "NoTag" , "Apparel", "Computing", "Jewellery", "Gardening", "Sport" };

struct item
{
	std::string name = "itemName";
	tag tags = NoTag;
};

class application
{
public:
	application();

	std::vector<item> item1;	//vector of items
	std::vector<std::vector<int>> combinationCodes;	//vector containing sets of items 
	std::vector<int> combin;
	std::vector<int> itemID;	//each item within the program has a unique int value to identify it with

	void createCombinations(int offset, int k);
	const char* getTextForEnum(int i);
	int getCombination(const std::vector<float>& Q1);

	float estimateReward(tag interest1, item chosenItem);
	float calcReward(tag interest1, item chosenItem, int satisfaction);
};

application::application() //initialize list of items. Changes depening on what TOTAL_ITEM_NUM has been set as in the header file. 
{
	for (int i = 0; i < TOTAL_ITEM_NUM; ++i)
		itemID.push_back(i);

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

	if (TOTAL_ITEM_NUM == 16)
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

		item1.at(10).name = "Garden-Seeds";
		item1.at(10).tags = Gardening;

		item1.at(11).name = "Hoe";
		item1.at(11).tags = Gardening;

		item1.at(12).name = "Football";
		item1.at(12).tags = Sport;

		item1.at(13).name = "Weight-set";
		item1.at(13).tags = Sport;

		item1.at(14).name = "Golf-club";
		item1.at(14).tags = Sport;

		item1.at(15).name = "Basketball";
		item1.at(15).tags = Sport;
	}
}

void application::createCombinations(int offset, int i)	//this function creates a vector containing all possible (non-repeating) combinations of itemIDs.
{														
	if (i == 0) {
		combinationCodes.push_back(combin);
		return;
	}

	for (int j = offset; j <= TOTAL_ITEM_NUM- i; ++j) {
		combin.push_back(itemID[j]);
		createCombinations(j + 1, i - 1);
		combin.pop_back();
	}
}

inline const char* application::getTextForEnum(int i)
{
	return EnumStrings[i];
}

int application::getCombination(const std::vector<float>& Q1)	//return combination to display
{
	float currentMax = *std::max_element(std::begin(Q1), std::end(Q1));	//find greatest weighting in Q matrix

	std::vector<int> maxElems;	//vector containing all "high value" combinations. 
									
	for (int i = 0; i < Q1.size(); i++)	
		if (Q1.at(i) >= (currentMax - 0.25f))	//"high value" combinations are sets of items within a certain range of the maximum value. 
			maxElems.push_back(i);				//There is a slight tolerance of .25f under the maximum value when finding all "high value" combinations so -
												//that the vector is not only full of combinations which are equal to the exact maximum.

	//for (int i = 0; i < maxElems.size(); i++)
		std::cout << "high value combinations: " << maxElems.size() << std::endl;

	int random, action = 0;

	random = rand() % 100;	

	if (random >= 20)
	{
		std::random_shuffle(maxElems.begin(), maxElems.end());	//list of "high value" combinations is shuffled.
																//this is done so that the program does not only recommend the highest weight combination everytime.
		action = *maxElems.begin();

		return action;
	}

	if (random < 20) // 20% chance to give the user a random combination of items
	{
		std::cout << "--Random recommendation--" << std::endl;

		action = rand() % combinationCodes.size();

		return action;
	}
}


inline float application::estimateReward(tag interest1, item chosenItem)	//function used to give a small amount of bias towards items within the user's stated interest.
{
	if (chosenItem.tags == interest1)
		return 0.2f;

	else
		return 0.0f;
}

inline float application::calcReward(tag interest1, item chosenItem, int satisfaction)	//function for calculating reward
{
	if (satisfaction == NULL)	//if satisfaction is null then the user has selected no items 
	{
		if (interest1 == chosenItem.tags)
			return -1.0f;

		if (interest1 != chosenItem.tags)
			return -1.5f;
	}

	if (satisfaction >= 4)	//if the user is satisfied give greater reward
	{
		if (interest1 == chosenItem.tags)	//greater reward is given towards items of the user's preffered interest
			return 1.5f;

		if (interest1 != chosenItem.tags)
			return 1.0f;
	}

	if (satisfaction <= 1)	//if the user is unsatified give a negative reward
	{
		if (interest1 == chosenItem.tags)	//a lesser negative is rewarded to items of the user's preffered interest 
			return -1.0f;

		if (interest1 != chosenItem.tags)
			return -1.5f;
	}

	if (satisfaction <= 3)	//if the user is neither fully satisfied or unsatisfied give a small positive reward
	{
		if (interest1 == chosenItem.tags)
			return 0.75f;

		if (interest1 != chosenItem.tags)
			return 0.5f;
	}
}