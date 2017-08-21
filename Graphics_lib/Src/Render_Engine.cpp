#include "../Inc/Render_Engine.hpp"

GLFWwindow *Render_Engine::window = nullptr;
Camera *Render_Engine::camera = nullptr;

bool Render_Engine::firstmouse = true;
GLfloat Render_Engine::deltaTime = 0.0f;
GLfloat Render_Engine::lastFrame = 0.0f;

GLfloat Render_Engine::lastX = 0.0f;
GLfloat Render_Engine::lastY = 0.0f;

bool Render_Engine::keys[1024];

Render_Engine::Render_Engine()
{
    return ;
}

Render_Engine::Render_Engine( std::string Win_Name, int Win_Width, int Win_Height)
{
    this->Win_Name = Win_Name;
    this->Screen_Height = Win_Height;
    this->Screen_Width = Win_Width;
}

Render_Engine::~Render_Engine()
{
    return ;
}

void Render_Engine::_render()
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );


    Model tmp = obj_load.Load_Object("/home/kchetty/Desktop/tmper/Object_files/nanosuit.obj");

    GLuint ye = load.load_texture("/home/kchetty/Desktop/tmper/Textures/gras.png");
    Model_Text tmo_nmoi( ye );

    std::cout << "Bef TEXT MODEL " << std::endl;

    Text_Model ne( tmp, tmo_nmoi );


    std::cout << "BEF LOOP " << std::endl;
    while ( !glfwWindowShouldClose( window ) )
    {
        GLfloat current_time = glfwGetTime();
        Render_Engine::deltaTime = current_time - Render_Engine::lastFrame;
        Render_Engine::lastFrame = current_time;

        glfwPollEvents( ); // poll for and process events
        DoMovement();

        glUseProgram( this->shader.GetProgramID() );

        this->draw.SetProjection( Render_Engine::camera->GetZoom() );

        this->draw.Prep();

        //projection = glm::perspective( Render_Engine::camera->GetZoom() , (GLfloat)this->Screen_Width / (GLfloat)this->Screen_Height, 1.0f, 10000.0f);

        //glm::mat4 model_matrix;
        //model_matrix = glm::rotate( model_matrix, (GLfloat)glfwGetTime() * 1.0f, glm::vec3( 0.5f, 1.0f, 0.0f ));
        //view_matrix = glm::translate( view_matrix, glm::vec3( 0.0f, 0.0f, -2.0f) );
        this->draw.SetViewMatrix(camera->GetViewMatrix());

        //GLfloat angle = 20.0f * x;
        //model = glm::rotate( model, angle, glm::vec3( 0.0f, 0.0f, 0.0f ));

        this->draw.Render_( ne, this->shader );

        glfwSwapBuffers( Render_Engine::window );
    }
}

void Render_Engine::init()
{
    if( !glfwInit() )
    {
        std::cout << "Bad news1" << std::endl;
        exit(1);
    }

    // open a window with GLFW, sets required GLFW options
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    Render_Engine::window = glfwCreateWindow( this->Screen_Width, this->Screen_Height, this->Win_Name.c_str(), nullptr, nullptr ); //Create GLFW window

    if ( !Render_Engine::window ) // Check if window was created
    {
        std::cout << "Bad news2" << std::endl;
        glfwTerminate(); // Terminate GLFW
        exit(2);
    }

    glfwMakeContextCurrent( Render_Engine::window ); // Make the windows context current
    glfwGetFramebufferSize( Render_Engine::window, &this->Screen_Width, &this->Screen_Height );

    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if( glewInit() != GLEW_OK )
    {
        std::cout << "Bad news 3" << std::endl;
        exit(3);
    }

    glfwSetKeyCallback( Render_Engine::window, KeyCallback);
    glfwSetScrollCallback( Render_Engine::window, ScrollCallback);
    glfwSetCursorPosCallback( Render_Engine::window, MouseCallback);

    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    Render_Engine::camera = new Camera( glm::vec3( 0.0f, 0.0f, 3.0f) );
    lastX = this->Screen_Width / 2.0f;
    lastY = this->Screen_Height / 2.0f;

    this->shader.compile_shaders("/home/kchetty/Desktop/tmper/Shaders/Colour_Shading.vert", "/home/kchetty/Desktop/tmper/Shaders/Colour_Shasiner.frag");

    this->draw.Load_Uniform( this->shader );

    glViewport( 0.0f, 0.0f, this->Screen_Width, this->Screen_Height ); //this->Screen_Width, this->Screen_Height ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalized to pixels.
}

void Render_Engine::KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose( window, GL_TRUE);

    if ( key >= 0 && key < 1024)
    {
        if ( GLFW_PRESS == action )
            keys[key] = true;
        else if ( GLFW_RELEASE == action )
            keys[key] = false;
    }
}

void Render_Engine::ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    camera->ProcessMouseScroll( yOffset );
}

void Render_Engine::MouseCallback( GLFWwindow *window, double posX, double posY )
{
    if ( firstmouse )
    {
        lastX = posX;
        lastY = posY;
        firstmouse = false;
    }

    GLfloat xOffset = posX - lastX;
    GLfloat yOffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    camera->ProcessMouseMovement( xOffset, yOffset );
}

void Render_Engine::DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
        camera->ProcessKeyboard( Camera_movement::FORWARD, deltaTime );
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
        camera->ProcessKeyboard( Camera_movement::BACKWARD, deltaTime );
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
        camera->ProcessKeyboard( Camera_movement::LEFT, deltaTime );
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
        camera->ProcessKeyboard( Camera_movement::RIGHT, deltaTime );
}
