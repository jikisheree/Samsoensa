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

    RenderWindow app(VideoMode(400, 533), "Raise dumb!");
    app.setFramerateLimit(60);

    Texture x1, x2, x3;
    x1.loadFromFile("images/bg1.png");
    x2.loadFromFile("images/platform.png");
    x3.loadFromFile("images/cat.png");

    Sprite sBackground(x1), sPlat(x2), sChars(x3);
    sBackground.setTextureRect(IntRect(0, 0, 400, 533));

    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        app.draw(sBackground);
        app.draw(sChars);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    return 0;
}