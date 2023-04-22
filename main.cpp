// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
using namespace sf;
using namespace std;
int main()
{
	float width = sf::VideoMode::getDesktopMode().width/2;
	float height = sf::VideoMode::getDesktopMode().height/2;
	View mainView(FloatRect(0.0f,0.0f,width, height));
	//width = 800; height = 600;
	// Create a video mode object
	VideoMode vm(width, height);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Font f;
	if (!f.loadFromFile("./fonts/KOMIKAP_.ttf")) cout << "failed to load font..." << endl;
	Text instructions;
	instructions.setFont(f);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::Green);

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
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
				    float x1 = event.mouseButton.x;
				    float y1 = event.mouseButton.y;
				    vertices.push_back({ x1,y1 });
				}
			}

		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*****************************************
			Update the scene
		*****************************************/
		//generate interior points

		ostringstream oss;
		oss << "Click stuff and " << endl << "I will write stuff";
		instructions.setString(oss.str());

		FloatRect textRect = instructions.getLocalBounds();
		instructions.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);

		instructions.setPosition(width / 2, 50);

		/*
		****************************************
		Draw the scene
		****************************************
		*/
		// Clear everything from the last run frame
		window.clear();
		// Draw our game scene here
		//RectangleShape r{ Vector2f{4,4} }; ///width, height.  Center uninitialized
		window.setView(mainView);
		CircleShape r(2);
		r.setFillColor(Color::Magenta);
		int len = vertices.size();
		if (len <=3)
		{
		    for (size_t i = 0; i < vertices.size(); i++)
		    {
			   r.setPosition(Vector2f{ vertices.at(i).x, vertices.at(i).y });
			   window.draw(r);
		    }
		}
		else
		{   
		    for (int i = 3; i < 100; i++)
		    {
			   float x1, x2, dx;
			   float y1, y2, dy;

			   srand(i);			   
			   int rnd_i = rand() % 3 + 0;
			   cout << "rnd_i = " << rnd_i << endl;

			   //x1 = vertices.at(rnd_i).x;
			   //y1 = vertices.at(rnd_i).y;
			   x1 = vertices.at(rnd_i).x;
			   y1 = vertices.at(rnd_i).y;
			   
			   //int len_i = vertices.size()-1;
			   x2 = vertices.at(i).x;
			   y2 = vertices.at(i).y;

			   dx = sqrt(pow(x1 - x2, 2.0)) / 2.0;
			   dy = sqrt(pow(y1 - y2, 2.0)) / 2.0;

			   if (x1 > x2)
				  dx += x2;
			   else
				  dx += x1;
			   if (y1 > y2)
				  dy += y2;
			   else
				  dy += y1;

			   cout << "dx = " << dx << ", dy = " << dy << endl;			  

			   CircleShape r(2 + rnd_i);
			   r.setPosition({ dx, dy });
			   window.draw(r);

			   vertices.push_back({ dx,dy });
		    }
		   // vertices.resize(1);
		}
				window.draw(instructions);
		// Show everything we just drew
		window.display();
	}

	return 0;
}
