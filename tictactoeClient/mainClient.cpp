#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <vector>
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")



int main(int argc, char** argv)
{
    //hide window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE); //SW_HIDE for hinding, SW_NORMAL for showing

    //Création d'une fenêtre
    int width = 900;
    int height = 900;
    sf::RenderWindow oWindow(sf::VideoMode(width, height), "SFML");

    WSADATA WSAData;
    WSAStartup(MAKEWORD(1, 0), &WSAData);

    SOCKET sock;
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(2735);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (SOCKADDR*)&sin, sizeof(sin));

    connect(sock, (SOCKADDR*)&sin, sizeof(sin));

    //Tableau
    int grid[3][3];

    //GameLoop
    sf::Clock oClock;
    float fDeltaTime;

    float mX;
    float mY;
    int inputX;
    int inputY;
    int tour = 0;

    while (oWindow.isOpen())
    {

        fDeltaTime = oClock.restart().asSeconds();

        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }

        //UPDATE

        mX = sf::Mouse::getPosition(oWindow).x;
        mY = sf::Mouse::getPosition(oWindow).y;


        if (oEvent.type == sf::Event::MouseButtonPressed)
        {
            if (oEvent.mouseButton.button == sf::Mouse::Left)
            {
                if (tour % 2 == 0)
                {
                    if (mX < 300)
                    {
                        inputX = 0;
                    }
                    if (mX > 300 && mX < 600)
                    {
                        inputX = 1;
                    }
                    if (mX > 600)
                    {
                        inputX = 2;
                    }

                    if (mY < 300)
                    {
                        inputY = 0;
                    }
                    if (mY > 300 && mY < 600)
                    {
                        inputY = 1;
                    }
                    if (mY > 600)
                    {
                        inputY = 2;
                    }

                    if (grid[inputX][inputY] != 'X' && grid[inputX][inputY] != 'O') {
                        grid[inputX][inputY] = 'X';
                        tour += 1;
                    }

                }
                else if (tour % 2 == 1)
                {
                    if (mX < 300)
                    {
                        inputX = 0;
                    }
                    if (mX > 300 && mX < 600)
                    {
                        inputX = 1;
                    }
                    if (mX > 600)
                    {
                        inputX = 2;
                    }

                    if (mY < 300)
                    {
                        inputY = 0;
                    }
                    if (mY > 300 && mY < 600)
                    {
                        inputY = 1;
                    }
                    if (mY > 600)
                    {
                        inputY = 2;
                    }

                    if (grid[inputX][inputY] != 'X' && grid[inputX][inputY] != 'O') {
                        grid[inputX][inputY] = 'O';
                        tour += 1;
                    }
                }
            }
        }



        //DRAW
        oWindow.clear();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == 'X')
                {
                    int shapeX = i * 300 + 150;
                    int shapeY = j * 300 + 150;

                    sf::RectangleShape line(sf::Vector2f(150, 5));
                    line.setFillColor(sf::Color(0, 0, 255));
                    line.setOrigin(75, 2.5);
                    line.setPosition(shapeX, shapeY);
                    line.rotate(45);
                    oWindow.draw(line);

                    sf::RectangleShape line2(sf::Vector2f(150, 5));
                    line2.setFillColor(sf::Color(0, 0, 255));
                    line2.setOrigin(75, 2.5);
                    line2.setPosition(shapeX, shapeY);
                    line2.rotate(135);
                    oWindow.draw(line2);
                }
                else if (grid[i][j] == 'O')
                {
                    int shapeX = i * 300 + 75;
                    int shapeY = j * 300 + 75;

                    sf::CircleShape circle(75);
                    circle.setOutlineThickness(-5);
                    circle.setOutlineColor(sf::Color(255, 0, 0));
                    circle.setFillColor(sf::Color::Transparent);
                    circle.setPosition(shapeX, shapeY);
                    oWindow.draw(circle);
                }
            }
        }

        sf::RectangleShape gridLine(sf::Vector2f(5, 900));
        gridLine.setFillColor(sf::Color(255, 255, 255));
        gridLine.setPosition(298, 0);
        oWindow.draw(gridLine);

        sf::RectangleShape gridLine2(sf::Vector2f(5, 900));
        gridLine2.setFillColor(sf::Color(255, 255, 255));
        gridLine2.setPosition(598, 0);
        oWindow.draw(gridLine2);

        sf::RectangleShape gridLine3(sf::Vector2f(900, 5));
        gridLine3.setFillColor(sf::Color(255, 255, 255));
        gridLine3.setPosition(0, 298);
        oWindow.draw(gridLine3);

        sf::RectangleShape gridLine4(sf::Vector2f(900, 5));
        gridLine4.setFillColor(sf::Color(255, 255, 255));
        gridLine4.setPosition(0, 598);
        oWindow.draw(gridLine4);

        oWindow.display();
    }
    WSACleanup();
    return 0;
}

