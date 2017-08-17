#include "../Inc/Render_Engine.hpp"

int main()
{
    Render_Engine tmp("DEZZ NUTZ", 1920, 1080);

    tmp.init();
    tmp._render();

    return (0);
}
