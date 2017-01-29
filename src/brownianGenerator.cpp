#include "../inc/brownianGenerator.hpp"
#include "../inc/topinclude.hpp"
#include <vector>
#include <iostream>

BrownianPathsGenerator::BrownianPathsGenerator(int xSize, int ySize)
{
	xSize_ = xSize;
	ySize_ = ySize;
}

TileMap BrownianPathsGenerator::Generate()
{
  TileMap map = MakePath();
  map.load(STASIS_ROOT_PATH"gfx/world.png", sf::Vector2u(16, 16), xSize_, ySize_);
  return map;
}

TileMap BrownianPathsGenerator::MakePath()
{
	int seed((std::random_device()()));
  auto rng = RngT(seed);

  TileMap map(xSize_, ySize_);

	//Direction for the probabilities: N, S, E, W (as per tilemap.hpp)
	//TODO: make the probabilisties a changeable heuristic
	std::vector<float> prob = {0.25, 0.25, 0.25, 0.25};
	std::discrete_distribution<int> distribution (prob.begin(), prob.end());
	Direction dir = static_cast<Direction>(distribution(rng));
  Direction dir_prev;

	int x, y;
	int step = 1;

	if(dir == Direction::North){
		y = ySize_-1;
		x = std::uniform_int_distribution<int>(0, xSize_-1)(rng);
	} else if(dir == Direction::South){
		y = 0;
		x = std::uniform_int_distribution<int>(0, xSize_-1)(rng);
	} else if(dir == Direction::East){
		x = xSize_-1;
		y = std::uniform_int_distribution<int>(0, ySize_-1)(rng);
	} else {
		x = 0;
		y = std::uniform_int_distribution<int>(0, ySize_-1)(rng);
	}

	map.SetTile (x,y,Tile::DirtFloor);

  //TODO: make the stopping condition a definable heuristic  
	for(int m = 0; m < xSize_*ySize_; m++){
		int xdelta = 0, ydelta = 0;

		dir = static_cast<Direction>(distribution(rng));

		if(dir == Direction::North){
			if(y+step >= ySize_){
				ydelta = ySize_-y-1;
			} else {
				ydelta = step;
			}
			map.SetTiles (x,y,x,y+ydelta,Tile::DirtFloor);
		} else if(dir == Direction::South){
			if(y-step < 0){
				ydelta = -y;
			} else {
				ydelta = -step;
			}
			map.SetTiles (x,y+ydelta,x,y,Tile::DirtFloor);
		} else if(dir == Direction::East){
			if(x+step >= xSize_){
				xdelta = xSize_-x-1;
			} else {
				xdelta = step;
			}
			map.SetTiles (x,y,x+xdelta,y,Tile::DirtFloor);
		} else {
			if(x-step < 0){
				xdelta = -x;
			} else {
				xdelta = -step;
			}
			map.SetTiles (x+xdelta,y,x,y,Tile::DirtFloor);
		}
		x += xdelta;
		y += ydelta;
	}
	return map;
}

