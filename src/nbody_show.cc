#include <nbody.hpp>
#include <singleton.hpp>

#include <cassert>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <GL/glut.h>
#include <unistd.h>

static void init( void )
{
    static GLfloat lightpos[] = {.5, .75, 1.5, 1};
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glLightfv( GL_LIGHT0, GL_POSITION, lightpos );
    GLUquadricObj* base = gluNewQuadric();
    gluQuadricOrientation( base, GLU_INSIDE );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

static void reshape( GLsizei w, GLsizei h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, 1, .01, 10 );
    gluLookAt( 0, 0, 2.577, 0, 0, -5, 0, 1, 0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

static void draw_room( void )
{
    /* material for the walls, floor, ceiling */
    static GLfloat wall_mat[] = {1.f, 1.f, 1.f, 1.f};
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat );
    glBegin( GL_QUADS );
    /* floor */
    glNormal3f( 0, 1, 0 );
    glVertex3f( -1, -1, 1 );
    glVertex3f( 1, -1, 1 );
    glVertex3f( 1, -1, -1 );
    glVertex3f( -1, -1, -1 );
    /* ceiling */
    glNormal3f( 0, -1, 0 );
    glVertex3f( -1, 1, -1 );
    glVertex3f( 1, 1, -1 );
    glVertex3f( 1, 1, 1 );
    glVertex3f( -1, 1, 1 );
    /* left wall */
    glNormal3f( 1, 0, 0 );
    glVertex3f( -1, -1, -1 );
    glVertex3f( -1, -1, 1 );
    glVertex3f( -1, 1, 1 );
    glVertex3f( -1, 1, -1 );
    /* right wall */
    glNormal3f( -1, 0, 0 );
    glVertex3f( 1, 1, -1 );
    glVertex3f( 1, 1, 1 );
    glVertex3f( 1, -1, 1 );
    glVertex3f( 1, -1, -1 );
    /* far wall */
    glNormal3f( 0, 0, 1 );
    glVertex3f( -1, -1, -1 );
    glVertex3f( 1, -1, -1 );
    glVertex3f( 1, 1, -1 );
    glVertex3f( -1, 1, -1 );
    glEnd();
}

static void draw_nbody()
{
    static GLfloat nbody_mat[] = {1.0f, 0.0f, 1.0f, 1.0f};
    auto& nb = feng::singleton<feng::nbody<float> >::instance();
    glPushMatrix();
    glTranslatef( 0, 0, 0.0 );
    glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, nbody_mat );
    glPointSize( 5.0f );
    glBegin( GL_POINTS );             // start drawing particles
    glColor3f( 1.0f, 1.0f, 1.0f );
    for ( auto p : nb.collection_ )
        { glVertex3f( p.p().x(), p.p().y(), p.p().z() ); }
    glEnd();                  // Done Drawing The particles
    nb();
    glPopMatrix();
}

static void draw( void )
{
    GLenum err;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    draw_room();
    glEnable( GL_BLEND );
    draw_nbody();
    glDisable( GL_BLEND );
    err = glGetError();

    if ( err != GL_NO_ERROR )
        std::cerr << "Error:  " << gluErrorString( err )  << "\n";

    glutSwapBuffers();
}

static void key( unsigned char key, int x, int y )
{
    static int idle = 1;

    if ( key == 27 ) //esc key 
        { exit( 0 ); }

    idle = ( idle == 0 );

    if ( idle )
    {
        glutIdleFunc( draw );
    }
    else
    {
        glutIdleFunc( 0 );
    }
}

int main( int argc, char* argv[] )
{
    usleep(5000000);
    int n = 1000;
    if ( 2 == argc ) n = std::atoi( argv[1] );
    if ( 3 == argc && 2 == std::strlen( argv[1] ) && '-' == argv[1][0] && 'n' == argv[1][1] ) n = std::atoi( argv[2] ); 

    auto& nb = feng::singleton<feng::nbody<float> >::instance();
    nb.random_initialize( n );
    glutInitWindowSize( 600, 600 );
    glutInitWindowPosition( 0, 0 );
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    glutCreateWindow( argv[0] );
    glutDisplayFunc( draw );
    glutIdleFunc( draw );
    glutKeyboardFunc( key );
    glutReshapeFunc( reshape );
    init();
    glutMainLoop();
    return 0;
}
