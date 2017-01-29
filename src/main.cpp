#include <iostream>
#include "../inc/simple_dungeonGenerator.hpp"
#include "../inc/simple_mazeGenerator.hpp"
#include "../inc/brownianGenerator.hpp"
#include "../inc/utils.hpp"

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tilemap");

  int xMapSize = 100;
  int yMapSize = 100;

  // create a view with its center and size
  sf::View defaultView(sf::Vector2f(xMapSize * 8, yMapSize * 8),
                sf::Vector2f(xMapSize * 16, yMapSize * 16));
  
  sf::View view(sf::Vector2f(xMapSize * 8, yMapSize * 8),
                sf::Vector2f(xMapSize * 16, yMapSize * 16));
  
  int stepMove = 5;
  
  window.setView(defaultView);
  window.setFramerateLimit(60);
  
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
      if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
      else if (event.type == sf::Event::KeyPressed)
      {
        //When backspace is clicked go back to default view
        if (event.key.code == sf::Keyboard::BackSpace)
        {
          window.setView(defaultView);
          view = defaultView;
        } else if(event.key.code == sf::Keyboard::Up)
        {
          view.move(0, -stepMove);
          window.setView(view);
        } else if(event.key.code == sf::Keyboard::Down)
        {
          view.move(0, stepMove);
          window.setView(view);
        } else if(event.key.code == sf::Keyboard::Right)
        {
          view.move(stepMove, 0);
          window.setView(view);
        } else if(event.key.code == sf::Keyboard::Left)
        {
          view.move(-stepMove, 0);
          window.setView(view);
        }
      }
      if (event.type == sf::Event::MouseWheelScrolled)
      {
        if (event.mouseWheelScroll.delta > 0)
          view = zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
        else if (event.mouseWheelScroll.delta < 0)
          view = zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, zoomAmount);
      }
    }

    // draw the map
    window.clear();
    window.draw(map);
    window.display();
  }

  return 0;
}

