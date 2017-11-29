#ifndef WORLD_H
#define WORLD_H

#include "Player.h"
#include "WorldConfig.h"
#include "Genetic.h"

class World
{
private:

#pragma region Attributes
	
	WorldConfig configurations;
	vector<Player*> players;

	size_t cycles;
	size_t atualCycle;
	size_t atualGeneration;

	bool endOfSimulation;
	
	Genetic genetic;

	float timer;

#pragma endregion

#pragma region Private Methods

	void InternUpdate();
	
#pragma endregion

public:

#pragma region Constructors

	World();
	World(WorldConfig configs, size_t cycles);
	~World();

#pragma endregion

#pragma region Getters and Setters

	void SetTimer(float timer);

	vector<Player*> GetPlayers();

#pragma endregion

#pragma region Public Methods

	void Start();
	void Update();
	void UpdatePlayerFitness(int id, float fitness);
	void UpdatePopulation();
	
#pragma endregion

};

#endif