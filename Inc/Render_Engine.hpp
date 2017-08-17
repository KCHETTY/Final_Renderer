#pragma once

#include "Base.hpp"
#include "Data_Loader.hpp"
#include "Render.hpp"
#include "Model.hpp"
#include "Shaders.hpp"
#include "Model_Text.hpp"
#include "Text_Model.hpp"
#include "Object_Loader.hpp"
#include "Camera.hpp"
#include "Component.hpp"
#include "Light_class.hpp"

class Render_Engine
{
    private:

        std::string Win_Name;
        int Screen_Width;
        int Screen_Height;

        static GLFWwindow *window;
        static Camera *camera;

        static GLfloat lastX;
        static GLfloat lastY;

        static bool keys[1024];
        static bool firstmouse ;

        static GLfloat deltaTime;
        static GLfloat lastFrame;

        Render_Engine();

    public:

        Render_Engine( std::string Win_Name, int Win_Width, int Win_Height);
        ~Render_Engine();

        void init();
        void _render();
        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
        static void MouseCallback( GLFWwindow *window, double posX, double posY );
        void DoMovement();

};
