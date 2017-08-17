#include "../Inc/Render_Engine.hpp"

int main()
{
    Render_Engine tmp("DEZZ NUTZ", 640, 640);

    tmp.init();
    tmp._render();

    return (0);
}
