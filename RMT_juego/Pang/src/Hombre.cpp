

#include "Hombre.h"
#include "glut.h"


Hombre::Hombre():sprite("imagenes/pangPlayer.png",5)
{
	sprite.setCenter(1,0);
	sprite.setSize(2,2);
	altura=1.8f;
}

Hombre::~Hombre()
{

}

void Hombre::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x,posicion.y,0.5);
   	glColor3f(1.0f,1.0f,1.0f);
    //glutSolidSphere(altura, 20, 20); //esfera antigua de dise�o

	//gestion de direccion y animacion
	if(velocidad.x>0.01)sprite.flip(false,false);
	if(velocidad.x<-0.01)sprite.flip(true,false);
	if((velocidad.x<0.01)&&(velocidad.x>-0.01))
		sprite.setState(0);
	else if (sprite.getState()==0)
		sprite.setState(1,false);
	sprite.draw();

	glPopMatrix();

}

void Hombre::mueve(float t)
{
	ObjetoMovil::mueve(t);
	sprite.loop();
}

