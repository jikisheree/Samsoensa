#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

struct point
{
    int x, y;
};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(600, 853), "Raise dumb!");
    app.setFramerateLimit(60);

    Texture x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14;
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


    Sprite sBackgroundGame(x1), sPlat(x2), sChars(x3), sBackgroundMainMenu(x4), sPlayButton(x5), sQuitButton(x6),
        sBGgameover(x9), sgameover(x10), sNewGameButton(x11), sQuitGOButton(x13);

    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % 600;
        plat[i].y = rand() % 853;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    enum States { MainMenu , Game , GameOver };
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
            if (Keyboard::isKeyPressed(Keyboard::Enter)) currentState = Game;
            if (sPlayButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
            {
                sPlayButton.setTexture(x7);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    currentState = Game;
                    x = 100;
                    y = 100;
                    dy = 0;
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
            // jump
            if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
            if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;
            if (Keyboard::isKeyPressed(Keyboard::Escape)) currentState = MainMenu;
            dy += 0.5;
            y += dy;
            if (y > 853) currentState = GameOver;

            if (y < h)
                for (int i = 0; i < 10; i++)
                {
                    y = h;
                    plat[i].y = plat[i].y - dy;
                    if (plat[i].y > 853) { plat[i].y = 0; plat[i].x = rand() % 300; }
                }

            for (int i = 0; i < 10; i++)
                if ((x + 100 > plat[i].x) && (x + 40 < plat[i].x + 140) &&
                    (y + 140 > plat[i].y) && (y + 140 < plat[i].y + 40) && (dy > 0)) dy = -20;

            sChars.setPosition(x, y);

            app.draw(sBackgroundGame);
            for (int i = 0; i < 10; i++)
            {
                sPlat.setPosition(plat[i].x, plat[i].y);
                app.draw(sPlat);
            }
            app.draw(sChars);

 
            break;
        case GameOver:
            sgameover.setPosition(22, 78);
            sNewGameButton.setPosition(155, 549);
            sQuitGOButton.setPosition(233, 678);
            sNewGameButton.setTexture(x11);
            sQuitGOButton.setTexture(x13);

            if (sNewGameButton.getGlobalBounds().contains(app.mapPixelToCoords(Mouse::getPosition(app))))
            {
                sNewGameButton.setTexture(x12);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    currentState = Game;
                    x = 100;
                    y = 100;
                    dy = 0;
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
        default:
            break;
        }

        app.display();
    }

    return 0;
}

/* Test pushing */