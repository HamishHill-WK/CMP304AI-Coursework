#include "Header.h"
using namespace std::chrono_literals;

application app;

int main()
{
	srand(time(NULL));

	app.setUpItems();
	app.calcNumOfStates();
	app.createCombinations(0, ITEMS_VISIBLE);
	tag interest = NoTag;

	int states = 0;

	states = app.numOfStates;

	float learningRate = .1f;
	float discountFactor = 0.25f;
	float maxQ = 5.0f;

	std::vector<std::vector<float>> Q;	//q matrix for each individual item
	Q.resize(states);
	for (int i = 0; i < states; i++)
		Q[i].resize(ITEMS_VISIBLE);

	std::vector<float> QSum;	//q matrix for each combination of items. 
	QSum.resize(states);

	int input = 0;
	std::cout << "--WELCOME TO HILLMART--" << std::endl;
	std::cout << "WE HOPE YOU ENJOY SHOPPING WITH US TODAY" << std::endl;

	if(TOTAL_ITEM_NUM < 16)
		std::cout << "Please enter your main interest from our selection using the number keys.\nApparel(1), Computing(2), Jewellery(3), Gardening(4)" << std::endl;

	if (TOTAL_ITEM_NUM == 16)
		std::cout << "Please enter your main interest from our selection using the number keys.\nApparel(1), Computing(2), Jewellery(3), Gardening(4), Sport(5)" << std::endl;

	std::cin >> input;

	if (input == 1)
		interest = Apparel;	
	
	if (input == 2)
		interest = Computing;	
	
	if (input == 3)
		interest = Jewellery;	
	
	if (input == 4)
		interest = Gardening;	
	
	if (input == 5)
		interest = Sport;

	for(int i = 0; i < states; i++)
		for(int j =0; j < ITEMS_VISIBLE; j++)
			Q.at(i).at(j) = app.estimateReward(interest, app.item1.at(app.combinationCodes.at(i).at(j)));	//this adds a small bias to items within the user's stated preference

	bool running = true;
	int x = 0;

	while (running)
	{
		for (int i = 0; i < states; i++)	//update Qsum
			QSum.at(i) = (Q.at(i).at(0) + Q.at(i).at(1) + Q.at(i).at(2));

		std::cout << "---------------------" << std::endl;
		//x = rand() % (TOTAL_ITEM_NUM * ITEMS_VISIBLE);
		x = app.getCombination(QSum);

		if (ITEMS_VISIBLE == 3)
		{
			std::cout << "Please select which item you are interested in using the number keys 1, 2 or 3.\nIf none of the items appeal to you, enter 9 to refresh.\nEnter 0 when you are done shopping." << std::endl;
			std::cout << "Item 1: " << app.item1.at(app.combinationCodes.at(x).at(0)).name << "\nItem 2: "
				<< app.item1.at(app.combinationCodes.at(x).at(1)).name << "\nItem 3: " << app.item1.at(app.combinationCodes.at(x).at(2)).name << "\n";

			input = 0;
			int satisfaction = 0;
			float reward = 0;
			std::cin >> input;

			std::cout << "Thank you for your selection" << std::endl;

			if (input == 1)
			{
				std::cout << "Are you happy with this item? Please rate from 1 to 5.\nItem: " << app.item1.at(app.combinationCodes.at(x).at(0)).name
					<< " tags: " << app.getTextForEnum(app.item1.at(app.combinationCodes.at(x).at(0)).tags) << "\n";

				std::cin >> satisfaction;
				reward = app.calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(0)), satisfaction);

				for (int i = 0; i < states; i++)	//update weighting for each instance of this item in vector of items
					for (int j = 0; j < ITEMS_VISIBLE; j++)
						if (app.combinationCodes.at(i).at(j) == app.combinationCodes.at(x).at(0))
							Q.at(i).at(j) = Q.at(i).at(j) + (learningRate * (reward + (discountFactor * maxQ) - Q.at(i).at(j)));
			}

			if (input == 2)
			{
				std::cout << "are you happy with this item? Please rate from 1 to 5.\nItem: " << app.item1.at(app.combinationCodes.at(x).at(1)).name
					<< " tags: " << app.getTextForEnum(app.item1.at(app.combinationCodes.at(x).at(1)).tags) << "\n";

				std::cin >> satisfaction;
				reward = app.calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(1)), satisfaction);

				for (int i = 0; i < states; i++) //update weighting for each instance of this item in vector of items
					for (int j = 0; j < ITEMS_VISIBLE; j++)
						if (app.combinationCodes.at(i).at(j) == app.combinationCodes.at(x).at(1))
							Q.at(i).at(j) = Q.at(i).at(j) + (learningRate * (reward + (discountFactor * maxQ) - Q.at(i).at(j)));

			}

			if (input == 3)
			{
				std::cout << "are you happy with this item? Please rate from 1 to 5.\nItem: " << app.item1.at(app.combinationCodes.at(x).at(2)).name
					<< " tags: " << app.getTextForEnum(app.item1.at(app.combinationCodes.at(x).at(2)).tags) << "\n";

				std::cin >> satisfaction;
				reward = app.calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(2)), satisfaction);

				for (int i = 0; i < states; i++) //update weighting for each instance of this item in vector of items
					for (int j = 0; j < ITEMS_VISIBLE; j++)
						if (app.combinationCodes.at(i).at(j) == app.combinationCodes.at(x).at(2))
							Q.at(i).at(j) = Q.at(i).at(j) + (learningRate * (reward + (discountFactor * maxQ) - Q.at(i).at(j)));
			}
		}

		if (input == 9)
		{
			std::cout << "No item selected\n";
			float reward = 0;
			//std::cin >> satisfaction;
			for(int i = 0; i < ITEMS_VISIBLE; i++)
				reward += app.calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(i)), NULL);

			for (int i = 0; i < states; i++) //update weighting for each instance of this item in vector of items
				for (int j = 0; j < ITEMS_VISIBLE; j++)
					if (app.combinationCodes.at(i).at(j) == app.combinationCodes.at(x).at(2))
						Q.at(i).at(j) = Q.at(i).at(j) + (learningRate * (reward + (discountFactor * maxQ) - Q.at(i).at(j)));
			continue;
		}

		if (input == 0)
			running = false;
	}

	for(int i = 0; i < states; i++)
		app.vFloatPrint(Q.at(i));	

	//for (int i = 0; i < states; i++)
	app.vFloatPrint(QSum);
	
	for(int i = 0; i < states; i++)
		app.vIntPrint(app.combinationCodes.at(i));

	std::cin.get();
}