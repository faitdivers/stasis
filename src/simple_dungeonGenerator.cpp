#include "../inc/topinclude.hpp"
#include "../inc/simple_dungeonGenerator.hpp"
 
SimpleDungeonGenerator::SimpleDungeonGenerator(int XSize, int YSize):
	Seed(std::random_device()()),
	MaxFeatures(1000),
	ChanceRoom(50), ChanceCorridor(50)
	{ 
		xSize_ = XSize;
		ySize_ = YSize;
	}

TileMap SimpleDungeonGenerator::Generate()
{
	// TODO: proper input validation.
	assert(MaxFeatures > 0);
	assert(xSize_ > 3);
	assert(ySize_ > 3);

	auto rng = RngT(Seed);
	auto map = TileMap(xSize_, ySize_);

	MakeDungeon(map, rng);

  map.load(STASIS_ROOT_PATH"gfx/world.png", sf::Vector2u(16, 16), xSize_, ySize_);

	return map;
}
 
 
int SimpleDungeonGenerator::GetRandomInt(RngT& rng, int min, int max) const
{
	return std::uniform_int_distribution<int>(min, max)(rng);
}

Direction SimpleDungeonGenerator::GetRandomDirection(RngT& rng) const
{
	return Direction(std::uniform_int_distribution<int>(0, 3)(rng));
}

bool SimpleDungeonGenerator::MakeCorridor(TileMap& map, RngT& rng, int x, int y, int maxLength, Direction direction) const
{
	assert(x >= 0 && x < xSize_);
	assert(y >= 0 && y < ySize_);

	assert(maxLength > 0 && maxLength <= std::max(xSize_, ySize_));

	auto length = GetRandomInt(rng, 2, maxLength);

	auto xStart = x;
	auto yStart = y;

	auto xEnd = x;
	auto yEnd = y;

	if (direction == Direction::North)
		yStart = y - length;
	else if (direction == Direction::East)
		xEnd = x + length;
	else if (direction == Direction::South)
		yEnd = y + length;
	else if (direction == Direction::West)
		xStart = x - length;

	if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
		return false;

	if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
		return false;

	map.SetTiles(xStart, yStart, xEnd, yEnd, Tile::Corridor);

	//std::cout << "Corridor: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

	return true;
}

bool SimpleDungeonGenerator::MakeRoom(TileMap& map, RngT& rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction) const
{
	// Minimum room size of 4x4 tiles (2x2 for walking on, the rest is walls)
	auto xLength = GetRandomInt(rng, 4, xMaxLength);
	auto yLength = GetRandomInt(rng, 4, yMaxLength);

	auto xStart = x;
	auto yStart = y;

	auto xEnd = x;
	auto yEnd = y;

	if (direction == Direction::North)
	{
		yStart = y - yLength;
		xStart = x - xLength / 2;
		xEnd = x + (xLength + 1) / 2;
	}
	else if (direction == Direction::East)
	{
		yStart = y - yLength / 2;
		yEnd = y + (yLength + 1) / 2;
		xEnd = x + xLength;
	}
	else if (direction == Direction::South)
	{
		yEnd = y + yLength;
		xStart = x - xLength / 2;
		xEnd = x + (xLength + 1) / 2;
	}
	else if (direction == Direction::West)
	{
		yStart = y - yLength / 2;
		yEnd = y + (yLength + 1) / 2;
		xStart = x - xLength;
	}

	if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
		return false;

	if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
		return false;

	map.SetTiles(xStart, yStart, xEnd, yEnd, Tile::DirtWall);
	map.SetTiles(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, Tile::DirtFloor);

	//std::cout << "Room: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

	return true;
}

bool SimpleDungeonGenerator::MakeFeature(TileMap& map, RngT& rng, int x, int y, int xmod, int ymod, Direction direction) const
{
	// Choose what to build
	auto chance = GetRandomInt(rng, 0, 100);

	if (chance <= ChanceRoom)
	{
		if (MakeRoom(map, rng, x + xmod, y + ymod, 8, 6, direction))
		{
			map.SetTile(x, y, Tile::Door);

			// Remove wall next to the door.
			map.SetTile(x + xmod, y + ymod, Tile::DirtFloor);

			return true;
		}

		return false;
	}
	else
	{
		if (MakeCorridor(map, rng, x + xmod, y + ymod, 6, direction))
		{
			map.SetTile(x, y, Tile::Door);

			return true;
		}

		return false;
	}
}

bool SimpleDungeonGenerator::MakeFeature(TileMap& map, RngT& rng) const
{
	auto tries = 0;
	auto maxTries = 1000;

	for( ; tries != maxTries; ++tries)
	{
		// Pick a random wall or corridor tile.
		// Make sure it has no adjacent doors (looks weird to have doors next to each other).
		// Find a direction from which it's reachable.
		// Attempt to make a feature (room or corridor) starting at this point.

		int x = GetRandomInt(rng, 1, xSize_ - 2);
		int y = GetRandomInt(rng, 1, ySize_ - 2);

		if (map.GetTile(x, y) != Tile::DirtWall && map.GetTile(x, y) != Tile::Corridor)
			continue;

		if (map.IsAdjacent(x, y, Tile::Door))
			continue;

		if (map.GetTile(x, y+1) == Tile::DirtFloor || map.GetTile(x, y+1) == Tile::Corridor)
		{
			if (MakeFeature(map, rng, x, y, 0, -1, Direction::North))
				return true;
		}
		else if (map.GetTile(x-1, y) == Tile::DirtFloor || map.GetTile(x-1, y) == Tile::Corridor)
		{
			if (MakeFeature(map, rng, x, y, 1, 0, Direction::East))
				return true;
		}
		else if (map.GetTile(x, y-1) == Tile::DirtFloor || map.GetTile(x, y-1) == Tile::Corridor)
		{
			if (MakeFeature(map, rng, x, y, 0, 1, Direction::South))
				return true;
		}
		else if (map.GetTile(x+1, y) == Tile::DirtFloor || map.GetTile(x+1, y) == Tile::Corridor)
		{
			if (MakeFeature(map, rng, x, y, -1, 0, Direction::West))
				return true;
		}
	}

	return false;
}

bool SimpleDungeonGenerator::MakeStairs(TileMap& map, RngT& rng, Tile tile) const
{
	auto tries = 0;
	auto maxTries = 10000;

	for ( ; tries != maxTries; ++tries)
	{
		int x = GetRandomInt(rng, 1, xSize_ - 2);
		int y = GetRandomInt(rng, 1, ySize_ - 2);

		if (!map.IsAdjacent(x, y, Tile::DirtFloor) && !map.IsAdjacent(x, y, Tile::Corridor))
			continue;

		if (map.IsAdjacent(x, y, Tile::Door))
			continue;

		map.SetTile(x, y, tile);

		return true;
	}

	return false;
}

bool SimpleDungeonGenerator::MakeDungeon(TileMap& map, RngT& rng) const
{
	// Make one room in the middle to start things off.
	MakeRoom(map, rng, xSize_ / 2, ySize_ / 2, 8, 6, GetRandomDirection(rng));

	for (auto features = 1; features != MaxFeatures; ++features)
	{
		if (!MakeFeature(map, rng))
		{
			std::cout << "Unable to place more features (placed " << features << ")." << std::endl;
			break;
		}
	}

	if (!MakeStairs(map, rng, Tile::UpStairs))
		std::cout << "Unable to place up stairs." << std::endl;

	if (!MakeStairs(map, rng, Tile::DownStairs))
		std::cout << "Unable to place down stairs." << std::endl;

	return true;
}
 
