#include "World.h"

#pragma region Constructors

World::World()
{
}

World::World(WorldConfig configs, size_t cycles)
{
	this->configurations = configs;
	this->atualGeneration = 0;
	this->cycles = cycles;
}

World::~World()
{
}

#pragma endregion

#pragma region Private Methods

void World::InternUpdate()
{
	if (atualGeneration < configurations.GetGenerations())
	{
		if (atualCycle < cycles)
		{
			for (size_t i = 0; i < players.size(); i++)
			{
				//TODO: HERE IS THE PLACE TO PLAY THE GAME
				players[i]->SetLifeTime(this->timer);
			}
			atualCycle++;
		}
		else
		{			
			atualCycle = 0;
			atualGeneration++;

			//Calculate Fitness
			for (size_t i = 0; i < players.size(); i++)
			{
				float ft = players[i]->UpdateFitness();

				if (ft <= 0)
				{
					endOfSimulation = true;
					return;
				}
			}

			sort(players.begin(), players.end(), [](Player* const& a, Player* const& b) { return a->GetFitness() < b->GetFitness(); });
			float bf = players[0]->GetFitness();

			cout << "End of Generation: " << atualGeneration << " Proximity %: " << 1-bf << endl;

			genetic.GenerateNewPopulation(players, PopulationGeneratorType::ROULETTE, configurations);
		}
	}
	else
	{
		endOfSimulation = true;
	}
}

#pragma endregion

#pragma region Getters and Setters


vector<Player*> World::GetPlayers() { return this->players; }

void World::SetTimer(float timer){ this->timer = timer; }

#pragma endregion

#pragma region Public Methods

void World::Start()
{
	for (size_t i = 0; i < configurations.GetPopulationSize(); i++)
	{
		Player* p = new Player(i, atualGeneration, Chromosome(cycles));
		players.push_back(p);
	}
}

void World::Update()
{

	if (!endOfSimulation)
	{
		InternUpdate();
	}
	else
	{

	}

	if (endOfSimulation)
	{
		cout << "END OF THE SIMULATION" << endl;
		system("pause");
	}
}


void World::UpdatePlayerFitness(int id, float lifeTime)
{
	players[id]->SetLifeTime(lifeTime);
	players[id]->UpdateFitness();
}

void World::UpdatePopulation()
{
	sort(players.begin(), players.end(), [](Player* const& a, Player* const& b) { return a->GetFitness() > b->GetFitness(); });
	float bf = players[0]->GetFitness();
	
	cout << "------------------------" << endl;
	cout << "End of Generation: " << atualGeneration << endl;
	cout << "Best Proximity %: " << bf << endl;
	cout << "Player from id: " << players[0]->GetId() << endl;
	cout << "Total Time: " << players[0]->GetLifeTime() << endl;
	cout << "------------------------" << endl;

	ofstream logFile;
	cout << GetDateTime() << endl;
	string path = "../../LOG/" + GetDateTime() + ".log";
	logFile.open(path);
	logFile << "GENERATION:" << atualGeneration << " ID:" << players[0]->GetId() << " TIME:" << players[0]->GetLifeTime() << endl;
	
	for (size_t j = 0; j < players[0]->GetChromosome().GetWeights().size(); j++)
	{
		logFile << players[0]->GetChromosome().GetWeights()[j] << "#";
	}
	
	logFile << endl;
	logFile.close();

	genetic.GenerateNewPopulation(players, PopulationGeneratorType::ROULETTE, configurations);

	atualGeneration++;
}


#pragma endregion
