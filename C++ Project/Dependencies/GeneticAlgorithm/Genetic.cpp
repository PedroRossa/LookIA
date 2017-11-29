#include "Genetic.h"

#pragma region Constructors

Genetic::Genetic()
{
}

Genetic::~Genetic()
{
}

#pragma endregion

#pragma region Private Methods

vector<Player*> Genetic::Roulette_Selection(vector<Player*> population, WorldConfig configs)
{
	int sum = 0;
	int index = 0;

	vector<Player*> newPop;

	sort(population.begin(), population.end(), [](Player* const& a, Player* const& b) { return a->GetFitness() > b->GetFitness(); });

	int populationSize = population.size();

	//check for elitism
	if (configs.UseElitism())
	{
		//get the best fitness individuals
		for (size_t i = 0; i < configs.GetElitismFactor(); i++)
		{
			Player* player = new Player(
				i,
				population[i]->GetGeneration() + 1,
				population[i]->GetChromosome());

			newPop.push_back(player);
		}

		populationSize -= configs.GetElitismFactor();
	}

	for (unsigned int i = 0; i < population.size(); i++) {
		sum += population[i]->GetFitness();
	}

	for (size_t i = 0; i < populationSize; i++)
	{
		double rnd = (((double)rand() / (double)RAND_MAX) * sum);
		sum = 0;

		for (unsigned int i = 0; i < population.size(); i++) {
			sum += population[i]->GetFitness();
			if (rnd < sum) {
				index = i;
				break;
			}
		}

		Player* player;
		//correct the ID
		if (configs.UseElitism())
		{
			player = new Player(
				i + configs.GetElitismFactor(),
				population[index]->GetGeneration() + 1,
				population[index]->GetChromosome());
		}
		else
		{
			player = new Player(
				i,
				population[index]->GetGeneration() + 1,
				population[index]->GetChromosome());
		}
		newPop.push_back(player);
	}
	
	//Run the crossover and mutation
	for (size_t i = 0; i < newPop.size(); i+=2)
	{
		Chromosome* newChromos = Crossover(newPop[i]->GetChromosome(), newPop[i + 1]->GetChromosome(), configs.GetCrossoverTax(), configs.GetCrossoverDivision());

		Mutation(&newChromos[0], configs.GetMutationTax());
		Mutation(&newChromos[1], configs.GetMutationTax());

		newPop[i]->SetChromosome(newChromos[0]);
		newPop[i]->SetChromosome(newChromos[1]);
	}

	return newPop;
}

vector<int> Genetic::GenerateDivisionPoints(int numberOfDivisions, int sizeOfChromossome)
{
	vector<int> divisionValues;

	//generate Division points
	for (size_t i = 0; i < numberOfDivisions; i++)
	{
		int randDivisionPoint = 1 + (rand() % (sizeOfChromossome - 1));
		//if find the rand value inside of divisionValues vector, try again
		if (find(divisionValues.begin(), divisionValues.end(), randDivisionPoint) != divisionValues.end())
		{
			i--;
		}
		else
		{
			divisionValues.push_back(randDivisionPoint);
		}
	}

	sort(divisionValues.begin(), divisionValues.end());
	return divisionValues;
}

Chromosome* Genetic::MixChromosomes(vector<float>valuesA, vector<float> valuesB, vector<int> divisionPoints)
{
	vector<float> newAValues;
	vector<float> newBValues;

	int globalPosition = 0;
	bool isPairCross = true;
	int atualDivision = 0;
	int lastDivision = 0;

	for (size_t i = 0; i < divisionPoints.size(); i++)
	{
		atualDivision = divisionPoints[i];
		
		if (i > 0)
			lastDivision = divisionPoints[i - 1];

		for (size_t j = lastDivision; j < atualDivision; j++)
		{
			if (isPairCross)
			{
				newAValues.push_back(valuesA[globalPosition]);
				newBValues.push_back(valuesB[globalPosition]);
			}
			else
			{
				newAValues.push_back(valuesB[globalPosition]);
				newBValues.push_back(valuesA[globalPosition]);
			}
			globalPosition++;
		}
		isPairCross = !isPairCross;
	}

	//set the last values
	for (size_t i = globalPosition; i < valuesA.size(); i++)
	{
		if (isPairCross)
		{
			newAValues.push_back(valuesA[i]);
			newBValues.push_back(valuesB[i]);
		}
		else
		{
			newAValues.push_back(valuesB[i]);
			newBValues.push_back(valuesA[i]);
		}
	}

	Chromosome a(newAValues.size(), newAValues);
	Chromosome b(newBValues.size(), newBValues);

	Chromosome* newChromosomes = new Chromosome[2];

	newChromosomes[0] = a;
	newChromosomes[1] = b;

	return newChromosomes;
}

#pragma endregion

#pragma region Public Methods

void Genetic::GenerateNewPopulation(vector<Player*>& population, PopulationGeneratorType type, WorldConfig configs)
{
	switch (type)
	{
	case ROULETTE:
		population = Roulette_Selection(population, configs);
		break;
	default:
		break;
	}
}

Chromosome* Genetic::Crossover(Chromosome chromosomeA, Chromosome chromosomeB, int crossoverTax, int divisions)
{
	//garantee the max division possible
	if (divisions >= chromosomeA.GetSize());
		divisions = chromosomeA.GetSize() - 1;
	if (divisions <= 0)
		divisions = 1;

	vector<int> divisionPoints = GenerateDivisionPoints(divisions, chromosomeA.GetSize());

	int crossValue = rand() % 100;
	if (crossValue <= crossoverTax)
	{
		Chromosome* c = MixChromosomes(chromosomeA.GetWeights(), chromosomeB.GetWeights(), divisionPoints);
		return  new Chromosome[2]{ c[0], c[1] };
	}
	else
	{
		return new Chromosome[2]{ chromosomeA, chromosomeB };
	}
}

void Genetic::Mutation(Chromosome* chromosome, int mutationTax)
{
	vector<float> values = chromosome->GetWeights();
	
	for (size_t i = 0; i < values.size(); i++)
	{
		int mutationsValue = rand() % 100;
		if (mutationsValue <= mutationTax)
		{
			int dial = rand() % 100;
			if (dial <= 40) 
			{
				float dialValue;
				int positive = rand() % 2;

				if (positive == 1)
					dialValue = values[i] + ((rand() % 10) / 10.0f);
				else 
					dialValue = values[i] - ((rand() % 10) / 10.0f);

				values[i] = dialValue;
			}
			else
			{
				values[i] = RandWeight(-1.0f, 1.0f);
			}
		}

	}

	chromosome->SetWeights(values);
}

#pragma endregion