//Pixel Art application

#include <iostream>
#include <memory>
#include <array>
#define SDL_MAIN_HANDLED //there is a main in SDL_main.h that causes Linker entry point error without this #define
#include "SDL.h"
#include "Coordinates.hpp"
#include "Screen.hpp"
#include "UserInput.hpp"
#include "Button.hpp"
#include "Grid.hpp"
#include "Vertex.hpp"

using namespace paint;


int main()
//int main()
{
    if (Screen::initialize())
    {
        std::cout << "SDL initialized" << std::endl;
    }


    Grid grid(32, 24);
    grid.setVertexType(0, 0, VertexType::Wall);
    grid.setVertexType(31, 0, VertexType::Wall);
    grid.setVertexType(0, 23, VertexType::Wall);
    grid.setVertexType(31, 23, VertexType::Wall);
    grid.setVertexType(0, 0, VertexType::Start);
    grid.setVertexType(31, 0, VertexType::End);

    grid.setVertexType(12, 5, VertexType::Wall);
    grid.setVertexType(12, 6, VertexType::Wall);
    grid.setVertexType(12, 7, VertexType::Wall);
    grid.setVertexType(12, 8, VertexType::Wall);
    grid.setVertexType(12, 9, VertexType::Wall);
    grid.setVertexType(12, 10, VertexType::Wall);

    grid.setVertexType(0, 12, VertexType::Wall);
    grid.setVertexType(1, 12, VertexType::Wall);
    grid.setVertexType(2, 12, VertexType::Wall);
    grid.setVertexType(3, 12, VertexType::Wall);
    grid.setVertexType(4, 12, VertexType::Wall);

    //obstacles
    for(int i = 0; i < 23; ++i) {
        grid.setVertexType(8, i, VertexType::Wall);
    }
    for(int i = 8; i < 24; ++i) {
        grid.setVertexType(16, i, VertexType::Wall);
    }
    for(int i = 0; i < 15; ++i) {
        grid.setVertexType(24, i, VertexType::Wall);
    }

    grid.computePath();


    //windows
    Window mainWindow("Paint", 800, 600);
    mainWindow.drawBackground();
    mainWindow.setColor(200, 200, 255);
    mainWindow.drawBackground();
    Window colorWindow("Color", 300, 200);
    colorWindow.setColor(200, 255, 200);
    colorWindow.drawBackground();

    //buttons
    Button button(&mainWindow, {0, 0}, 200, 200);
    Button button3(&mainWindow, {500, 500}, 100, 100);
    Button button2(&colorWindow, {0, 0}, 100, 100);
    UserInput userinput;
    bool appOpen = true;
    while (appOpen)
    {
        std::vector<Inputs> inputs = userinput.processEvents(mainWindow, colorWindow);
        for (Inputs input : inputs)
        {
            switch (input)
            {
            case Inputs::MouseLeft:
            {
                break;
            }
            case Inputs::MouseRight:
            {
                break;
            }
            case Inputs::CloseColorWindow:
            {
                colorWindow.close();
                break;
            }
            case Inputs::CloseMainWindow:
            {
                mainWindow.close();
                appOpen = false;
                break;
            }
            case Inputs::CloseApplication:
            {
                appOpen = false;
                break;
            }
            default:
                break;
            }
        }

        //get currently active window
        Window *activeWindow = nullptr;
        if (mainWindow.isActive())
        {
            activeWindow = &mainWindow;
        }
        else if (colorWindow.isActive())
        {
            activeWindow = &colorWindow;
        }

        //update button states
        if (button.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button.setState(State::Hover);
        }
        else
        {
            button.setState(State::Idle);
        }
        if (button3.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button3.setState(State::Hover);
        }
        else
        {
            button3.setState(State::Idle);
        }

        //update button states
        if (button2.mouseHover(activeWindow, userinput.getMouseCoordinates()))
        {
            button2.setState(State::Hover);
        }
        else
        {
            button2.setState(State::Idle);
        }

        button.update();
        button2.update();
        button3.update();

        //draw grid
        for (int col = 0; col < 32; ++col)
        {
            for (int row = 0; row < 24; ++row)
            {
                VertexType type = grid.getVertexType(col, row);
                switch (type)
                {
                case VertexType::Wall:
                    mainWindow.setColor(0, 0, 0);
                    break;
                case VertexType::Unvisited:
                    mainWindow.setColor(255, 255, 255);
                    break;
                case VertexType::Visited:
                    mainWindow.setColor(255, 255, 255);
                    break;
                case VertexType::Start:
                    mainWindow.setColor(150, 150, 255);
                    break;
                case VertexType::End:
                    mainWindow.setColor(100, 255, 100);
                    break;
                default:
                    mainWindow.setColor(255, 255, 255);
                    break;
                }

                mainWindow.drawRectangle({col * 25, row * 25}, {col * 25 + 25, row * 25 + 25});
            }
        }

        

        mainWindow.setColor(150, 150, 150);
        //draw grid lines
        for (int col = 25; col < 800; col += 25)
        {
            mainWindow.drawLine({col, 0}, {col, 600});
        }
        for (int row = 25; row < 600; row += 25)
        {
            mainWindow.drawLine({0, row}, {800, row});
        }
        mainWindow.render();
        colorWindow.render();
    }

    colorWindow.close();
    mainWindow.close();
    Screen::close();

    std::cout << "SDL shutdown" << std::endl;
    return 0;
}