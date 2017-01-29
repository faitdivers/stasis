#include "../inc/tilemap.hpp"
#include <random>


class SimpleMazeGenerator 
{
public:
	SimpleMazeGenerator(int xSize, int ySize, float c, float d);
	TileMap Generate();
	
private:
	TileMap MakeMaze();

	typedef std::mt19937 RngT;
	int shape_ [2];
	float c_adj_; //complexity adjusted to room size
	float d_adj_; //density adjusted to room size
};
