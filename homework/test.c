#include <stdio.h>
#include <math.h>

	enum strikers { Giroux, Bony, Rooney, Hazard, Aguero, Costa, Kane } player;
	enum teams { Arsenal, ManCity, ManU, Chelsea, Tottenham } team;
	
int main(int argc, char **argv) {
	
    player = Giroux;

	if (player==Giroux) { team=Arsenal; printf("Working"); }
	else if (player==Bony) team=ManCity;
	else if (player==Rooney) team=ManU;
        

}
