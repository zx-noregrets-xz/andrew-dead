#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ANSI_RESET     "\x1b[0m"
#define ANSI_RED       "\x1b[31m"
#define ANSI_GREEN     "\x1b[32m"
#define ANSI_YELLOW    "\x1b[33m"

int rb (int min, int max){
  return rand() % (max - min + 1) + min;
}


int main(){

    srand(time(NULL));
    int Clock = 0, seconds=0, mintutes=0, arrivecounter=0, leavecounter=0, gameactive=1, CarsInLot=0;
    // Create the parking lot
    char parklot[20][45];
    // Make all the characters O in the parking lot
    for (int a=0;a<20;a++){
        for (int b=0;b<45;b++){
            parklot[a][b] = 'O';
        }
    }
    // Randomly set the arrival and leave times
    int CarArriveTime = rb(1,10);
    int CarLeaveTime = rb(15,30);
    // Coordinate values that the arrive and leave blocks use to determine where to pick a spot to park and which car should leave
    int slox, sloy;
    while (gameactive==1){
        printf("\e[1;1H\e[2J");
        usleep(1000000);
        Clock++;
        seconds++;
        // Increase the arrival and leave counters that are seperated from clock time to prevent factors from skewing the simulation
        arrivecounter++;
        leavecounter++;

        //Makes a pretty looking clock with minutes
        if (Clock%60==0){
            mintutes++;
            seconds=0;
        }
        printf("Current Time is %0i minutes %i seconds\n", mintutes, seconds);
        printf("There are " ANSI_RED "%i car(s)" ANSI_RESET " in the lot\n", CarsInLot);

        // Arrival block
        if (arrivecounter == CarArriveTime) {
            // Make sure lot is not full
            if (CarsInLot < 900) {
                int valid = 0;
                while (valid == 0) {
                    slox = rb(0,19);
                    sloy = rb(0,44);
                    // Check if spot is free
                    if (parklot[slox][sloy] == 'O') {
                        parklot[slox][sloy] = '#';
                        CarsInLot++;
                        printf(ANSI_YELLOW "A car has arrived, assigning to spot %i, %i\n", sloy+1, 20-slox);
                        printf(ANSI_RESET);
                        valid = 1;
                    }
                }

            }
            else {

                printf(ANSI_YELLOW "Parking lot FULL, waiting for spaces\n" ANSI_RESET);
            }
            // Pick a new arrival time and reset the counter
            arrivecounter = 0;
            CarArriveTime = rb(1,10);
        }

        // Leave block
        if (leavecounter == CarLeaveTime) {
            int valid = 0;
            while (valid == 0) {
                slox = rb(0,19);
                sloy = rb(0,44);
                // Check if spot is occupied
                if (parklot[slox][sloy] == '#') {
                    parklot[slox][sloy] = 'O';
                    CarsInLot--;
                    printf(ANSI_GREEN "A car has left %i, %i\n", sloy+1, 20-slox);
                    printf(ANSI_RESET);
                    valid = 1;
                }
            }
            leavecounter = 0;
            CarLeaveTime = rb(15,30);
        }

        // Print parking lot
        for (int a=0;a<20; a++){
            for (int b=0; b<45; b++){
                if (parklot[a][b] == '#'){
                    printf(ANSI_RED "# " ANSI_RESET);
                }
                else{
                    printf("O ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}
