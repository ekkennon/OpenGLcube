#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>
#include <iostream>

using namespace std;

int CURENT_TIME;


class Box{
public:
  Box();
  void draw();
  void chposition(double x,double y,double z);
  void rotate(bool rot);
  void scale(bool sc);
private:
  bool rot;
  bool sc;
  double x,y,z;
};

Box::Box(){
  x=0;y=0;z=0;
  rot=false;
}


void Box::scale(bool sc){
 this->sc=sc;
}


void Box::rotate(bool rot){
 this->rot=rot;
}

void Box::chposition(double x,double y,double z){
  this->x=x;
  this->y=y;
  this->z=z;
}

void Box::draw(){
  
  glPushMatrix();
  glTranslatef(x,y,z);
   
  if(sc) 
  glScaled(1+0.5*sin((((CURENT_TIME%2000)/1000.0)-1)*2*3.14),
           1+0.5*sin((((CURENT_TIME%2000)/1000.0)-1)*2*3.14),
	   1+0.5*sin((((CURENT_TIME%2000)/1000.0)-1)*2*3.14));
  
  
  if(rot) 
  glRotatef( CURENT_TIME*360/1000, 0.0f, 1.0f, 0.0f );
  
  glBegin( GL_QUADS );                 /* Draw A Quad                      */
      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Green           */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Top)      */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Top)       */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Bottom Left Of The Quad (Top)    */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Bottom Right Of The Quad (Top)   */

      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Orange          */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Top Right Of The Quad (Botm)     */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Top Left Of The Quad (Botm)      */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Botm)   */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Botm)  */

      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Red             */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Front)    */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Front)     */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Front)  */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Front) */

      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Yellow          */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Back)   */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Back)  */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Back)     */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Back)      */

      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Blue            */
      glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Left)     */
      glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Left)      */
      glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Left)   */
      glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Left)  */

      glColor3f(   0.0f,  0.0f,  0.0f ); /* Set The Color To Violet          */
      glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Right)    */
      glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Right)     */
      glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Right)  */
      glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Right) */
    glEnd( );                            /* Done Drawing The Quad            */

  glPopMatrix();
}


const int swidth = 800;//screen width
const int sheight = 600;//screen height
const int bpp = 32;//bits per pixel (32 bit)

SDL_Surface *screen = NULL;
SDL_Event event;

bool init();
void clean();
void render();

Box boxes[20][20];

int main(int argc,char *argv[]){ 
   
  for(int i=0;i<20;i++){
    for(int j=0;j<20;j++){
     boxes[i][j].chposition(i*3-30,j*3-30,0);
  } }
  
  boxes[5][1].rotate(true);
  
  boxes[10][15].rotate(true);
  boxes[10][15].scale(true);
  
  boxes[15][15].scale(true);
  
  if (init() == false){
    return 1;
  }
  
  bool quit = false;//turns true if the user wants to quit
  while (quit == false){
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
	quit = true;
      }
      else if(event.type == SDL_KEYDOWN){
	switch(event.key.keysym.sym){
	  case SDLK_ESCAPE:
	    quit = true;
	    break;
	  default:
	    break;
	}
      }
    }
    //cout<<"work";
    render();
  }
  clean();
  
  return 0;
}

bool init(){
    
    int videoFlags;
    const SDL_VideoInfo *videoInfo;

    /* Fetch the video info */
    SDL_Init( SDL_INIT_VIDEO);
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n",
		     SDL_GetError( ) );
	    exit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    screen = SDL_SetVideoMode( swidth, sheight, bpp,
				videoFlags );

  SDL_WM_SetCaption("Mastermind",NULL);
  
  
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    
    GLfloat ratio;
    ratio = ( GLfloat )swidth / ( GLfloat )sheight;
    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )swidth, ( GLsizei )sheight );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

  return true;
}

void clean()
{
  SDL_Quit();
}

void render(){
  CURENT_TIME=SDL_GetTicks();
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  glLoadIdentity();
  glTranslatef( 0.0f, 0.0f, -100.0f );
  
  for(int i=0;i<20;i++){
    for(int j=0;j<20;j++){
     boxes[i][j].draw();
  } }

  SDL_GL_SwapBuffers( );
}
