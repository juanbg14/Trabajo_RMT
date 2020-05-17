#include "Mundo.h"
#include "glut.h"
#include <cmath>
#include "Interaccion.h"

Mundo::~Mundo()
{
	esferas.destruirContenido();
	disparos.destruirContenido();
}

void Mundo::rotarOjo()
{
	float dist=sqrt(x_ojo*x_ojo+z_ojo*z_ojo);
	float ang=atan2(z_ojo,x_ojo);
	ang+=0.05f;
	x_ojo=dist*cos(ang);
	z_ojo=dist*sin(ang);
}
void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	//aqui es donde hay que poner el codigo de dibujo
	caja.dibuja();
	hombre.dibuja();
	disparos.dibuja();
	plataforma.dibuja();
	bonus.dibuja();
	esferas.dibuja();
	esfera_pulsante.dibuja();
	disparo_especial.dibuja();

	ETSIDI::setTextColor(1,1,0);
	ETSIDI::setFont("fuentes/Bitwise.ttf",16);
	ETSIDI::printxy("Pang 1.1", -10,17);
	
	ETSIDI::setTextColor(1,1,1);
	ETSIDI::setFont("fuentes/Bitwise.ttf",12);
	ETSIDI::printxy("Hernando & Rodriguez-Losada",-10,16.4);
}

void Mundo::mueve()
{
	disparo_especial.mueve(0.025f);
	if(Interaccion::colision(disparo_especial,plataforma))
		disparo_especial.setVel(0,0);

	esfera_pulsante.mueve(0.025f);
	Interaccion::rebote(esfera_pulsante,plataforma);
	Interaccion::rebote(esfera_pulsante,caja);

	hombre.mueve(0.025f);
	bonus.mueve(0.025f);

	disparos.mueve(0.025f);
	disparos.colision(caja);
	disparos.colision(plataforma);

	esferas.mueve(0.025f);
	esferas.rebote();
	esferas.rebote(plataforma);
	esferas.rebote(caja);
	Esfera *aux=esferas.colision(hombre);
	if(aux!=0){
		esferas.eliminar(aux);
		ETSIDI::play("sonidos/impacto.wav");
	}


	Interaccion::rebote(hombre,caja);
}

void Mundo::inicializa()
{
	x_ojo=0;
	y_ojo=7.5;
	z_ojo=30;

	bonus.setPos(5.0f,5.0f);
	plataforma.setPos(-5.0f,9.0f,5.0f,9.0f);

	Esfera *e1=new Esfera(1.5f,2,4,5,15);
	e1->setColor(0,0,255);
	esferas.agregar(e1); //esfera

	Esfera *e2=new Esfera(2,-2,4,-5,15);
	e2->setColor(255,255,255);
	esferas.agregar(e2); //esfera2

	for(int i=0;i<6;i++)
	{
		Esfera* aux=new Esfera(0.75+i*0.25,i,1+i,i,i);
		esferas.agregar(aux);
	} 

}

void Mundo::tecla(unsigned char key)
{
		switch(key)
	{
		case ' ':
			{
 				Disparo* d=new Disparo();
				Vector2D pos=hombre.getPos();
				d->setPos(pos.x,pos.y);
				disparos.agregar(d);
				hombre.setVel(0,0);
				ETSIDI::play("sonidos/disparo.wav");
				break;
			}
		case '1':	
 			esferas.agregar (new Esfera(0.5f,0,10));
			break;
		case '2':	
 			esferas.agregar (new Esfera(1.0f,0,10));
			break;
		case '3':	
 			esferas.agregar (new Esfera(1.5f,0,10));
			break;
		case '4':	
 			esferas.agregar (new Esfera(2.0f,0,10));
			break;
	}

}
void Mundo::teclaEspecial(unsigned char key)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		hombre.setVel (-5.0f, 0.0f);
		break;
	case GLUT_KEY_RIGHT:
		hombre.setVel (5.0f, 0.0f);
		break;
	}
}