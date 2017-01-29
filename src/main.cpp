#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/simple_dungeonGenerator.hpp"
#include "../inc/simple_mazeGenerator.hpp"
#include "../inc/brownianGenerator.hpp"

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tilemap");

  int xMapSize = 100;
  int yMapSize = 100;

  // create a view with its center and size
  sf::View view(sf::Vector2f(xMapSize * 8, yMapSize * 8),
                sf::Vector2f(xMapSize * 16, yMapSize * 16));

  window.setView(view);

  //Simple Dungeon Generation
  //SimpleDungeonGenerator dungeon1(xMapSize, yMapSize);
  //TileMap map = dungeon1.Generate();

  //Simple Maze Generation
  // float complexity = .75;
  // float density = .25;
  // SimpleMazeGenerator maze1(xMapSize, yMapSize, complexity, density);
  // TileMap map = maze1.Generate();

  //Brownian Paths Generation
  BrownianPathsGenerator bpath(xMapSize, yMapSize);
  TileMap map = bpath.Generate();

  // run the main loop
  while (window.isOpen()) {
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // draw the map
    window.clear();
    window.draw(map);
    window.display();
  }

  return 0;
}

