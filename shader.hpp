#ifndef __SHADER_HPP__
#define __SHADER_HPP__

// (c) 2010 Geoff Huston
// Licensed under the GPL

typedef enum shader_param_type_t {
  SHADER_ATTRIBUTE,
  SHADER_UNIFORM
} param_type;

class ShaderParameter {
  public:
    Coordinate< int > address;
    param_type kind;

    ShaderParameter( int addr, param_type k ) {
      address( addr );
      kind = k;
    }

    void operator= ( float x ) {
      if( kind == SHADER_UNIFORM ) {
	glUniform1f( address(), x );
      }
    }

    void operator= ( int x ) {
      if( kind == SHADER_UNIFORM ) {
	glUniform1i( address(), x ); 
      }
    }

    void operator= ( float x[3] ) {
      if( kind == SHADER_UNIFORM ) {
	glUniform3fv( address(), 3, x );
      }
    }

    void operator() ( float x, float y, float z ) {
      if( kind == SHADER_UNIFORM ) {
	glUniform3f( address(), x, y, z ); 
      }
    }

    void operator() ( int n, float *f ) {
      if( kind == SHADER_UNIFORM ) {
	if( n == 3 ) {
	  glUniform3fv( address(), 3, f ); 
	} else if ( n == 2 ) {
	  glUniform2fv( address(), 2, f );
	}
      }
    }

    void operator() ( int n, int *i ) {
      if( kind == SHADER_UNIFORM ) {
	if( n == 3 ) {
	  glUniform3iv( address(), 3, i ); 
	} else if ( n == 2 ) {
	  glUniform2iv( address(), 2, i );
	}
      }
    }
};

class Shader {
  protected:
    std::map< std::string, ShaderParameter > _parameters;
    void init_map( void );
  public:
    Coordinate< GLint > pid;
    Shader( const char*, const char* );
    ~Shader( void );

    ShaderParameter operator[]( std::string which ) {
      return _parameters.find( which )->second;
    }

    virtual void Use( void );
};

class TextureShader : public Shader {

  public:
    TextureShader( );
};


#endif
