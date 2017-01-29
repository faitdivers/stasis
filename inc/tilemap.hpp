#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <cassert>

enum class Tile {
  Unused = 0,
  DefaultBkgIni = 16 * 4,
  DefaultBkgEnd = 16 * 4 + 3,
  DirtWall = 16,
  DirtFloor = 1,
  Corridor = 1,
  Door = 12 * 16 + 5,
  UpStairs = 9 * 16,
  DownStairs = 9 * 16
};

class TileMap : public sf::Drawable, public sf::Transformable {
public:

  TileMap(int xSize, int ySize);

  bool load(const std::string& tileset,
            sf::Vector2u tileSize,
            unsigned int width,
            unsigned int height);

  void SetTile(int x, int y, Tile tiletype);
  void SetTiles(int xStart, int yStart, int xEnd, int yEnd, Tile tiletype);
  Tile GetTile(int x, int y) const;
  bool IsXInBounds(int x) const;
  bool IsYInBounds(int y) const;
  bool IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd) const;
  bool IsAdjacent(int x, int y, Tile tile) const;

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::VertexArray vertices_;
  sf::Texture tileset_;
  int xSize_;
  int ySize_;
  int* tileLevel;
};

#endif
