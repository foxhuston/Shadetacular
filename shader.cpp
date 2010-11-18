#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<cstdlib>

#include<GL/glew.h>
#include<GL/glext.h>
#include<GL/gl.h>

#include "coordinate.hpp"
#include "shader.hpp"

using namespace std;

string slurpFile( string fname ) {
  ifstream fs( fname.c_str(), ifstream::in );

  //This is awesome! From: http://www.gamedev.net/community/forums/topic.asp?topic_id=353162
  string buff((istreambuf_iterator<char>(fs)), istreambuf_iterator<char>());

  return buff;
}

void Shader::init_map( void ) {
  int maxUniforms;
  glGetProgramiv( pid(), GL_ACTIVE_UNIFORMS, &maxUniforms);

  int maxUlen;
  glGetProgramiv( pid(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUlen);

  GLchar *ubuf=(char *)malloc(maxUlen+1);
  for (int i=0 ; i < maxUniforms; i++){
    int size;
    GLenum type;
    glGetActiveUniform( pid(), i, maxUlen, NULL, &size, &type, ubuf );

    string uniform_name(ubuf);
    _parameters.insert(pair<string,ShaderParameter>(uniform_name,ShaderParameter( glGetUniformLocation( pid(), ubuf ), SHADER_UNIFORM )));
    cout << "Uniform \x1B[33m" << uniform_name << "\x1B[0m with location: " << _parameters.find( uniform_name )->second.address() << endl;
    
  }
  free(ubuf);

  int maxAttributes;
  glGetProgramiv(pid(), GL_ACTIVE_ATTRIBUTES,&maxAttributes);
  int maxAlen;
  glGetProgramiv(pid(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAlen);

  GLchar *abuf=(char *)malloc(maxAlen+1);
  for (int i=0 ; i < maxAttributes; i++){
    int size;
    GLenum type;
    glGetActiveAttrib( pid(), i, maxAlen, NULL, &size, &type, abuf );

    string attr_name(abuf);
    _parameters.insert(pair<string,ShaderParameter>(attr_name,ShaderParameter( glGetAttribLocation( pid(), abuf ), SHADER_ATTRIBUTE )));
    cout << "Attribute \x1B[33m" << attr_name << "\x1B[0m with location: " << _parameters.find( attr_name )->second.address() << endl;
  }
  free (abuf);
}

void checkShaderCompileStatus( GLint sh ) {
  GLint status;
  // Check for any compile time error.
  glGetShaderiv(sh,GL_COMPILE_STATUS,&status);
  
  cout << "\x1B[00;31m";

  if (status==GL_FALSE){ // Error in shader code compilation.
    GLint infologLength;
    glGetShaderiv(sh,GL_INFO_LOG_LENGTH,&infologLength);
    if (infologLength==0){
      cout << "An undocumented error occurred." << endl;
      glDeleteShader(sh);
      cout << "\x1B[00;00m";
      return;
    }
    char *infoLog = (char *)malloc(infologLength);
    if (infoLog == NULL){
      cout << "A tragic malloc error!" << endl;
      glDeleteShader(sh);
      cout << "\x1B[00;00m";
      return;
    }
    int readChars  = 0;
    glGetShaderInfoLog(sh, infologLength, &readChars, infoLog);
    cout << "Error: " << infoLog << endl;
    free(infoLog);
    glDeleteShader(sh);
  }
  cout << "\x1B[00;00m";
}

Shader::Shader( const char *vertex_shader_file_name,
		const char *fragment_shader_file_name ) {

  pid( glCreateProgram() );
  int vs_id = -1;
  int fs_id = -1;
  string vert_shader_code = slurpFile( vertex_shader_file_name );
  string frag_shader_code = slurpFile( fragment_shader_file_name );

  vs_id = glCreateShader( GL_VERTEX_SHADER );
  const char *vcode = vert_shader_code.c_str();
  glShaderSource(vs_id, 1, &vcode, NULL);
  glCompileShader( vs_id );
  checkShaderCompileStatus( vs_id );

  fs_id = glCreateShader( GL_FRAGMENT_SHADER );
  const char *fcode = frag_shader_code.c_str();
  glShaderSource(fs_id, 1, &fcode, NULL);
  glCompileShader( fs_id );
  checkShaderCompileStatus( fs_id );

  glAttachShader( pid(), vs_id );
  glAttachShader( pid(), fs_id );

  glLinkProgram( pid() );

  glValidateProgram( pid() );
  GLint status;
  glGetProgramiv( pid(), GL_VALIDATE_STATUS, &status);

  if( status ) {
    cout << "\x1B[01;34mIt's all good!\x1B[0m" << endl;
  } else {
    cout << "\x1B[01;31mIT IS NOT ALL GOOD\x1B[0m" << endl;
    return;
  }

  init_map();

}

Shader::~Shader( void ) {
  glDeleteProgram( pid() );
}

void Shader::Use( void ) {
  glUseProgram( pid() );
}

TextureShader::TextureShader( )
  : Shader ( "shaders/ref_vert.glsl", "shaders/ref_frag.glsl" ) {

}

