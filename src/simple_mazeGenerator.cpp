// C++ adaptation from https://en.wikipedia.org/wiki/Maze_generation_algorithm 
#include "../inc/topinclude.hpp"
#include "../inc/simple_mazeGenerator.hpp"
#include <vector>

SimpleMazeGenerator::SimpleMazeGenerator (int xSize, int ySize, float c, float d)
// width, height, complexity and density
{
    //Only odd shapes
    shape_[1] = (ySize / 2) * 2 - 1;
    shape_[0] = (xSize / 2) * 2 - 1;
    //Adjust complexity and density relative to maze size
    c_adj_ = static_cast<int>(c * ((shape_[0] + shape_[1])));
    d_adj_ = static_cast<int>(d * ((shape_[0]) + (shape_[1])));
    //c_adj_ = 10;
    //d_adj_ = 10;
}

TileMap SimpleMazeGenerator::Generate()
{
    TileMap map = MakeMaze();
    map.load(STATIS_ROOT_PATH"gfx/world.png", sf::Vector2u(16, 16), shape_[1], shape_[0]);
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
        x = std::uniform_int_distribution<int>(0, shape_[0]-1)(rng);
        y = std::uniform_int_distribution<int>(0, shape_[1]-1)(rng);
        map.SetTile(x,y,Tile::DirtFloor);
        for(int j = 0; j < c_adj_; j++)
        {
            std::vector<std::vector<int>> neighbours;
            std::vector<int> v;
            if (x > 1 && y < shape_[1])
            {
                v = {x-step, y};
                neighbours.push_back(v);
            }
            if (x < shape_[0] - step && y < shape_[1])
            {
                v = {x+step, y};
                neighbours.push_back(v);
            }
            if (y > 1 && x < shape_[0])
            {
                v = {x, y-step};
                neighbours.push_back(v);
            }
            if (y < shape_[1] - step && x < shape_[0])
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
