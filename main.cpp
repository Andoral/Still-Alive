#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include<iostream>
#include<chrono>
#include<thread>
#include <sstream>
#include <fstream>
#include <list>
#include "map.h"
using namespace sf;
using namespace std;

int downloadlvl = 1;
int downloadmoney = 0;

class Hero
{
public:

	float x, y, w, h, dx, dy, speed = 0;
	int movemark = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	int lvl = 1;
	int money = 200;
	int health = 100;
	bool life = 1;
	Hero(String F, int X, int Y, float W, float H)
	{
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));


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
		interactionWithMap();
	}
	void interactionWithMap()
	{
		for (int i = y / 50; i < (y + h) / 50; i++)
		{
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
				if (MAP[i][j] == '0' || (MAP[i][j] == '1'))
				{
					if (dy > 0)
					{
						y = i * 50 - h;
					}
					if (dy < 0)
					{
						y = i * 50 + 50;
					}
					if (dx > 0)
					{
						x = j * 50 - w;
					}
					if (dx < 0)
					{
						x = j * 50 + 50;
					}
				}


			}
		}

	}
		FloatRect getRect()
		{
			return FloatRect(x, y, w, h);
		}
	

};

class Enemy
{
public:

	float x, y, w, h, dx, dy, speed = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	int health = 8;
	bool life = 1;
	Enemy(String F, int X, int Y, float W, float H)
	{
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));


	}
	void move(float time)
	{
		speed = 0.05;
		dx = -speed;
		dy = 0;
		x += dx * time;
		y += dy * time;
		sprite.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()
	{
		for (int i = y / 50; i < (y + h) / 50; i++)
		{
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
				if (MAP[i][j] == '0')
				{
					if (dy > 0)
					{
						y = i * 50 - h;
					}
					if (dy < 0)
					{
						y = i * 50 + 50;
					}
					if (dx > 0)
					{
						x = j * 50 - w;
					}
					if (dx < 0)
					{
						x = j * 50 + 50;
					}
				}
				if (MAP[i][j] == '1')
				{
					exit(1);
				}


			}
		}

	}

	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}

};

class bullet
{
	public:

	float x, y, w, h, dx, dy = 0;
	float speed = 0.5;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	bool life = 1;
	bullet(String F, int X, int Y, float W, float H)
	{
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(0, 0, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h));


	}
	void move(float time)
	{
		dx = speed;
		dy = 0;
		x += dx * time;
		sprite.setPosition(x, y);
		interactionWithMap();
	}
	void interactionWithMap()
	{
		for (int i = y / 50; i < (y + h) / 50; i++)
		{
			for (int j = x / 50; j < (x + w) / 50; j++)
			{
			
		
				if (MAP[i][j] == '0')
				{
					life = false;
				}


			}
		}

	}
	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}



};

void Download(int& lvl, int& money, RenderWindow& window)
{
	const char ch = '\n';
	char array[2][10];
	ifstream fs("save.txt", ios::in);
	for (int r = 0; r < 2; r++)
	{
		fs.getline(array[r], 9, ch); 
	}
	fs.close();
	downloadlvl = atoi(array[0]);
	downloadmoney = atoi(array[1]);

		
}

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
					Download(downloadlvl,downloadmoney, window);
					return;
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

void Saving(int lvl, int  money)
{
	char array[2][10];
	_itoa(lvl, array[0], 10);
	_itoa(money, array[1], 10);
	fstream fs("save.txt", ios::trunc | ios::out | ios::binary);
	fs << array[0];
	fs << '\n';
	fs << array[1];

}




int main()
{
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setStyle(Text::Bold);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image gun_up;
	gun_up.loadFromFile("images/up.png");
	gun_up.createMaskFromColor(Color(0, 0, 0));
	Texture gun;
	gun.loadFromImage(gun_up);
	Sprite s_gun;
	s_gun.setTexture(gun);
	s_gun.setPosition(100, 350);
	bool gunmark = 0;

	Image level_image;
	level_image.loadFromFile("images/levels.png");
	Texture levelT;
	levelT.loadFromImage(level_image);
	Sprite s_level;
	s_level.setTexture(levelT);
	s_level.setPosition(60, 350);

	Image saving_image;
	saving_image.loadFromFile("images/save.png");
	Texture Save;
	Save.loadFromImage(saving_image);
	Sprite s_save;
	s_save.setTexture(Save);
	s_save.setPosition(750, 350);
	bool savemark = 0;

	RenderWindow window(VideoMode(800, 400), "STILL ALIVE");


	Menu(window);


	


	Hero MainHero("lvl1.png", 250, 250, 83.0, 92.0);
	MainHero.lvl = downloadlvl;
	


	int randomspawn;
	randomspawn = rand() % 2 + 1;
	std::list<Enemy*>  zombies;
	std::list<Enemy*>::iterator it;
	if(randomspawn == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			zombies.push_back(new Enemy("Zombie.png", 750 + 10 * i, 50 + 80 * i, 89.0, 92.0));
		}		
	}
	if (randomspawn == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			zombies.push_back(new Enemy("Zombie.png", 750 - 10 * i, 210 - 80 * i, 89.0, 92.0));
		}
	}

	std::list<bullet*>  bullets;
	std::list<bullet*>::iterator itt;
	bool bull;



	float CurrentFrame = 0;
	Clock clock;
	Clock moneyclock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		float timeismoney = moneyclock.getElapsedTime().asSeconds();
		float pasttimeismoney = 0;
		MainHero.money = downloadmoney + timeismoney - pasttimeismoney;
		pasttimeismoney = timeismoney;
		clock.restart();
		time = time / 800;


		s_gun.setColor(Color::White);
		gunmark = 0;

		s_save.setColor(Color::White);
		savemark = 0;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			bull = 1;
			if ((Keyboard::isKeyPressed(Keyboard::Space)))
			{
				if (bull == true)
				{
					bullets.push_back(new bullet("bullet.png", MainHero.x, MainHero.y, 16.0, 16.0));
					bull = false;
				}
			}
		}
		if (MainHero.life == 0 || MainHero.health <= 0)
		{
			window.close();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) 
		{
			MainHero.movemark = 1; MainHero.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		{
			MainHero.movemark = 0; MainHero.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		{
			MainHero.movemark = 3; MainHero.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;

		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))))
		{
			MainHero.movemark = 2; MainHero.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3; 
		}
		
		if ((IntRect(100, 350, 35, 35).contains(Mouse::getPosition(window))))
		{
			if (MainHero.money >= 1000)
			{
				s_gun.setColor(Color::Green);
				gunmark = 1;
			}
			else
			{
				s_gun.setColor(Color::Red);
			}
		}
		if ((IntRect(750, 350, 35, 35).contains(Mouse::getPosition(window))))
		{
			s_save.setColor(Color::Green);
			savemark = 1;
		}
		if ((Mouse::isButtonPressed(Mouse::Left)))
		{
			if (gunmark == 1)
			{
				if (MainHero.lvl != 4)
				{
					MainHero.lvl++;
					downloadmoney = downloadmoney - 1000;
				}
			}
			if (savemark == 1)
			{
				Saving(MainHero.lvl, MainHero.money);
				return 0;
			}
		}

		MainHero.move(time);



		for (it = zombies.begin(); it != zombies.end();)
		{
			Enemy* b = *it;
			b->move(time);
			if (b->life == false)
			{
				it = zombies.erase(it);
				delete b;
			}
			else it++;
		}
		for (it = zombies.begin(); it != zombies.end(); it++)
		{
			if ((*it)->getRect().intersects(MainHero.getRect()))
			{
				
				MainHero.health -= 100;
				
			}
		}
		for (it = zombies.begin(); it != zombies.end(); it++)
		{
			for ( itt = bullets.begin(); itt != bullets.end(); itt++)
			{
				if ((*it)->getRect().intersects((*itt)->getRect()))
				{
					(*itt)->life = false;
					if (MainHero.lvl == 1)
					{
						if ((*it)->health == 1)
						{
							(*it)->x = 950;
							downloadmoney += 25;
							(*it)->health = 8;
						}
						(*it)->health -= 1;
					}
					if (MainHero.lvl == 2)
					{
						if ((*it)->health <= 2)
						{
							(*it)->x = 950;
							downloadmoney += 25;
							(*it)->health = 8;
						}
						(*it)->health -= 2;
					}
					if (MainHero.lvl == 3)
					{
						if ((*it)->health <= 3)
						{
							(*it)->x = 950;
							downloadmoney += 25;
							(*it)->health = 8;
						}
						(*it)->health -= 3;
					}
					if (MainHero.lvl == 4)
					{
						if ((*it)->health <= 4)
						{
							(*it)->x = 950;
							downloadmoney += 25;
							(*it)->health = 8;
						}
						(*it)->health -= 4;
					}

				
				}
			}
		}
		for (itt = bullets.begin(); itt != bullets.end();)
		{
			bullet* a = *itt;
			a->move(time);
			if (a->life == false)
			{
				itt = bullets.erase(itt);
				delete a;

			}
			else itt++;
		}

		window.clear();
		for (int i = 0; i < MAP_H; i++)
		{
			for (int j = 0; j < MAP_W; j++)
			{
				if (MAP[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 50, 50)); 
				if (MAP[i][j] == '0')  s_map.setTextureRect(IntRect(50, 0, 100, 100));
				if (MAP[i][j] == '1')  s_map.setTextureRect(IntRect(100, 0, 150, 100));


				s_map.setPosition(j * 50, i * 50);
				window.draw(s_map);

			}
		}
		if (MainHero.lvl == 1)
		{
			s_level.setTextureRect(IntRect(0, 0, 35, 35));
			MainHero.image.loadFromFile("images/lvl1.png");
			MainHero.texture.loadFromImage(MainHero.image);
			MainHero.sprite.setTexture(MainHero.texture);
			window.draw(s_level);
		}
		if (MainHero.lvl == 2)
		{
			s_level.setTextureRect(IntRect(35, 0, 30, 35));
			MainHero.image.loadFromFile("images/lvl2.png");
			MainHero.texture.loadFromImage(MainHero.image);
			MainHero.sprite.setTexture(MainHero.texture);
			window.draw(s_level);
		}
		if (MainHero.lvl == 3)
		{
			s_level.setTextureRect(IntRect(60, 0, 40, 35));
			MainHero.image.loadFromFile("images/lvl3.png");
			MainHero.texture.loadFromImage(MainHero.image);
			MainHero.sprite.setTexture(MainHero.texture);
			window.draw(s_level);
		}
		if (MainHero.lvl == 4)
		{
			s_level.setTextureRect(IntRect(95, 0, 40 , 35));
			MainHero.image.loadFromFile("images/lvl4.png");
			MainHero.texture.loadFromImage(MainHero.image);
			MainHero.sprite.setTexture(MainHero.texture);
			window.draw(s_level);
		}
		ostringstream HealthStr,MoneyStr;
		HealthStr << MainHero.health;
		MoneyStr << MainHero.money;
		text.setString("Здоровье: " + HealthStr.str() + "\nДеньги: " + MoneyStr.str());
		text.setPosition(10, 8);
		window.draw(text);


		window.draw(MainHero.sprite);


		for (it = zombies.begin(); it != zombies.end(); it++)
		{
			window.draw((*it)->sprite); 
		}

		for (auto a : bullets)
		{
		  window.draw(a->sprite);
		}
		

		window.draw(s_gun);

		window.draw(s_save);


		window.display();
	}

	return 0;
}