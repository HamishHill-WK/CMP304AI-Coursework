#include "Header.h"
using namespace std::chrono_literals;

application app;

void pretty_print(const std::vector<float>& v) {
	static int count = 0;
	std::cout << "combination no " << (++count) << ": [ ";
	for (int i = 0; i < v.size(); ++i) { std::cout << v[i] << " "; }
	std::cout << "] " << std::endl;
}

void pretty_print1(const std::vector<int>& v) {
	static int count = 0;
	std::cout << "combination no " << (++count) << ": [ ";
	for (int i = 0; i < v.size(); ++i) { std::cout << v[i] << " "; }
	std::cout << "] " << std::endl;
}

float calcReward(tag interest1, item chosenItem, int satisfaction)
{
	if (satisfaction >= 3)
	{
		if (interest1 == chosenItem.tags)
			return 5.0f;

		if (interest1 != chosenItem.tags)
			return 1.0f;
	}

	if (satisfaction == 1)
	{
		if (interest1 == chosenItem.tags)
			return -1.0f;

		if (interest1 != chosenItem.tags)
			return -5.0f;
	}


	if (satisfaction < 3)
	{
		if (interest1 == chosenItem.tags)
			return 2.0f;

		if (interest1 != chosenItem.tags)
			return 0.0f;
	}

}

int main()
{
	srand(time(NULL));

	app.setUpItems();
	app.calcNumOfStates();
	app.createCombinations(0, ITEMS_VISIBLE);
	tag interest = NoTag;

	int states = 0;
	states = app.numOfStates;

	std::vector<std::vector<float>> Q;
	Q.resize(states);
	for (int i = 0; i < states; i++)
		Q[i].resize(ITEMS_VISIBLE);

	bool running = true;
	int input = 0;

	std::cout << "please enter your main interest from: Apparel(1), Computing(2), Jewellery(3), Gardening(4)" << std::endl;
	std::cin >> input;

	if (input == 1)
		interest = Apparel;	
	
	if (input == 2)
		interest = Computing;	
	
	if (input == 3)
		interest = Jewellery;	
	
	if (input == 4)
		interest = Gardening;

	for (int i = 0; i < states; i++)	//add bias towards the user's prefferred interest at start 
	{
		if(app.item1.at(app.combinationCodes.at(i).at(0)).tags == interest)
			Q.at(i).at(0) += 1.0f;

		if (app.item1.at(app.combinationCodes.at(i).at(1)).tags == interest)
			Q.at(i).at(1) += 1.0f;

		if (app.item1.at(app.combinationCodes.at(i).at(2)).tags == interest)
			Q.at(i).at(2) += 1.0f;
	}

	for (int i = 0; i < states; i++)
		pretty_print(Q.at(i));

	while (running)
	{
		int x = rand() % (TOTAL_ITEM_NUM * ITEMS_VISIBLE);
		std::cout << app.item1.at(app.combinationCodes.at(x).at(0)).name << " " << app.item1.at(app.combinationCodes.at(x).at(1)).name << " " << app.item1.at(app.combinationCodes.at(x).at(2)).name << "\n";

		input = 0;
		int satisfaction = 0;
		float reward = 0;
		std::cin >> input;

		if (input == 1)
		{
			std::cout << "are you happy with this item ?: " << app.item1.at(app.combinationCodes.at(x).at(0)).name
				<< " tags: " << app.getTextForEnum(app.item1.at(app.combinationCodes.at(x).at(0)).tags) << "\n";

			std::cin >> satisfaction;
			reward = calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(0)), satisfaction);
			//Q.at(x).at(0) = reward; 
			for (int i = 0; i < states; i++)	//update weighting for each instance of this item in vector of items
			{
				if (app.combinationCodes.at(i).at(0) == app.combinationCodes.at(x).at(0))
					Q.at(i).at(0) += reward;

				if (app.combinationCodes.at(i).at(0) == app.combinationCodes.at(x).at(1))
					Q.at(i).at(1) += reward;

				if (app.combinationCodes.at(i).at(0) == app.combinationCodes.at(x).at(2))
					Q.at(i).at(2) += reward;
			}
		}

		if (input == 2)
		{
			std::cout << "are you happy with this item ?: " << app.item1.at(app.combinationCodes.at(x).at(1)).name
				<< " tags: " << app.item1.at(app.combinationCodes.at(x).at(1)).tags << "\n";

			std::cin >> satisfaction;
			reward = calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(1)), satisfaction);

			for (int i = 0; i < states; i++)
			{
				if (app.combinationCodes.at(i).at(1) == app.combinationCodes.at(x).at(0))
					Q.at(i).at(0) += reward;

				if (app.combinationCodes.at(i).at(1) == app.combinationCodes.at(x).at(1))
					Q.at(i).at(1) += reward;

				if (app.combinationCodes.at(i).at(1) == app.combinationCodes.at(x).at(2))
					Q.at(i).at(2) += reward;
			}
		}
		
		if (input == 3)
		{
			//std::string tag = app.item1.at(app.combinationCodes.at(x).at(2)).tags;
			std::cout << "are you happy with this item? Please rate from 1 to 5. Item: " << app.item1.at(app.combinationCodes.at(x).at(2)).name
				<< " tags: " << app.item1.at(app.combinationCodes.at(x).at(2)).tags << "\n";

			std::cin >> satisfaction;
			reward = calcReward(interest, app.item1.at(app.combinationCodes.at(x).at(2)), satisfaction);

			for (int i = 0; i < states; i++)
			{
				if (app.combinationCodes.at(i).at(2) == app.combinationCodes.at(x).at(0))
					Q.at(i).at(0) += reward;

				if (app.combinationCodes.at(i).at(2) == app.combinationCodes.at(x).at(1))
					Q.at(i).at(1) += reward;

				if (app.combinationCodes.at(i).at(2) == app.combinationCodes.at(x).at(2))
					Q.at(i).at(2) += reward;
			}
		}

		if (input == 4)
			running = false;

	}

	for(int i = 0; i < states; i++)
	pretty_print(Q.at(i));	
	
	for(int i = 0; i < states; i++)
	pretty_print1(app.combinationCodes.at(i));

	// Calculate Reward
	// TODO: Calculate the reward you want to give to the AI
	//reward = calcReward(currentState, chosen_action);
	//Q[currentState][chosen_action] = Q[currentState][chosen_action] + (learningRate * (reward + (discountFactor * maxQ) - Q[currentState][chosen_action]));

	std::cin.get();
}