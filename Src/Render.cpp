#include "../Inc/Render.hpp"


void Render::Prep()
{
    glClearColor( 0.3f, 0.6f, 0.8f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Render::SetProjection( GLfloat const &tmp_zoom )
{
    this->projection = glm::perspective( tmp_zoom, 640.0f / 640.0f, 1.0f, 10000.0f);
}

void Render::SetViewMatrix( glm::mat4 const &tmp_matrix )
{
    this->view_matrix = tmp_matrix;
}

void Render::Render_( Text_Model &tmp, Shaders &shader )
{
    this->modelLoc = shader.GetUniformLocation( "model" );
    this->projLoc = shader.GetUniformLocation( "projection" );
    this->viewLoc = shader.GetUniformLocation( "view" );
    this->lightLoc = shader.GetUniformLocation( "light_pos" );
    this->colourLoc = shader.GetUniformLocation( "light_colour" );
    this->shineLoc = shader.GetUniformLocation( "shine_damper" );
    this->reflectionLoc = shader.GetUniformLocation( "reflection" );

    shader.load_float( this->shineLoc, 23.0f);
    shader.load_float( this->reflectionLoc, 1.0f);

    shader.load_matrix( this->projLoc, this->projection );
    shader.load_matrix( this->viewLoc, this->view_matrix );

    shader.load_vect( this->lightLoc, this->light->GetPosition() );
    shader.load_vect( this->colourLoc, this->light->GetColour() );

    glm::mat4 model;

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f) );

    shader.load_matrix( this->modelLoc, model );

    glBindVertexArray( tmp.GetModel().GetVAO() );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    //glActiveTexture( GL_TEXTURE0 );
    glBindTexture(GL_TEXTURE_2D, tmp.GetModelText().GetTextureID());
    glUniform1i( glGetUniformLocation(shader.GetProgramID(), "Texture_"), 0.0f );

    glDrawElements( GL_TRIANGLES, tmp.GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    glBindVertexArray( 0 );
}
