#include "gLib.h"
#include "Heroes/HumanoidCharacter.cpp"
#include "Scenario/Scenario.cpp"

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;

HumanoidCharacter teste, teste2, teste3;
Scenario landscape;

float escala;
float dx,dy,dz;

int windowsWidth, windowsHeight;

//Limitador da animação
GLdouble lastWalkAnimation;
GLdouble currentWalkAnimation;
GLdouble difference;


void defineIlumination ( void ){
    GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0}; 
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; // "cor" 
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
    GLfloat posicaoLuz[4]={0.0, 1000, 1000, 1.0};
    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
    GLint especMaterial = 60;
    // Define a refletância do material 
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    // Ativa o uso da luz ambiente 
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}


void draw( void ){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	defineIlumination();

	teste.draw();
	teste2.draw();
    teste3.draw();

	glPushMatrix();
		glRotatef(180,0,1,0); 
		glScalef(150,150,150);
		landscape.draw();
	glPopMatrix();
	glutSwapBuffers();
}	


void idle( void ){
	currentWalkAnimation = glutGet(GLUT_ELAPSED_TIME);
	difference = currentWalkAnimation - lastWalkAnimation;
	
    if(difference >= 10){
    	teste.walkAnimation();
		teste2.walkAnimation();
    	lastWalkAnimation = currentWalkAnimation;
    }
    glutPostRedisplay();
}

double mouseOriginAngle( int x, int y ){
    int xa, ya;
    int x2,y2;
    x2 = x - windowsWidth;
    y2 = windowsHeight - y ;

    ya = 0;
    xa = 0;

    double oposto, adjascente;
    adjascente = x2 - xa;
    oposto = y2 - ya;

    double aux =  atan(adjascente/oposto) * 180 / M_PI;
    if(oposto < 0) aux = aux + 180;
    aux = -aux;

    return aux;
}


// Inicialização
void init(void)
{
	dx = dy = 0;
	lastWalkAnimation = glutGet(GLUT_ELAPSED_TIME);
	escala = 0.15;

	glClearColor(135/255.0,206/255.0,250/255.0, 0);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_TEXTURE_2D);
    
    // Initializes Scenario
    FILE *objFile, *bmp;
    objFile = fopen("Objs/scenario.txt","r");
    bmp = fopen("Img/scenario.bmp","rb");
    landscape.setObjFile(objFile);
    landscape.setTexFile(bmp);
    landscape.readObjFile();
    landscape.setTexID();
    fclose( objFile );
    fclose( bmp );

    //Inicializa opções do observador
	angle = 45;
	rotX = 45;
    rotY = 0;
    obsZ = 200;
}


// Função usada para especificar a posição do observador virtual
void positionsObserver(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	glTranslatef(-dx,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glTranslatef(0,0,-dz);
	defineIlumination();
}


// Função usada para especificar o volume de visualização
void SpecifiesVisualizationParameters( void ){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,1000);
	positionsObserver();
}

void reshape(GLsizei w, GLsizei h){	
	windowsHeight = h;
    windowsWidth = w;
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;
	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	SpecifiesVisualizationParameters();
}


// Callback para gerenciar eventos do mouse
void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			///code
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			///code
		}
	SpecifiesVisualizationParameters();
	glutPostRedisplay();
}

void SpecialKeys (int tecla, int x, int y){
	switch (tecla){
		case GLUT_KEY_LEFT:	
			rotY--;
			break;
		case GLUT_KEY_RIGHT:
			rotY++;
			break;
		case GLUT_KEY_UP:
			rotX++;
			break;
		case GLUT_KEY_DOWN:
			rotX--;
			break;
		case GLUT_KEY_HOME:
			obsZ++;
			break;
		case GLUT_KEY_END:
			obsZ--;
			break;
        default:
            break;
	}
	positionsObserver();
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
	int rotate;
    switch (key){	
		case 'b':
			teste2.takeDamage(20);
			break;
		case 27:
			exit(0);
			break;
		case 'a':
			dx-=1.5;
			rotate = -90;
			break;
		case 'd':
			dx+=1.5;
			rotate = 90;
			break;
        case 'w':
            dz-=1.5;
            rotate = 180;
            break;
        case 's':
            dz+=1.5	;
            rotate = 0;
            break;
        case 'o':
            obsZ++;
            break;
        case 'i':
            obsZ--;
            break;
        default:
            break;
    }
    teste.setRotate( 0, rotate, 0 );
	teste.setPosition(dx,teste.getPosition().getY(),dz);
    positionsObserver();
	glutPostRedisplay();
}

// Programa Principal
int main()
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowPosition(5,5);
	glutInitWindowSize(1024,720);
	glutCreateWindow("Hello MOBA");
	glutFullScreen(); 

	glutDisplayFunc( draw );
	glutSpecialFunc( SpecialKeys );
    glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( idle );


	teste3.setHeadColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
    teste3.setBodyColor( 0.5, 0.5, 0.5 );
    teste3.setArmColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
    teste3.setLegColor( 0.0, 0.0, 1.0 );
    teste3.setScale( 0.7, 0.5, 0.7 );
    teste3.setRotate( 0, 45, 0 );
    teste3.setWalk(true);
    teste3.setPosition( 29.0, 0.0, 0.0 );
   
	teste.setHeadColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
	teste.setBodyColor( 1.0, 0.0, 0.0 );
	teste.setArmColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
	teste.setLegColor( 0.0, 0.0, 1.0 );
	teste.setScale( 0.5, 0.5, 0.5 );
	teste.setRotate( 0, 45, 0 );
	teste.setWalk(true);
	teste.setPosition( -20.0, 0.0, 0.0 );
    

	teste2.setHeadColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
	teste2.setBodyColor( 0.5, 0.5, 0.5 );
	teste2.setArmColor( 244.0f/255.0f, 164.0f/255.0f, 96.0f/255.0f);
	teste2.setLegColor( 0.0, 0.0, 1.0 );
	teste2.setScale( 0.7, 0.5, 0.7 );
	teste2.setRotate( 0, 45, 0 );
	teste2.setWalk(true);
	teste2.setPosition( 0.0, 0.0, 0.0 );
    
	init();
	glutMainLoop();
}

