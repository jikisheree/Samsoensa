#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "time.h"
#include <iostream>
#include <list>
#include <cmath>

using namespace sf;
using namespace std;

bool checkPlat(Sprite& sPlat,list<Sprite> plats) // Check the platform if it's close to other platforms.
{
	for (auto i = plats.begin(); i != plats.end(); i++)
	{
		if (pow((sPlat.getPosition().x - i->getPosition().x),2) + pow((sPlat.getPosition().y - i->getPosition().y),2) < 20000) {
			return false;
		}
	}
	return true;
}

int main()
{
	srand(time(0));

	Clock clock1, clock2;

	RenderWindow app(VideoMode(600, 853), "Let's Jump with Kitten!");
	app.setFramerateLimit(60);

	int x = 100, y = 100, h = 200;
	int scores = 0, highscore = 0;
	float dx = 0, dy = 0;
	enum States { MainMenu, Game, GameOver, Pause };
	short unsigned currentState = MainMenu;

	//open music from file
	Music musicmenu, musicgame, musicgameover;
	musicmenu.openFromFile("sounds/bgm.wav");
	musicgame.openFromFile("sounds/butter_building.wav");
	musicgameover.openFromFile("sounds/gameover.wav");
	//set loop/volume.
	musicmenu.play();
	musicmenu.setVolume(15);
	musicgame.setVolume(5);
	musicgameover.setVolume(4);
	musicgame.setLoop(true);
	musicmenu.setLoop(true);

	Texture x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23;
	x1.loadFromFile("images/bg1.jpg");
	x2.loadFromFile("images/platform.png");
	x3.loadFromFile("images/cat.png");
	x4.loadFromFile("images/bgmain.jpg");
	x5.loadFromFile("images/playButton.png");
	x6.loadFromFile("images/quitButton.png");
	x7.loadFromFile("images/playButton2.png");
	x8.loadFromFile("images/quitButton2.png");
	x9.loadFromFile("images/bgGameOver.png");
	x10.loadFromFile("images/gameOver.png");
	x11.loadFromFile("images/newGame.png");
	x12.loadFromFile("images/newGame2.png");
	x13.loadFromFile("images/quitButtonGO.png");
	x14.loadFromFile("images/quitButtonGO2.png");
	x15.loadFromFile("images/cat2.png");
	x16.loadFromFile("images/BGpause.png");
	x17.loadFromFile("images/replay.png");
	x18.loadFromFile("images/replay2.png");
	x19.loadFromFile("images/resume.png");
	x20.loadFromFile("images/resume2.png");
	x21.loadFromFile("images/dog.png");
	x22.loadFromFile("images/fish.png");
	x23.loadFromFile("images/circle.png");

	Sprite sBackgroundGame(x1), sPlat(x2), sChars(x3), sBackgroundMainMenu(x4), sPlayButton(x5), sQuitButton(x6),
		sBGgameover(x9), sgameover(x10), sNewGameButton(x11), sQuitGOButton(x13), sReplayButton(x17),
		sResumeButton(x19), sBackgroundPause(x16), sFish(x22), sBlackhole(x23);
	Sprite fish[10];
	Sprite* sDog = NULL;
	list<Sprite> plats;

	//load & set font
	Font font;
	font.loadFromFile("font/Pixeboy.ttf");
	Text scoretext, highscoretext;
	scoretext.setFillColor(Color::White);
	highscoretext.setFillColor(Color::White);
	scoretext.setFont(font);
	highscoretext.setFont(font);

	// random & check platform 
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	plats.push_back(sPlat);
	for (auto i = plats.begin(); i != plats.end(); i++)
	{
		i->setPosition(rand() % 500, rand() % 1353 - 500);
		for (auto j = plats.begin(); j != i; j++)
		{
			if (pow((i->getPosition().x - j->getPosition().x),2) + pow((i->getPosition().y - j->getPosition().y),2) < 20000) 
			{
				i = plats.begin();
				break;
			}
		}
	}
	//Random fish
	for (int i = 0; i < 10; i++)
	{
		fish[i] = sFish;
		fish[i].setPosition(rand() % 560, rand() % 840);
	}
	//set blackhole
	if (scores >= 400)
		sBlackhole.setPosition(rand() % 500, rand() % 780);
	
	while (app.isOpen())
	{
		//time condition
		float time1 = clock1.getElapsedTime().asSeconds();
		if (time1 > 3) {
			clock1.restart();
		}

		int time2 = clock2.getElapsedTime().asSeconds();

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		switch (currentState)
		{
		case MainMenu:
			//set everything
			sPlayButton.setPosition(82, 236);
			sQuitButton.setPosition(92, 358);
			sPlayButton.setTexture(x5);
			sQuitButton.setTexture(x6);

			//playbutton
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				sPlayButton.setTexture(x7);
				currentState = Game;
				musicmenu.pause();
				musicgame.play();
			}
			if (sPlayButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sPlayButton.setTexture(x7);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					currentState = Game;
					musicmenu.pause();
					musicgame.play();
				}
			}
			if (sQuitButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sQuitButton.setTexture(x8);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					app.close();
				}
			}

			//Render
			app.draw(sBackgroundMainMenu);
			app.draw(sPlayButton);
			app.draw(sQuitButton);
			break;
		case Game:

			//set bLackhole first position
			if (scores < 400)
				sBlackhole.setPosition(2000, 2000);

			//set scoretext
			scoretext.setCharacterSize(50);
			scoretext.setPosition(15, 3);
			scoretext.setString("Score : " + to_string(scores));

			if (Keyboard::isKeyPressed(Keyboard::Right) or Keyboard::isKeyPressed(Keyboard::D)) x += 4.5;
			if (Keyboard::isKeyPressed(Keyboard::Left) or Keyboard::isKeyPressed(Keyboard::A)) x -= 4.5;
			if (Keyboard::isKeyPressed(Keyboard::Escape) or Keyboard::isKeyPressed(Keyboard::Space))
			{
				currentState = Pause;
				musicgame.pause();
				musicmenu.play();
			}
			dy += 0.49;
			y += dy;

			//if charactor positoin out of window >> change to another side
			if (x > 600) x = -70;
			if (x < -sChars.getGlobalBounds().width) x = 600;

			//jump
			for (auto& i : plats)
			{
				if ((x + 65 > i.getPosition().x) && (x + 30 < i.getPosition().x + 112) &&
					(y + 125 > i.getPosition().y) && (y + 125 < i.getPosition().y + 40) && (dy > 0)) {
					dy = -20;
					sChars.setTexture(x15);
					if (time1 > 1.5) {
						sChars.setTexture(x3);
					}
				}
			}

		//Move the platform,fish and dog down and set new position
		if (y < h)
		{
			y = h;
			for (auto& i : plats)
			{
				i.setPosition(i.getPosition().x, i.getPosition().y - dy);
			}
			for (auto i = plats.begin(); i != plats.end(); i++)
			{
				if (i->getPosition().y > 853) {
					plats.erase(i);
					break;
				}
			}
			for (int i = 0; i < 10; i++)
			{
				fish[i].setPosition(fish[i].getPosition().x, fish[i].getPosition().y - dy);
				if (fish[i].getPosition().y > 853) { fish[i].setPosition(rand() % 560, -sFish.getGlobalBounds().height); }
			}
			if (sDog && sDog->getPosition().y > 853) {
				delete sDog;
				sDog = NULL;
			}
			if (sDog) sDog->setPosition(sDog->getPosition().x, sDog->getPosition().y - dy);
			if (plats.size() < 10)
			{
				sPlat.setPosition(rand() % 500, -500);
				if (checkPlat(sPlat, plats))
				{
					plats.push_back(sPlat);
					if (!sDog && scores >= 200 && rand () % 5 == 0)
					{
						sDog = new Sprite(x21);
						sDog->setPosition(plats.back().getPosition().x + 10, plats.back().getPosition().y - 115);
					}
				}
			}
			if (scores >= 400 && time2 > 15) {
				sBlackhole.setPosition(sBlackhole.getPosition().x, sBlackhole.getPosition().y - dy);
				if (sBlackhole.getPosition().y > 853) { sBlackhole.setPosition(rand() % 500, 200); }
				if (time2 > 20) {
					clock2.restart();
					sBlackhole.setPosition(1000, 1000);
				}
			}
		}

		//if cat Colliding with fish or dog then it dissappear
		for (int i = 0; i < 10; i++) {
			if (sChars.getGlobalBounds().intersects(fish[i].getGlobalBounds())) {
				scores += 5;
				fish[i].setPosition(rand() % 560, -sFish.getGlobalBounds().height); //set new position (dissappear)
			}
		}
		if (sDog && sChars.getGlobalBounds().intersects(sDog->getGlobalBounds())) {
			scores -= 20;
			delete sDog;
			sDog = NULL;
		}
		// meet blackhole >> gameover
		if (scores >= 200) {
			if (sChars.getGlobalBounds().intersects(sBlackhole.getGlobalBounds())) {
				currentState = GameOver;
			}
		}

		//GameOver
		if (y > 853)
		{
			if (scores > highscore) highscore = scores; //Check the score at the end of the game.
			currentState = GameOver;
			musicgame.pause();
			musicgameover.play();
		}
		if (scores < 0)
		{
			scores = 0;
			currentState = GameOver;
			musicgame.pause();
			musicgameover.play();
		}

		//update cat position
		sChars.setPosition(x, y);

		//render
		app.draw(sBackgroundGame);
		for (auto& i : plats)
		{
			app.draw(i);
		}
		for (int i = 0; i < 10; i++)
		{
			app.draw(fish[i]);
		}
		if (sDog)
		{
			app.draw(*sDog);
		}
		if (scores >= 400)
		{
			app.draw(sBlackhole);
		}
		app.draw(sChars);
		app.draw(scoretext);
		break;
		case GameOver:
			//set everything
			sgameover.setPosition(22, 78);
			sNewGameButton.setPosition(155, 549);
			sQuitGOButton.setPosition(233, 678);
			sNewGameButton.setTexture(x11);
			sQuitGOButton.setTexture(x13);
			highscoretext.setCharacterSize(60);
			highscoretext.setPosition(45, 175);
			highscoretext.setString("HIGH SCORE : " + to_string(highscore));
			scoretext.setCharacterSize(60);
			scoretext.setPosition(45, 235);

			//newgamebutton
			if (sNewGameButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))) || Keyboard::isKeyPressed(Keyboard::Enter)
				or Keyboard::isKeyPressed(Keyboard::Space))
			{
				sNewGameButton.setTexture(x12);
				if (Mouse::isButtonPressed(Mouse::Left) or Keyboard::isKeyPressed(Keyboard::Enter) or Keyboard::isKeyPressed(Keyboard::Space))
				{
					currentState = Game;
					musicgame.stop();
					musicgame.play();
					musicgameover.stop();
					//newgame set cat&plat position
					x = 100;
					y = 100;
					dy = 0;
					for (auto i = plats.begin(); i != plats.end(); i++)
					{
						i->setPosition(rand() % 500, rand() % 1353 - 500);
						for (auto j = plats.begin(); j != i; j++)
						{
							if (pow((i->getPosition().x - j->getPosition().x), 2) + pow((i->getPosition().y - j->getPosition().y), 2) < 20000) 
							{
								i = plats.begin();
								break;
							}
						}
					}
					for (int i = 0; i < 10; i++)
					{
						fish[i] = sFish;
						fish[i].setPosition(rand() % 560, rand() % 840);
					}
					sDog = NULL;
				}
			}
			if (sQuitGOButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sQuitGOButton.setTexture(x14);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					app.close();
				}
			}

			//set scores 
			scores = 0;

			//Render
			app.draw(sBGgameover);
			app.draw(sgameover);
			app.draw(sNewGameButton);
			app.draw(sQuitGOButton);
			app.draw(highscoretext);
			app.draw(scoretext);
			break;
		case Pause:
			//set everything
			sResumeButton.setPosition(167, 182);
			sReplayButton.setPosition(165, 303);
			sQuitButton.setPosition(177, 421);
			sResumeButton.setTexture(x19);
			sReplayButton.setTexture(x17);
			sQuitButton.setTexture(x6);
			//resume
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				sResumeButton.setTexture(x20);
				currentState = Game;
				musicgame.play();
				musicmenu.pause();
			}
			if (sResumeButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sResumeButton.setTexture(x20);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					currentState = Game;
					musicgame.play();
					musicmenu.pause();
				}
			}
			// replay
			if (sReplayButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sReplayButton.setTexture(x18);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					currentState = Game;
					musicgame.stop();
					musicgame.play();
					musicmenu.pause();
					//set new cat&plat position
					x = 100;
					y = 100;
					dy = 0;
					for (auto i = plats.begin(); i != plats.end(); i++)
					{
						i->setPosition(rand() % 500, rand() % 1353 - 500);
						for (auto j = plats.begin(); j != i; j++)
						{
							if (pow((i->getPosition().x - j->getPosition().x), 2) + pow((i->getPosition().y - j->getPosition().y), 2) < 20000) 
							{
								i = plats.begin();
								break;
							}
						}
					}
					for (int i = 0; i < 10; i++)
					{
						fish[i] = sFish;
						fish[i].setPosition(rand() % 560, rand() % 840);
					}
					sDog = NULL;
				}
			}
			//Quit
			if (sQuitButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
			{
				sQuitButton.setTexture(x8);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					app.close();
				}
			}
			
			//Render
			app.draw(sBackgroundPause);
			app.draw(sResumeButton);
			app.draw(sReplayButton);
			app.draw(sQuitButton);
			break;
		default:
			break;
	}
	app.display();
}
return 0;
}