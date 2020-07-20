#include "application.hpp"

int main(int count, char **args)
{
    Application app;

    while(!app.Done())
    {
        app.Update();
    }

    return 0;
}