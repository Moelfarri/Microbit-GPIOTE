#include <stdint.h>
#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"




//ALLE de 4 GPIOTE kanalene skal brukes 
//Kanal 1 skal brukes til å lytte til A-knappen ---> Generere en hendelse dersom A knappen trykkes. --> alts når spenningen på GPIO pinnen går fra høy til lav
//De resterende 3 knappene skal alle være konfigurert osm oppgaver og kobles til hver sin forsyningspinne for LED-matrisen.





int main(){

	//Konfigurere Jordingspinnene som output
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);

    }
    //3 Tasks/Oppgaver:
    GPIOTE->CONFIG[0] = 3 | (13 << 8) | ( 3 << 16) | (1 << 20); //sett (0 << 20) -> (1 << 20) for riktig
    GPIOTE->CONFIG[1] = 3 | (14 << 8) | ( 3 << 16) | (1 << 20);
    GPIOTE->CONFIG[2] = 3 | (15 << 8) | ( 3 << 16) | (1 << 20);
    // Configure A button as Event
    GPIOTE->CONFIG[3] = 1 | (17 << 8) | ( 2 << 16);




    //Kobler PPI kanalene med GPIOTE knapp og pinner
    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[3]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
    PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[3]);
    PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[1]);
    PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[3]);
    PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[2]);

    //For å aktivere knappen
    PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2);
    
 



	int sleep = 0;
	

		sleep = 10000;
		while(--sleep);

    
	return 0;
}
