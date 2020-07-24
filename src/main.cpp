#include "application.hpp"

int main(int count, char **args)
{
    (void)count;
    (void)args;
    Application app;
    app.Init();

    while(!app.Done())
    {
        app.Update();
    }

    return 0;
}