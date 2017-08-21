#pragma once

#include "Base.hpp"
#include "Text_Model.hpp"
#include "Shaders.hpp"
#include "Light_class.hpp"

class Render
{
    private:
        glm::mat4 projection;
        glm::mat4 view_matrix;

        GLint modelLoc;
        GLint projLoc;
        GLint viewLoc;
        GLint lightLoc;
        GLint colourLoc;
        GLint shineLoc;
        GLint reflectionLoc;

        Light_class *light = new Light_class( glm::vec3(0.0f, 4.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f) );

    public:

        void SetViewMatrix( glm::mat4 const &tmp_matrix );
        void SetProjection( GLfloat const &tmp_zoom );
        void Load_Uniform( Shaders &shader );
        void Prep();
        void Render_( Text_Model &tmp, Shaders &shader );

};
