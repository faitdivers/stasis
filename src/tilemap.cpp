#include "../inc/tilemap.hpp"
#include <iostream>

TileMap::TileMap(int xSize, int ySize) {
  xSize_ = xSize;
  ySize_ = ySize;
  tileLevel.resize(xSize*ySize);
  for (int i = 0; i < xSize*ySize; i++) {
    tileLevel[i] = static_cast<int>(Tile::DefaultBkgIni) + rand() % 4;
  }
}

bool TileMap::load(const std::string& tileset,
                   sf::Vector2u tileSize,
                   unsigned int width,
                   unsigned int height) {
  // load the tileset texture
  if (!tileset_.loadFromFile(tileset))
    return false;

  // resize the vertex array to fit the level size
  vertices_.setPrimitiveType(sf::Quads);
  vertices_.resize(width * height * 4);

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j) {
      // get the current tile number
      int tileNumber = tileLevel[i + j * width];

      // find its position in the tileset texture
      int tu = tileNumber % (tileset_.getSize().x / tileSize.x);
      int tv = tileNumber / (tileset_.getSize().x / tileSize.x);

      // get a pointer to the current tile's quad
      sf::Vertex* quad = &vertices_[(i + j * width) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tileSize.x,
                                      j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x,
                                      j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x,
        (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x,
        (j + 1) * tileSize.y);

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tileSize.x,
                                       tv * tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x,
                                       tv * tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x,
        (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x,
        (tv + 1) * tileSize.y);
    }

  return true;
}

void TileMap::SetTile(int x, int y, Tile tiletype) {
  assert(IsXInBounds(x));
  assert(IsYInBounds(y));

  //std::cout << "Placed Tile! " + std::to_string(x) + ", " + std::to_string(y) << std::endl;
  tileLevel[x + xSize_ * y] = static_cast<int>(tiletype);
}

void TileMap::SetTiles(int xStart, int yStart, int xEnd, int yEnd, Tile tiletype) {
  assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
  assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

  assert(xStart <= xEnd);
  assert(yStart <= yEnd);

  for (auto y = yStart; y != yEnd + 1; ++y)
    for (auto x = xStart; x != xEnd + 1; ++x)
      SetTile(x, y, tiletype);
}

Tile TileMap::GetTile(int x, int y) const {
  assert(IsXInBounds(x));
  assert(IsYInBounds(y));

  return static_cast<Tile>(tileLevel[x + xSize_ * y]);
}

bool TileMap::IsXInBounds(int x) const {
  return x >= 0 && x < xSize_;
}

bool TileMap::IsYInBounds(int y) const {
  return y >= 0 && y < ySize_;
}

//Checks if the Tile type is either unused or DefaultBkg
bool TileMap::IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd) const {
  assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
  assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

  assert(xStart <= xEnd);
  assert(yStart <= yEnd);

  for (auto y = yStart; y != yEnd + 1; ++y)
    for (auto x = xStart; x != xEnd + 1; ++x)
      if (GetTile(x, y) != Tile::Unused &&
        (GetTile(x, y) < Tile::DefaultBkgIni && GetTile(x, y) > Tile::DefaultBkgEnd))
        return false;

  return true;
}

bool TileMap::IsAdjacent(int x, int y, Tile tile) const {
  assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
  assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));

  return
    GetTile(x - 1, y) == tile || GetTile(x + 1, y) == tile ||
    GetTile(x, y - 1) == tile || GetTile(x, y + 1) == tile;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  states.texture = &tileset_;

  // draw the vertex array
  target.draw(vertices_, states);
}
