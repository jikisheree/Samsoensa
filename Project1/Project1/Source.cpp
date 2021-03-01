#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(600, 853), "Raise dumb!");
    app.setFramerateLimit(60);

    //open music from file & set loop/volume.
    Music musicmenu, musicgame;
    musicmenu.openFromFile("sounds/lala.wav");
    musicgame.openFromFile("sounds/butter_building.wav");

    musicmenu.play();
    musicmenu.setVolume(5);
    musicgame.setVolume(2);
    musicgame.setLoop(true);
    musicmenu.setLoop(true);

    Texture x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20;
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

    Sprite sBackgroundGame(x1), sPlat(x2), sChars(x3), sBackgroundMainMenu(x4), sPlayButton(x5), sQuitButton(x6),
        sBGgameover(x9), sgameover(x10), sNewGameButton(x11), sQuitGOButton(x13),sReplayButton(x17),
        sResumeButton(x19),sBackgroundPause(x16);

    Sprite plat[36];

    // random & check platform 
    for (int i = 0; i < 6; i++)
    {
        plat[i].setOrigin(0, 0);
        plat[i] = sPlat;
        plat[i].setPosition(rand() % 500, rand() % 853);
        for (int j = 0; j != i;j++)
        {
           if (plat[i].getPosition().y > plat[j].getPosition().y - 100
               && plat[i].getPosition().y < plat[j].getPosition().y + 100)
            {
               i--;
               break;
            }
        }
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    enum States { MainMenu , Game , GameOver ,Pause};
    short unsigned currentState = MainMenu;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        switch (currentState)
        {
        case MainMenu:
            sPlayButton.setPosition(82, 236);
            sQuitButton.setPosition(92, 358);
            sPlayButton.setTexture(x5);
            sQuitButton.setTexture(x6);
            //playbutton
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                sPlayButton.setTexture(x7);
                currentState = Game;
                musicmenu.stop();
                musicgame.play();
            }
            if (sPlayButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
            {
                sPlayButton.setTexture(x7);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    currentState = Game;
                    musicmenu.stop();
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
            app.draw(sBackgroundMainMenu);
            app.draw(sPlayButton);
            app.draw(sQuitButton);
            
            break;
        case Game:
            if (Keyboard::isKeyPressed(Keyboard::Right) or Keyboard::isKeyPressed(Keyboard::D)) x += 4.5;
            if (Keyboard::isKeyPressed(Keyboard::Left) or Keyboard::isKeyPressed(Keyboard::A)) x -= 4.5;
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                currentState = Pause;
                musicgame.pause();
            }
            dy += 0.49;
            y += dy;
            if (y > 853)
            {
                currentState = GameOver;
                musicgame.pause();
            }

            //jump
            for (int i = 0; i < 6; i++)
            {
                if ((x + 65 > plat[i].getPosition().x) && (x + 30 < plat[i].getPosition().x + 112) &&
                    (y + 125 > plat[i].getPosition().y) && (y + 125 < plat[i].getPosition().y + 40) && (dy > 0)) dy = -20;
            }

            //Move the platform down and set new paltform position
            if (y < h)
            {
                for (int i = 0; i < 6; i++)
                {
                    y = h;
                    plat[i].setPosition(plat[i].getPosition().x, plat[i].getPosition().y - dy);
                    if (plat[i].getPosition().y > 853) {plat[i].setPosition(rand() % 500, -100);}
                }
            }

            sChars.setPosition(x, y);
            //render
            app.draw(sBackgroundGame);
            for (int i = 0; i < 6; i++)
            {
                app.draw(plat[i]);
            }
            app.draw(sChars);
            break;
        case GameOver:
            sgameover.setPosition(22, 78);
            sNewGameButton.setPosition(155, 549);
            sQuitGOButton.setPosition(233, 678);
            sNewGameButton.setTexture(x11);
            sQuitGOButton.setTexture(x13);

            //newgamebutton
            if (sNewGameButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))) || Keyboard::isKeyPressed(Keyboard::Enter))
            {
                sNewGameButton.setTexture(x12);
                if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    currentState = Game;
                    musicgame.stop();
                    musicgame.play();
                    //newgame set cat&plat position
                    x = 100;
                    y = 100;
                    dy = 0;
                    for (int i = 0; i < 6; i++)
                    {
                        plat[i] = sPlat;
                        plat[i].setPosition(rand() % 500, rand() % 853);
                        for (int j = 0; j != i; j++)
                        {
                            if (plat[i].getPosition().y > (plat[j].getPosition().y - 100)
                                && plat[i].getPosition().y < (plat[j].getPosition().y + 100))
                            {
                                i--;
                                break;
                            }
                        }
                    }
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
            app.draw(sBGgameover);
            app.draw(sgameover);
            app.draw(sNewGameButton);
            app.draw(sQuitGOButton);
            break;
        case Pause:
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
            }
            if (sResumeButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
            {
                sResumeButton.setTexture(x20);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    currentState = Game;
                    musicgame.play();
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
                    //set new cat&plat position
                    x = 100;
                    y = 100;
                    dy = 0;
                    for (int i = 0; i < 6; i++)
                    {
                        plat[i] = sPlat;
                        plat[i].setPosition(rand() % 500, rand() % 853);
                        for (int j = 0; j != i; j++)
                        {
                            if (plat[i].getPosition().y > (plat[j].getPosition().y - 100)
                                && plat[i].getPosition().y < (plat[j].getPosition().y + 100))
                            {
                                i--;
                                break;
                            }
                        }
                    }
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