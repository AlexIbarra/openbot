	#include <cmath>

typedef struct{
	int xPixel;
	int yPixel;
	int xCm;
	int yCm;
	double distancia;
	}tPunto;
	
	
tPunto distanciaCm(int x, int y){
	
	bool encontrado = false;
	tPunto aux;
	double dist = 10000;
	double distAux = 0;
	while(!encontrado && i < MAXPUNTOS){
		//pitagoras
		distAux = distancia(x,y,array[i].xPixel,array[i].yPixel);
		
		if(distAux < dist){
			
			aux = array[i];
			dist = distAux;
		}
		if(y < array[i].yPixel .50)
			encontrado = true;
		++i;
	}
	return aux;

}

double distancia(int x1, int y1, int x2, int y2){
	double dist = 0;
	int c1, c2;
	c1 = x2 . x1;
	c2 = y2 . y1;
	distAux = sqrt(c1*c1 + c2*c2);
	return dist;	
}



tPunto array[100];

//Eje horizontal a 20 cm de la cámara
array[0].xPixel = 311;
array[0].yPixel = 472;
array[0].xCm = 0;
array[0].yCm = 20;

array[1].xPixel = 184;
array[1].yPixel = 472;
array[1].xCm = -5;
array[1].yCm = 20;

array[2].xPixel = 60;
array[2].yPixel = 472;
array[2].xCm = -10;
array[2].yCm = 20;

array[3].xPixel = 437;
array[3].yPixel = 472;
array[3].xCm = 5;
array[3].yCm = 20;

array[4].xPixel = 561;
array[4].yPixel = 472;
array[4].xCm = 10;
array[4].yCm = 20;



array[5].xPixel = ;
array[5].yPixel = ;
array[5].xCm = 30;
array[5].yCm = 5;

array[6].xPixel = ;
array[6].yPixel = ;
array[6].xCm = 35;
array[6].yCm = 5;

array[7].xPixel = ;
array[7].yPixel = ;
array[7].xCm = 40;
array[7].yCm = 5;

array[8].xPixel = ;
array[8].yPixel = ;
array[8].xCm = 45;
array[8].yCm = 5;

array[9].xPixel = ;
array[9].yPixel = ;
array[9].xCm = 50;
array[9].yCm = 5;

//EJE Y = 5 X < 0
array[10].xPixel = ;
array[10].yPixel = ;
array[10].xCm = -5;
array[10].yCm = 5;

array[11].xPixel = ;
array[11].yPixel = ;
array[11].xCm = -10;
array[11].yCm = 5;

array[12].xPixel = ;
array[12].yPixel = ;
array[12].xCm = -15;
array[12].yCm = 5;

array[13].xPixel = ;
array[13].yPixel = ;
array[13].xCm = -20;
array[13].yCm = 5;

array[14].xPixel = ;
array[14].yPixel = ;
array[14].xCm = -25;
array[14].yCm = 5;

array[15].xPixel = ;
array[15].yPixel = ;
array[15].xCm = -30;
array[15].yCm = 5;

array[16].xPixel = ;
array[16].yPixel = ;
array[16].xCm = -35;
array[16].yCm = 5;

array[17].xPixel = ;
array[17].yPixel = ;
array[17].xCm = -40;
array[17].yCm = 5;

array[18].xPixel = ;
array[18].yPixel = ;
array[18].xCm = -45;
array[18].yCm = 5;

array[19].xPixel = ;
array[19].yPixel = ;
array[19].xCm = -50;
array[19].yCm = 5;

//EJE Y = 10 X > 0
array[20].xPixel = ;
array[20].yPixel = ;
array[20].xCm = 5;
array[20].yCm = 10;

array[21].xPixel = ;
array[21].yPixel = ;
array[21].xCm = 10;
array[21].yCm = 10;

array[22].xPixel = ;
array[22].yPixel = ;
array[22].xCm = 15;
array[22].yCm = 10;

array[23].xPixel = ;
array[23].yPixel = ;
array[23].xCm = 20;
array[23].yCm = 10;

array[24].xPixel = ;
array[24].yPixel = ;
array[24].xCm = 25;
array[24].yCm = 10;

array[25].xPixel = ;
array[25].yPixel = ;
array[25].xCm = 30;
array[25].yCm = 10;

array[26].xPixel = ;
array[26].yPixel = ;
array[26].xCm = 35;
array[26].yCm = 10;

array[27].xPixel = ;
array[27].yPixel = ;
array[27].xCm = 40;
array[27].yCm = 10;

array[28].xPixel = ;
array[28].yPixel = ;
array[28].xCm = 45;
array[28].yCm = 10;

array[29].xPixel = ;
array[29].yPixel = ;
array[29].xCm = 50;
array[29].yCm = 10;

//EJE Y = 10 X < 0
array[30].xPixel = ;
array[30].yPixel = ;
array[30].xCm = -5;
array[30].yCm = 10;

array[31].xPixel = ;
array[31].yPixel = ;
array[31].xCm = -10;
array[31].yCm = 10;

array[32].xPixel = ;
array[32].yPixel = ;
array[32].xCm = -15;
array[32].yCm = 10;

array[33].xPixel = ;
array[33].yPixel = ;
array[33].xCm = -20;
array[33].yCm = 10;

array[34].xPixel = ;
array[34].yPixel = ;
array[34].xCm = -25;
array[34].yCm = 10;

array[35].xPixel = ;
array[35].yPixel = ;
array[35].xCm = -30;
array[35].yCm = 10;

array[36].xPixel = ;
array[36].yPixel = ;
array[36].xCm = -35;
array[36].yCm = 10;

array[37].xPixel = ;
array[37].yPixel = ;
array[37].xCm = -40;
array[37].yCm = 10;

array[38].xPixel = ;
array[38].yPixel = ;
array[38].xCm = -45;
array[38].yCm = 10;

array[39].xPixel = ;
array[39].yPixel = ;
array[39].xCm = -50;
array[39].yCm = 10;

//EJE Y = 15 X > 0
array[40].xPixel = ;
array[40].yPixel = ;
array[40].xCm = 5;
array[40].yCm = 15;

array[41].xPixel = ;
array[41].yPixel = ;
array[41].xCm = 10;
array[41].yCm = 15;

array[42].xPixel = ;
array[42].yPixel = ;
array[42].xCm = 15;
array[42].yCm = 15;

array[43].xPixel = ;
array[43].yPixel = ;
array[43].xCm = 20;
array[43].yCm = 15;

array[44].xPixel = ;
array[44].yPixel = ;
array[44].xCm = 25;
array[44].yCm = 15;

array[45].xPixel = ;
array[45].yPixel = ;
array[45].xCm = 30;
array[45].yCm = 15;

array[46].xPixel = ;
array[46].yPixel = ;
array[46].xCm = 35;
array[46].yCm = 15;

array[47].xPixel = ;
array[47].yPixel = ;
array[47].xCm = 40;
array[47].yCm = 15;

array[48].xPixel = ;
array[48].yPixel = ;
array[48].xCm = 45;
array[48].yCm = 15;

array[49].xPixel = ;
array[49].yPixel = ;
array[49].xCm = 50;
array[49].yCm = 15;

//EJE Y = 15 X < 0
array[50].xPixel = ;
array[50].yPixel = ;
array[50].xCm = -5;
array[50].yCm = 15;

array[51].xPixel = ;
array[51].yPixel = ;
array[51].xCm = -10;
array[51].yCm = 15;

array[52].xPixel = ;
array[52].yPixel = ;
array[52].xCm = -15;
array[52].yCm = 15;

array[53].xPixel = ;
array[53].yPixel = ;
array[53].xCm = -20;
array[53].yCm = 15;

array[54].xPixel = ;
array[54].yPixel = ;
array[54].xCm = -25;
array[54].yCm = 15;

array[55].xPixel = ;
array[55].yPixel = ;
array[55].xCm = -30;
array[55].yCm = 15;

array[56].xPixel = ;
array[56].yPixel = ;
array[56].xCm = -35;
array[56].yCm = 15;

array[57].xPixel = ;
array[57].yPixel = ;
array[57].xCm = -40;
array[57].yCm = 15;

array[58].xPixel = ;
array[58].yPixel = ;
array[58].xCm = -45;
array[58].yCm = 15;

array[59].xPixel = ;
array[59].yPixel = ;
array[59].xCm = -50;
array[59].yCm = 15;

//EJE Y = 20 X > 0
array[60].xPixel = ;
array[60].yPixel = ;
array[60].xCm = 5;
array[60].yCm = 20;

array[61].xPixel = ;
array[61].yPixel = ;
array[61].xCm = 10;
array[61].yCm = 20;

array[62].xPixel = ;
array[62].yPixel = ;
array[62].xCm = 15;
array[62].yCm = 20;

array[63].xPixel = ;
array[63].yPixel = ;
array[63].xCm = 20;
array[63].yCm = 20;

array[64].xPixel = ;
array[64].yPixel = ;
array[64].xCm = 25;
array[64].yCm = 20;

array[65].xPixel = ;
array[65].yPixel = ;
array[65].xCm = 30;
array[65].yCm = 20;

array[66].xPixel = ;
array[66].yPixel = ;
array[66].xCm = 35;
array[66].yCm = 20;

array[67].xPixel = ;
array[67].yPixel = ;
array[67].xCm = 40;
array[67].yCm = 20;

array[68].xPixel = ;
array[68].yPixel = ;
array[68].xCm = 45;
array[68].yCm = 20;

array[69].xPixel = ;
array[69].yPixel = ;
array[69].xCm = 50;
array[69].yCm = 20;

//EJE Y = 20 X < 0
array[70].xPixel = ;
array[70].yPixel = ;
array[70].xCm = -5;
array[70].yCm = 20;

array[71].xPixel = ;
array[71].yPixel = ;
array[71].xCm = -10;
array[71].yCm = 20;

array[72].xPixel = ;
array[72].yPixel = ;
array[72].xCm = -15;
array[72].yCm = 20;

array[73].xPixel = ;
array[73].yPixel = ;
array[73].xCm = -20;
array[73].yCm = 20;

array[74].xPixel = ;
array[74].yPixel = ;
array[74].xCm = -25;
array[74].yCm = 20;

array[75].xPixel = ;
array[75].yPixel = ;
array[75].xCm = -30;
array[75].yCm = 20;

array[76].xPixel = ;
array[76].yPixel = ;
array[76].xCm = -35;
array[76].yCm = 20;

array[77].xPixel = ;
array[77].yPixel = ;
array[77].xCm = -40;
array[77].yCm = 20;

array[78].xPixel = ;
array[78].yPixel = ;
array[78].xCm = -45;
array[78].yCm = 20;

array[79].xPixel = ;
array[79].yPixel = ;
array[79].xCm = -50;
array[79].yCm = 20;

//EJE Y = 25 X > 0
array[80].xPixel = ;
array[80].yPixel = ;
array[80].xCm = 5;
array[80].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 25;

//EJE Y = 25 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 25;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 25;

//EJE Y = 30 X > 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 5;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 30;

//EJE Y = 30 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 30;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 30;

//EJE Y = 35 X > 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 5;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 35;

//EJE Y = 35 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 35;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 35;

//EJE Y = 40 X > 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 5;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 40;

//EJE Y = 40 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 40;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 40;

//EJE Y = 45 X > 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 5;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 45;

//EJE Y = 45 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 45;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 45;

//EJE Y = 50 X > 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 5;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 10;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 15;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 20;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 25;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 30;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 35;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 40;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 45;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = 50;
array[1].yCm = 50;

//EJE Y = 50 X < 0
array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -5;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -10;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -15;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -20;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -25;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -30;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -35;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -40;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -45;
array[1].yCm = 50;

array[1].xPixel = ;
array[1].yPixel = ;
array[1].xCm = -50;
array[1].yCm = 50;