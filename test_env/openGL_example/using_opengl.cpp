#include <SFML/Window.hpp>

int main()
{
	bool Running = true;
	bool QuitKeyPressed = false;
	
	#Basic window creation
	sf::Window Application(sf::VideoMode(800, 600, 32). "SFML OpenGL");
	
	sf::WindowSettings
	
	const sf::Input& Input = Application.GetInput()
	while (Running)
	{
		Application.Display();
		
		QuitKeyPressed = Input.IsKeyDown(sf::Key::Q);
		
		if (QuitKeyPressed) Running = false;
		
	}
	
	return 0;
}