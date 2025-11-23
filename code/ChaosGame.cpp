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
	RenderWindow window(vm, "Chaos Game", Style::Default);

	// added font support
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error loading font!" << std::endl;
	}

	// Set up text to communicate with user
	sf::Text text;
	text.setFont(font);
	text.setString("Click on any three points on the screen to create the vertices for the triangle. Afterwards, the fourth point will start the chaos game algorithm.");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);

	// Generate random seed for random triangle vertice
	srand(time(0));
	

	vector<Vector2f> vertices;
	vector<Vector2f> points;

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
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "The left button was pressed" << std::endl;
			    std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
					// First 3 clicks to set triangle vertices
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
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
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			
			/// Accelerate midpoint process with for loop
			for (int i = 0; i < 100; ++i)
			{
				int randomNum = rand() % 3;

				Vector2f randomVertex = vertices[randomNum];
				Vector2f lastPoint = points.back();

				Vector2f midPoint;
				midPoint.x = (lastPoint.x + randomVertex.x) / 2;
				midPoint.y = (lastPoint.y + randomVertex.y) / 2;

				points.push_back(midPoint);
			}

		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		window.draw(text); // display text on screen

		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::White);
		    window.draw(rect);
		}
		///TODO:  Draw points

		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape point(Vector2f(5, 5));
			point.setPosition(Vector2f(points[i].x, points[i].y));
			point.setFillColor(Color::White);
			window.draw(point);
		}

		window.display();
	}
}
