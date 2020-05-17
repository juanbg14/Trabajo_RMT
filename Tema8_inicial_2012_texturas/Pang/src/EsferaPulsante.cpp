#include "EsferaPulsante.h"


EsferaPulsante::EsferaPulsante(void)
{
	radio_max=2.0f;
	radio_min=0.5f;
	pulso=0.5f;
	aceleracion.y=0.0f;
	posicion.y=5.0f;
}


EsferaPulsante::~EsferaPulsante(void)
{
}


void EsferaPulsante::mueve(float t)
{
	Esfera::mueve(t);

	if(radio>radio_max)
		pulso=-pulso;
	if(radio<radio_min)
		pulso=-pulso;
	radio+=pulso*t;

	color.r=radio*255;
	color.g=255-radio*100;
	color.b=100+radio*50;
}
