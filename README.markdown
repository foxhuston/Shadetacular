Shadetacular
============

Shadetacular will help you:

*  Use shader programs.
*  Write cleaner C++ code.
*  Do your laundry.

Seriously.

## Use and Inner Workings ##

The very first thing you have to do is include the two header files (in this order):

    #include <coordinate.hpp>
    #include <shader.hpp>

When it reads the file, it builds a std::map< string, ShaderParameter >
out of the uniforms and attributes it finds. What you get out of this is
some nice syntactic sugar for working with sending data to shaders' uniforms:

    //Given that your shader has declared a 'uniform float theta;'
    float g_Theta = 0;

    .
    .
    .

    Shader tShade( "shaders/vert_shader.glsl", "shaders/frag_shader.glsl" );
    
    .
    .
    .
    
    g_Theta += 0.01;
    tShade["theta"] = g_Theta;


As of the moment, it will recognize:

*  float
*  float[]
*  *float
*  int


It also overrides () to allow the following:

    float x = 0, y = 1, z = -4;
    .
    .
    .
    tShade["atPosition"]( x, y, z );

as well as

    float *eyePos = new float[3];
    eyePos[0] = 0.0f;
    eyePos[1] = 1.0f;
    eyePos[2] = -5.0f;
    .
    .
    .
    tShade["eyePosition"]( 3, eyePos );

## Caveats ##

There are some things to be aware of; namely:

#### Linux Land ####

This compiles with g++. I can't think of any reason that
it wouldn't compile with anything else, as I don't really use
all that much black magic.

#### Code ####

Not all types are written yet; perhaps most importantly, I haven't
written the matrix assignment code yet. To work directly with the
locations of the uniforms, you can use the .address() method as follows:

      Shader tShade( "shaders/vert_shader.glsl", "shaders/frag_shader.glsl" );
      glUniform3f( tShade["eyePosition"].address(), 1, 2, 3 );

This is also the only one to way to use the attributes at the moment.
