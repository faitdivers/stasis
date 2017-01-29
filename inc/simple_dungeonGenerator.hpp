#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "../inc/tilemap.hpp"

enum class Direction
{
	North, South, East, West,
};

// This class allows for the creation of dungeons containing:
// - Square Rooms
// - Straight Corridors
// - Doors
// - Up and Down stairs
//
// It is not guaranteed that there is a path from stair to stair.
class SimpleDungeonGenerator
{
public:
 
	int Seed; 
	int m_xSize, m_ySize;
	int MaxFeatures;
	int ChanceRoom, ChanceCorridor;
 
	SimpleDungeonGenerator(int XSize, int YSize);
	TileMap Generate();
 
private:
 
	typedef std::mt19937 RngT;
 
	int GetRandomInt(RngT& rng, int min, int max) const;
	Direction GetRandomDirection(RngT& rng) const;
	bool MakeCorridor(TileMap& map, RngT& rng, int x, int y, int maxLength, Direction direction) const;
	bool MakeRoom(TileMap& map, RngT& rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction) const;
	bool MakeFeature(TileMap& map, RngT& rng, int x, int y, int xmod, int ymod, Direction direction) const;
	bool MakeFeature(TileMap& map, RngT& rng) const;
	bool MakeStairs(TileMap& map, RngT& rng, Tile tile) const;
	bool MakeDungeon(TileMap& map, RngT& rng) const;
 
};
