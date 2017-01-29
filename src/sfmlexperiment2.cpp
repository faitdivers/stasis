#include <iostream>
#include <SFML/Graphics.hpp>
#include "../inc/dungeon_generator.hpp"

// namespace {
// class TileMap : public sf::Drawable, public sf::Transformable {
// public:
//   bool load(const std::string& tileset,
//             sf::Vector2u tileSize,
//             const int* tiles,
//             unsigned int width,
//             unsigned int height) {
//     // load the tileset texture
//     if (!m_tileset.loadFromFile(tileset))
//       return false;

//     // resize the vertex array to fit the level size
//     m_vertices.setPrimitiveType(sf::Quads);
//     m_vertices.resize(width * height * 4);

//     // populate the vertex array, with one quad per tile
//     for (unsigned int i = 0; i < width; ++i)
//       for (unsigned int j = 0; j < height; ++j) {
//         // get the current tile number
//         int tileNumber = tiles[i + j * width];

//         // find its position in the tileset texture
//         int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
//         int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

//         // get a pointer to the current tile's quad
//         sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

//         // define its 4 corners
//         quad[0].position = sf::Vector2f(i * tileSize.x,
//                                         j * tileSize.y);
//         quad[1].position = sf::Vector2f((i + 1) * tileSize.x,
//                                         j * tileSize.y);
//         quad[2].position = sf::Vector2f((i + 1) * tileSize.x,
//           (j + 1) * tileSize.y);
//         quad[3].position = sf::Vector2f(i * tileSize.x,
//           (j + 1) * tileSize.y);

//         // define its 4 texture coordinates
//         quad[0].texCoords = sf::Vector2f(tu * tileSize.x,
//                                          tv * tileSize.y);
//         quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x,
//                                          tv * tileSize.y);
//         quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x,
//           (tv + 1) * tileSize.y);
//         quad[3].texCoords = sf::Vector2f(tu * tileSize.x,
//           (tv + 1) * tileSize.y);
//       }

//     return true;
//   }
// private:

//   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     // apply the transform
//     states.transform *= getTransform();

//     // apply the tileset texture
//     states.texture = &m_tileset;

//     // draw the vertex array
//     target.draw(m_vertices, states);
//   }

//   sf::VertexArray m_vertices;
//   sf::Texture m_tileset;
// };
// }

int main() {
  // create the window
  sf::RenderWindow window(sf::VideoMode(1024, 1024), "Tilemap");

  // create a view with its center and size
  sf::View view(sf::Vector2f(64, 64), sf::Vector2f(128, 128));

  window.setView(view);

  // create the tilemap from the level definition
  TileMap map(64,128);
  if (!map.load("gfx/world.png", sf::Vector2u(16, 16), tileLevel, 16, 16))
    return -1;

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
