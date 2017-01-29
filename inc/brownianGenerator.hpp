#include "../inc/tilemap.hpp"
#include <random>


class BrownianPathsGenerator 
{
public:
	BrownianPathsGenerator(int xSize, int ySize);
	TileMap Generate();
	
private:
	TileMap MakePath();

	typedef std::mt19937 RngT;
	int xSize_;
	int ySize_;
};