#include "../inc/tilemap.hpp"
#include <random>


class SimpleMazeGenerator 
{
public:
	SimpleMazeGenerator(int xSize, int ySize, int c, int d);
	TileMap Generate();
	
private:
	TileMap MakeMaze();

	typedef std::mt19937 RngT;
	int shape_ [2];
	int c_adj_; //complexity adjusted to room size
	int d_adj_; //density adjusted to room size
};
