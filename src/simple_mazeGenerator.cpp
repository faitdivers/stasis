// C++ adaptation from https://en.wikipedia.org/wiki/Maze_generation_algorithm 
#include "../inc/simple_mazeGenerator.hpp"
#include <vector>

SimpleMazeGenerator::SimpleMazeGenerator (int xSize, int ySize, int c, int d)
// width, height, complexity and density
{
    //Only odd shapes
    shape_[0] = (ySize / 2) * 2 - 1;
    shape_[1] = (xSize / 2) * 2 - 1;
    //Adjust complexity and density relative to maze size
    c_adj_ = c * (5 * (shape_[0] + shape_[1]));
    d_adj_ = d * ((shape_[0]/2) * (shape_[1]/2));
}

TileMap SimpleMazeGenerator::Generate()
{
    TileMap map = MakeMaze();
    map.load("../../gfx/world.png", sf::Vector2u(16, 16), shape_[1], shape_[0]);
    return map;
}

TileMap SimpleMazeGenerator::MakeMaze()
{
    int step = 2;
    TileMap map(shape_[0], shape_[1]);
    int seed((std::random_device()()));
    auto rng = RngT(seed);

    int x, y;

    for(int i = 0; i < d_adj_; i++)
    {
        x = std::uniform_int_distribution<int>(0, shape_[1])(rng);
        y = std::uniform_int_distribution<int>(0, shape_[0])(rng);
        map.SetTile(x,y,Tile::DirtFloor);
        for(int j = 0; j < c_adj_; j++)
        {
            std::vector<std::vector<int>> neighbours;
            std::vector<int> v;
            if (x > 1)
            {
                v = {x-step, y};
                neighbours.push_back(v);
            }
            if (x < shape_[1] - step)
            {
                v = {x+step, y};
                neighbours.push_back(v);
            }
            if (y > 1)
            {
                v = {x, y-step};
                neighbours.push_back(v);
            }
            if (y < shape_[0] - step)
            {
                v = {x, y+step};
                neighbours.push_back(v);
            }
            if (neighbours.size())
            {
                int neigh_rnd = std::uniform_int_distribution<int>(0, neighbours.size()-1)(rng);
                std::vector<int> neigh = neighbours[neigh_rnd];
                if(map.IsAreaUnused(neigh[0], neigh[1], neigh[0], neigh[1]))
                {
                    map.SetTile(neigh[0],neigh[1],Tile::DirtFloor);
                    map.SetTile(neigh[0] + (x-neigh[0])/2,neigh[1] + (y-neigh[1])/2, Tile::DirtFloor);
                    x = neigh[0];
                    y = neigh[1];
                }
            }
        }
    }
    return map;
}
