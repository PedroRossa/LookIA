#include "Player.h"

#pragma region Constructors

Player::Player()
{
}

Player::Player(size_t id, int generation,Chromosome chromosome)
{
	this->id = id;
	this->generation = generation;
	this->chromosome = chromosome;
}

Player::~Player()
{
}

#pragma endregion

#pragma region Getters and Setters

float Player::GetLifeTime(){ return this->lifeTime; }
void Player::SetLifeTime(float value) { this->lifeTime = value; }

#pragma endregion

#pragma region Public Methods

float Player::UpdateFitness()
{
	//objective is got the highest time in game
	float value = this->lifeTime / 9999;

	this->fitness = value;
	return this->fitness;
}


#pragma endregion