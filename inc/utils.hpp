#include <SFML/Graphics.hpp>

const float zoomAmount{ 1.1f };
sf::View zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);