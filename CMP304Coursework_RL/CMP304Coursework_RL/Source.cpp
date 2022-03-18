#include "Header.h"
using namespace std::chrono_literals;

enum State { STABLE = 0, TOO_MUCH_PRESSURE, TOO_LITTLE_PRESSURE };
enum Action { WAIT = 0, ADD_WATER, RELEASE_WATER };

//std::array<std::array<float, ACTION_NUM>, STATE_NUM> Q = { {0} };
//std::array<std::string, ACTION_NUM> action_to_string = { "WAIT", "ADD WATER", "RELEASE WATER" };
//std::array<std::string, ACTION_NUM> state_to_string = { "STABLE", "TOO MUCH PRESSURE", "TOO LITTLE PRESSURE" };

application app;

std::array<item, TOTAL_ITEM_NUM> array_of_items;
std::array<item, ITEMS_VISIBLE> array_of_items_visible;

void printMatrix()
{
	using namespace std;
	cout << "Q Matrix" << endl << endl;
	for (int i = 0; i < STATE_NUM; i++)
	{
		for (int j = 0; j < ACTION_NUM; j++)
		{
			//cout << "For state \"" << state_to_string[i] << "\" the action \"" << action_to_string[j] << "\" has a value of: " << Q[i][j] << endl;
		}
	}
}

int action(State currentS)
{
	float bestV = Q[currentS][0];

	int random = 0;

	int action = 0;

	random = rand() % 100;

	for (int i = 0; i < ACTION_NUM; i++)
	{
		if (random >= 10)
			if (Q[currentS][i] > bestV)
			{
				std::cout << " ------------ " << std::endl;
				std::cout << " ?? NOT RANDOM ?? " << std::endl;
				std::cout << " ------------ " << std::endl;

				bestV = Q[currentS][i];
				action = i;
			}

		if (random < 10)
		{
			std::cout << " ------------ " << std::endl;
			std::cout << " @@ RANDOM @@ " << std::endl;
			std::cout << " ------------ " << std::endl;

			if (random <= 2)
				i = 0;

			if (random >= 7)
				i = 1;

			else
				i = 2;

			bestV = Q[currentS][i];
			action = i;
			break;
		}
	}

	std::cout << "bestV: " << bestV << std::endl;

	return action;
}



int main()
{
	srand(time(NULL));

	app.setUpItems();
	app.calcNumOfStates();

	int states = 0;
	states = app.numOfStates;
	item itemX, itemY, itemZ;

	//app.item1[0], app.item1[1], app.item1[2]
	std::vector<std::vector<float>> Q;
	Q.resize(states);
	for (int i = 0; i < states; i++)
		Q[i].resize(ITEMS_VISIBLE);

	float s = Q[0][0];

	std::vector<std::vector<item>> itemStates;// = { itemX, itemY, itemZ };
	itemStates.resize(states);

	for (int i = 0; i < states; i++)
	{
		for (int j = 0; j < TOTAL_ITEM_NUM; j++)
		{
			if (j < 7)
			{
				itemX = app.item1[j];
				itemY = app.item1[j + 1];
				itemZ = app.item1[j + 2];

			}
			itemStates.at(i+j) = { itemX, itemY, itemZ };
		}
		
	}
	 //state XYZ

	float system_pressure = 50.f;

	float learningRate = .1f;

	float discountFactor = 0.25f;

	float maxQ = 10.0f;

	int iterator = 0;

	int actionInt = 0;

	float reward = 0;

	float LM[3][3] = { {0} };


	Action chosen_action = WAIT;

	while (system_pressure > 0)
	{
		//std::cout << " ------------ " << std::endl;
		//std::cout << "System pressure is sitting at: " << system_pressure << "." << std::endl;
		//std::cout << " ------------ " << std::endl;

		// Describe State
		// TODO: Store a local variable that describes the current state
		//currentState = currentPressure(system_pressure);

		//actionInt = action(currentState);

		// Choose Action
		// TODO: Store a local variable that explains what action the AI will perform

		// Perform the Action
		// TODO: Implement the chosen action. Use a switch statement or function to manage this.
		if (actionInt == 0)
			chosen_action = Action::WAIT;

		if (actionInt == 1)
			chosen_action = Action::ADD_WATER;

		if (actionInt == 2)
			chosen_action = Action::RELEASE_WATER;

		// Calculate Reward
		// TODO: Calculate the reward you want to give to the AI
		//reward = calcReward(currentState, chosen_action);
		//Q[currentState][chosen_action] = Q[currentState][chosen_action] + (learningRate * (reward + (discountFactor * maxQ) - Q[currentState][chosen_action]));

		// Update Q Matrix
		// TODO: Update the correct item the Q matrix with the correct reward.

		// TODO: Print out which action the AI ran. You can use a similar method to the action_to_string or state_to_string described in the printMatrix function

		switch (chosen_action)
		{
		case Action::WAIT:
			// TODO: Add code
			std::cout << " ------------ " << std::endl;
			std::cout << "--- I'm waiting ---" << std::endl;
			std::cout << " ------------ " << std::endl;
			break;
		case Action::ADD_WATER:
			// TODO: Add code
			std::cout << " ------------ " << std::endl;
			std::cout << "### adding water ###" << std::endl;
			std::cout << " ------------ " << std::endl;
			system_pressure += 10.0f;
			break;
		case Action::RELEASE_WATER:
			// TODO: Add code
			std::cout << " ------------ " << std::endl;
			std::cout << "%%% releasing water %%%" << std::endl;
			std::cout << " ------------ " << std::endl;
			system_pressure -= 10.0f;
			break;
		default:
			// We should never reach this point
			// but its good to prepare for it just in case
			std::cout << "_ I'm stuck in default state _" << std::endl;
			break;
		}



		system_pressure -= (rand() % 4);
		std::cout << " ++++++++++++++ " << std::endl;
		std::cout << "System has lost some pressure." << std::endl;
		std::cout << " ++++++++++++++ " << std::endl;
		std::this_thread::sleep_for(100ms);
		iterator++;

		if (iterator == 50)
			break;

		//learningRate -= .1f;
		//discountFactor -= .1f;
	}

	printMatrix();

	std::cin.get();
}