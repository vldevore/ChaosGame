// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	int iterations = 10000;

	// create and load font V //made it more clear we are using SFML with "sff::"
	sf::Font font;
	font.loadFromFile("KOMTITA_.ttf");

	// create text V //made it more clear we are using SFML with "sf::"
	sf::Text text;
	text.setFont(font);
	//fixed "SetString to setString" T
	text.setString("Click any three points on the screen to create a triangle, then click where you would like to create a starting point.");
	text.setCharacterSize(24);
	//set color to white so it shows on the game screen
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	
	//stops the player from adding any more points after the third. T
	bool canClick = true;

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left && canClick)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
				//stops player from adding more points. T
				canClick = false;
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if (points.size() > 0 && points.size() < iterations)
		{
			// generate more point(s)

			// select random vertex
			Vector2f randVertex = (vertices.at(rand() % 3));

			// calculate midpoint between random vertex and the last point in the vector
			Vector2f midpoint = Vector2f((randVertex.x + points.back().x) / 2, (randVertex.y + points.back().y) / 2);

			// push back the newly generated coordinate
			points.push_back(midpoint);
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
			
		window.clear();
		
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}

		//draw text V
		window.draw(text);
		
		//draw a triangle (set position might be wack) V 
		for(int i = 0; i < vertices.size(); i++)
		{
			CircleShape triangle(8, 3);
			triangle.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			triangle.setOutlineThickness(3);
			triangle.setOutlineColor(Color(250, 150, 100));
			window.draw(triangle);
		}
		
		//created a way to render all the points onto the screen. T
		for (const Vector2f point : points)
		{
			CircleShape triangle(8, 3);
			triangle.setPosition(point);
			triangle.setOutlineThickness(2);
			triangle.setOutlineColor(Color(250, 150, 100));
			window.draw(triangle);
		}
		
		window.display();
	}
}
