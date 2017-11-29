#ifndef PLAYER_H
#define PLAYER_H

#include "Individual.h"
class Player : public Individual
{
private:

#pragma region Attributes

	float lifeTime;

#pragma endregion

public:

#pragma region Constructors

	Player();
	Player(size_t id, int generation, Chromosome chromosome);
	~Player();

#pragma endregion

#pragma region Getters and Setters

	float GetLifeTime();

	void SetLifeTime(float value);

#pragma endregion

#pragma region Public Methods
	
	float UpdateFitness();

#pragma endregion

};

#endif