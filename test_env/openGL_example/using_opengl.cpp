#include <SFML/Window.hpp>

void draw()
{
	glBegin(GL_QUADS);

    	glVertex3f(-50.f, -50.f, -50.f);
    	glVertex3f(-50.f,  50.f, -50.f);
    	glVertex3f( 50.f,  50.f, -50.f);
    	glVertex3f( 50.f, -50.f, -50.f);

	    glVertex3f(-50.f, -50.f, 50.f);
	    glVertex3f(-50.f,  50.f, 50.f);
	    glVertex3f( 50.f,  50.f, 50.f);
	    glVertex3f( 50.f, -50.f, 50.f);

	    glVertex3f(-50.f, -50.f, -50.f);
	    glVertex3f(-50.f,  50.f, -50.f);
	    glVertex3f(-50.f,  50.f,  50.f);
	    glVertex3f(-50.f, -50.f,  50.f);

	    glVertex3f(50.f, -50.f, -50.f);
	    glVertex3f(50.f,  50.f, -50.f);
	    glVertex3f(50.f,  50.f,  50.f);
	    glVertex3f(50.f, -50.f,  50.f);

	    glVertex3f(-50.f, -50.f,  50.f);
	    glVertex3f(-50.f, -50.f, -50.f);
	    glVertex3f( 50.f, -50.f, -50.f);
	    glVertex3f( 50.f, -50.f,  50.f);

	    glVertex3f(-50.f, 50.f,  50.f);
	    glVertex3f(-50.f, 50.f, -50.f);
	    glVertex3f( 50.f, 50.f, -50.f);
	    glVertex3f( 50.f, 50.f,  50.f);

	glEnd();
}

int main()
{
	bool Running = true;
	bool QuitKeyPressed = false;
	
	//Basic window creation with settings struct
	
	//Creating rendering context
	sf::WindowSettings Settings;
	Settings.DepthBits = 24; //24 bit depth buffer
	Settings.StencilBits = 8; //8 bit stencil buffer
	Settings.AntialiasingLevel = 2; //2 levels of anitaliasing
	
    sf::Window Application(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close, Settings);
	
	//I DONT UNDERSTAND THIS NEXT PART AT ALL
	
	//Setting colour and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	
	//Enable Z-Buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
	//Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 500.f);	
	
	sf::Clock Clock;
	const sf::Input& Input = Application.GetInput();
	while (Running)
	{
		
		QuitKeyPressed = Input.IsKeyDown(sf::Key::Q);
		
		sf::Event Event;
		while (Application.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Resized)
    			glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}

		Application.SetActive();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glRotatef(Clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
		glRotatef(Clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
		glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

		draw();

		if (QuitKeyPressed) Running = false;
		Application.Display();
		
	}
	
	return EXIT_SUCCESS;
}