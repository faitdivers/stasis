#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/simple_dungeonGenerator.hpp"
#include "../inc/simple_mazeGenerator.hpp"

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tilemap");

  int xMapSize = 100;
  int yMapSize = 100;

  // create a view with its center and size
  sf::View view(sf::Vector2f(xMapSize * 4, yMapSize * 4),
                sf::Vector2f(xMapSize * 8, yMapSize * 8));

  window.setView(view);

  //Simple Dungeon Generation
  SimpleDungeonGenerator dungeon1(xMapSize, yMapSize);
  TileMap map = dungeon1.Generate();

  //Simple Maze Generation
  //int complexity = 75;
  //int density = 75;
  //SimpleMazeGenerator maze1(xMapSize, yMapSize, complexity, density);
  //TileMap map = maze1.Generate();

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

// int _main() {
//   sf::RenderWindow window(sf::VideoMode(640, 480),
//                           "SFML works!");
//   window.setFramerateLimit(60);

//   auto window_size = window.getSize();
//   sf::View view(sf::FloatRect(0, 0, window_size.x, window_size.y));
//   view.setCenter({ 0,0 });
//   window.setView(view);

//   //sf::RectangleShape shape({100, 100});
//   //shape.setFillColor(sf::Color::Green);
//   //shape.setOrigin({ shape.getSize().x/2,shape.getSize().y/2 });

//   sf::Time delta_time;
//   sf::Clock clock;

//   sf::Font font;
//   font.loadFromFile("tahoma.ttf");
//   sf::Text text("Text test", font);

//   text.setPosition({ 50,50 });

//   sf::Texture gems_texture;
//   gems_texture.loadFromFile("/Users/jlopesesilva/Dropbox/sfml_exp_xcode/sfml_exp_xcode/gfx/gems.png");
//   sf::Sprite gem(gems_texture);
//   sf::Vector2f gem_size(16, 40);
//   int gem_y_offset = 80;
//   gem.setTextureRect(sf::IntRect(0, gem_y_offset, gem_size.x, gem_size.y));
//   gem.scale({ 2.0, 2.0 });
//   gem.setOrigin(gem_size * 0.5f);

//   int num_frames = 18;
//   float anim_duration = 1.0;
//   float elapsed_time = 0.0;

//   while (window.isOpen()) {
//     delta_time = clock.restart();
//     elapsed_time += delta_time.asSeconds();

//     sf::Event event;
//     while (window.pollEvent(event)) {
//       if (event.type == sf::Event::KeyPressed) {
//         if (event.key.code == sf::Keyboard::Key::W)
//           view.rotate(-5);
//         if (event.key.code == sf::Keyboard::Key::A)
//           view.rotate(-5);
//         if (event.key.code == sf::Keyboard::Key::S)
//           view.rotate(-5);
//         else if (event.key.code == sf::Keyboard::Key::D)
//           view.rotate(5);
//       }
//       //
//       if (event.type == sf::Event::Closed)
//         window.close();
//     }

//     int gem_frame = static_cast<int>((elapsed_time / anim_duration)
//                                      * num_frames) % num_frames;
//     gem.setTextureRect(sf::IntRect(gem_frame * gem_size.x, gem_y_offset,
//                                    gem_size.x, gem_size.y));
//     window.clear();
//     window.setView(view);
//     window.draw(text);
//     window.draw(gem);
//     //window.draw(shape);
//     window.display();
//   }

//   return 0;
// }
