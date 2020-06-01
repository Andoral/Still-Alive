#include <SFML/Graphics.hpp>
#include<iostream>
#include<chrono>
#include<thread>
using namespace sf;
using namespace std;

class Hero
{
public:

	float x, y, w, h, dx, dy, speed = 0;
	int movemark = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Hero(String F, int X, int Y, float W, float H)
	{
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(w, h, w, h));


	}
	void move(float time)
	{
		switch (movemark)
		{
		case 0: 
			{
			dx = speed;
			dy = 0;
			break;
			}
		case 1:
			{
			dx = -speed;
			dy = 0;
			break;
			}
		case 2:
			{
			dx = 0;
			dy = speed;
			break;
			}
		case 3:
			{
			dx = 0;
			dy = -speed;
			break;
			}
		}
		x += dx * time;
		y += dy * time;
		speed = 0;
		sprite.setPosition(x, y);
	}
};

void Menu(RenderWindow &window)
{
	Texture Title, PlayButton, LoadButton, ExitButton, BotPicture;
	int buttonmark;
	int picturemark = 0;
	bool menumark = 0;
	Clock clock;
	Clock CycleTimeclock;
	int CycleTime, PastCycleTime = 0;
	Title.loadFromFile("images/SteelALIVE.png");
	PlayButton.loadFromFile("images/PlayButton.png");
	LoadButton.loadFromFile("images/LoadButton.png");
	ExitButton.loadFromFile("images/ExitButton.png");
	BotPicture.loadFromFile("images/bg0.png");
	Sprite title(Title), button1(PlayButton), button2(LoadButton), button3(ExitButton), bg1(BotPicture), bg2(BotPicture);
	title.setPosition(275, 0);
	button1.setPosition(315, 100);
	button2.setPosition(315, 170);
	button3.setPosition(315, 240);
	bg1.setPosition(30, 80);
	bg2.setPosition(490, 80);
	while (menumark == 0)
	{
		float time = clock.getElapsedTime().asMicroseconds();
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
			{
				window.close();
				exit(1);
			}
		}
			button1.setColor(Color::White);
			button2.setColor(Color::White);
			button3.setColor(Color::White);
			buttonmark = 0;
			if ((IntRect(315, 100, 150, 55).contains(Mouse::getPosition(window))))
			{
				buttonmark = 1;
				button1.setColor(Color::Green);
			}
			if ((IntRect(315, 170, 150, 50).contains(Mouse::getPosition(window))))
			{
				buttonmark = 2;
				button2.setColor(Color::Green);
			}
			if ((IntRect(315, 240, 150, 50).contains(Mouse::getPosition(window))))
			{
				buttonmark = 3;
				button3.setColor(Color::Green);
			}
			if ((Mouse::isButtonPressed(Mouse::Left)))
			{
				if (buttonmark == 1)
				{
					return;
				}
				if (buttonmark == 2)
				{

				}
				if (buttonmark == 3)
				{
					exit(2);
				}
			}
			CycleTime = CycleTimeclock.getElapsedTime().asSeconds();
			if ((CycleTime - PastCycleTime) > 3)
			{
				int random = rand();
				if ((random & 2 + 1) == 1)
				{
					BotPicture.loadFromFile("images/1.png");
					PastCycleTime = CycleTime;
				}
				if ((random & 2 + 1) == 2)
				{
					BotPicture.loadFromFile("images/2.png");
					PastCycleTime = CycleTime;
				}

			
			}
			clock.restart();
			time = time / 800;
			window.draw(title);
			window.draw(button1);
			window.draw(button2);
			window.draw(button3);
			window.draw(bg1);
			window.draw(bg2);
			window.display();
		
		
	}




}



int main()
{





	RenderWindow window(VideoMode(800, 400), "STILL ALIVE");
	Menu(window);








	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}