/*  ---------------------------------------------------------------------------------------------
  ____           _____  _____                                 |
 //   \    /\    ||  \\ ||  \\       ||                       | Version: 1.0
||        // \   ||__// ||__//  ___  ||___   ___  _ __  ___   | Developers: CFD Lab
||       //===\  ||     ||     //  \ ||  \\ //__\ |/ \\// \\  |             High-Voltage Lab
 \\___/ //     \ ||     ||     \\__  ||  || \\__  ||  ||  ||  | 
                                                              | Developed in 
                                                              |     University of Patras, Greece
-------------------------------------------------------------------------------------------------

File info
=========
    File name:          main.c
    Type:               source
    Short Description:  This file contains all the executable source code.

Description
=========== 
This is a computational code for calculating the species densities (volume averaged)
and gas temperature of a partially ionized low pressure hydrogen plasma, using the
mathematical 0-D model described by Chen et al. [1]. The electron temeprature and
the ionization, excitation and elastic reactions rate constants were calculated
using the computational software BOLSIG+ [2], using cross sectional data from the 
LXcat project [3]. The rest of the reaction rate constants were obtained by the
literature [4,5].

Platform
========
The computational code is writen in C programming language, and both the BOLSIG+ 
and the present code can be executed in both Unix-based systems and Windows.

References
==========
[1] Chun Ku Chen et al. “Modelling the discharge region of a microwave generated
    hydrogen plasma”. In: Journal of Physics D: Applied Physics 32.6 (1999),
    pp. 688–698. issn: 00223727. doi: 10.1088/0022-3727/32/6/015 .
[2] http://www.bolsig.laplace.univ-tlse.fr/
[3] http://www.lxcat.laplace.univ-tlse.fr
[4] A. T. Hjartarson, E. G. Thorsteinsson, and J. T. Gudmundsson. “Low pressure
    hydrogen discharges diluted with argon explored using a global model”. In: Plasma
    Sources Science and Technology 19.6 (2010). issn: 09630252. doi:
    10.1088/0963-0252/19/6/065008 .
[5] A. A. Matveyev and V. P. Silakov. “Kinetic processes in a highly-ionized
    non-equilibrium hydrogen plasma”. In: Plasma Sources Science and Technology 4.4
    (1995), pp. 606–617. issn: 09630252. doi: 10.1088/0963-0252/4/4/012 .

---------------------------------------------------------------------------------------------  */

// Include C libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

// Include header files
#include "variables.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    // Read input file
    readfile("input.txt");

    // Count how many reactions there are in BOLSIG+ cross-section file
    count_BOLSIG = countBolsigReactions();

    // Allocate arrays according to input parameters
    allocate(&K, react_num, subreact_num);
    allocate(&Ethr, react_num, subreact_num);
    allocate(&map_reactions, count_BOLSIG, 2);


    // ----------------------------------------------------------------------------------
    // Initial values
    // ----------------------------------------------------------------------------------
    // Rate coefficients
    K[1][0] = 4.73e-14*pow(Te,-0.23)*exp(-10.09/Te);            // m3/s [Hjartarson et al. 2010]
    K[2][0] = 1.10e-14*pow(Te,0.42)*exp(-16.05/(Te));           // m3/s [Hjartarson et al. 2010]
    K[3][0] = 0.7e-16;                                          // m3/s
    K[4][0] = 7.89e-15*pow(Te,0.41)*exp(-14.23/Te);             // m3/s [Hjartarson et al. 2010]
    K[5][0] = 0.5e-18;                                          // m3/s
    K[6][0] = 2.35e-14*pow(Te,0.4);                             // m3/s [Hjartarson et al. 2010]
    K[7][0] = 7.30e-16*pow(Te,0.8);                             // m3/s [Hjartarson et al. 2010]
    K[8][0] = 1.88e-13*pow(Te,-0.39)*exp(-28.82/Te);            // m3/s [Hjartarson et al. 2010]
    K[9][0] = 1.00e-13*pow(Te,0.37)*exp(-14.46/Te);             // m3/s [Hjartarson et al. 2010]
    K[10][0] = 3.1e-41*sqrt(300.0/Tg);                          // m6/s [Matveyev et al. 1995]
    K[11][0] = 2.00e-15;                                        // m3/s [Hjartarson et al. 2010]
    K[13][0] = 2.68e-43*pow(Tg,-0.6);                           // m6/s [Matveyev et al. 1995]
    K[12][0] = 3.0*K[13][0];                                    // m6/s [Matveyev et al. 1995]
    Gamma = 0.151*exp(-1090.0/Tg);
    K[14][0] = 0.5*(Gamma/(2*R))*sqrt(8*kB*Tg/(pi*mH));         // 1/s [Chen et al. 1999]

    // Initial values for species densities and temperature
    nH_0 = 1.0e15;
    nH2_0 = 1.0e15;
    nHplus_0 = 1.0e15;
    nH2plus_0 = 1.0e15;
    nH3plus_0 = 1.0e15;
    Tg_0 = Tg;

    // Correct solutions
    // nH = 1.212e21;
    // nHplus = 2.613e15;
    // nH2plus = 7.542e13;
    // nH3plus = 3.27e17;
    // ne = 3.33e17;


    // ----------------------------------------------------------------------------------
    // Calculate general quantities
    // ----------------------------------------------------------------------------------
    // Total number of species
    n = p/(kB*Tg);
    rho = p/(RH2*Tg);
    Ethr[1][0] = 10.8*eVtoJ;
    V = (pi*R*R)*L;
    Ai = 2*pi*R*L;


    // ----------------------------------------------------------------------------------
    // Start the solution of the equations
    // ----------------------------------------------------------------------------------
    // Print screen initial info
    printScreen_beginning();

    // Main while loop
    while ( (err_H>1.0e-8 || err_Hplus>1.0e-8|| err_H2plus>1.0e-8 || err_H3plus>1.0e-8 || err_Tg>1.0e-8) || count<1 )
    {
        // Iteration counter
        count++;

        // Print to screen the iteration counter
        printf("Iteration %d\n", count);

        // Here place the rate coefficients that are not calculated from the BOLSIG+
        K[1][0] = 4.73e-14*pow(Te,-0.23)*exp(-10.09/Te);        // m3/s
        // K[2][0] = 1.10e-14*pow(Te,0.42)*exp(-16.05/(Te));       // m3/s
        // K[3][0] = 0.7e-16;                                      // m3/s
        // K[4][0] = 7.89e-15*pow(Te,0.41)*exp(-14.23/Te);         // m3/s
        K[5][0] = 0.5e-18;                                      // m3/s
        K[6][0] = 2.35e-14*pow(Te,0.4);                         // m3/s
        K[7][0] = 7.30e-16*pow(Te,0.8);                         // m3/s
        K[8][0] = 1.88e-13*pow(Te,-0.39)*exp(-28.82/Te);        // m3/s
        K[9][0] = 1.00e-13*pow(Te,0.37)*exp(-14.46/Te);         // m3/s
        K[10][0] = 3.1e-41*sqrt(300.0/Tg);                      // m6/s [Matveyev et al. 1995]
        K[11][0] = 2.00e-15;                                    // m3/s [Hjartarson et al. 2010]
        K[13][0] = 2.68e-43*pow(Tg,-0.6);                       // m6/s [Matveyev et al. 1995]
        K[12][0] = 3.0*K[13][0];                                // m6/s [Matveyev et al. 1995]
        Gamma = 0.151*exp(-1090.0/Tg);
        K[14][0] = 0.5*(Gamma/(2*R))*sqrt(8*kB*Tg/(pi*mH));         // 1/s [Chen et al. 1999]
        K[15][0] = 4.0e9;
        K[16][0] = 2.5e9;
        K[17][0] = 4.5e4;


        // ----------------------------------------------------------------------------------
        // Solve the balance equations
        // ----------------------------------------------------------------------------------
        count_SB = 0;
        while ( (err_H>1.0e-8 || err_Hplus>1.0e-8 || err_H2plus>1.0e-8 || err_H3plus>1.0e-8 ) || count_SB<1 )
        {
            // Loop counter
            count_SB++;
            
            // Solve the equations with SOR method
            nH      = (1.0-r1)*nH_0      + r1*(2*K[1][0]*ne_0*nH2_0+K[3][0]*ne_0*nH2_0+K[11][0]*nH2plus_0*nH2_0 - K[4][0]*ne_0*nH_0-2*K[12][0]*nH_0*nH_0*nH_0-2*K[13][0]*nH_0*nH_0*nH2_0)/K[14][0];
            nHplus  = (1.0-r1)*nHplus_0  + r1*(K[3][0]*ne_0*nH2_0+K[4][0]*ne_0*nH_0+K[8][0]*ne_0*nH2plus_0+K[9][0]*ne_0*nH3plus_0 - K[5][0]*ne_0*nHplus_0-K[10][0]*nH2_0*nH2_0*nHplus_0)/K[15][0];
            nH2plus = (1.0-r2)*nH2plus_0 + r2*(K[2][0]*ne_0*nH2_0-K[8][0]*ne_0*nH2plus_0-K[11][0]*nH2_0*nH2plus_0)/K[16][0];
            nH3plus = (1.0-r1)*nH3plus_0 + r1*(K[10][0]*nH2_0*nH2_0*nHplus_0+K[11][0]*nH2_0*nH2plus_0-K[7][0]*ne_0*nH3plus_0-K[9][0]*ne_0*nH3plus_0)/K[17][0];

            // Calculate the e and H2 densities
            ne = nHplus + nH2plus + nH3plus;
            nH2 = n - nH - nHplus - nH2plus - nH3plus;

            // Calculate errors for this loop
            err_e = relativeError(ne,ne_0);
            err_H = relativeError(nH,nH_0);
            err_H2 = relativeError(nH2,nH2_0);
            err_Hplus = relativeError(nHplus,nHplus_0);
            err_H2plus = relativeError(nH2plus,nH2plus_0);
            err_H3plus = relativeError(nH3plus,nH3plus_0);

            // Prepare for next iteration
            ne_0 = ne;
            nH_0 = nH;
            nH2_0 = nH2;
            nHplus_0 = nHplus;
            nH2plus_0 = nH2plus;
            nH3plus_0 = nH3plus;

            if (fmod(count_SB,3000000)==0)
                printf("Densities: n=%.4e ne=%.4e nH=%.4e nH2=%.4e nH+=%.4e nH2+=%.4e nH3+=%.4e SB_count=%d\n",n,ne,nH,nH2,nHplus,nH2plus,nH3plus,count_SB);
        }   

        // Print species balance results
        printf("Densities: n=%.4e ne=%.4e nH=%.4e nH2=%.4e nH+=%.4e nH2+=%.4e nH3+=%.4e SB_count=%d\n",n,ne,nH,nH2,nHplus,nH2plus,nH3plus,count_SB);


        // ----------------------------------------------------------------------------------
        // Run the BOLSIG+ code
        // ----------------------------------------------------------------------------------
        // Write the BOLSIG+ input file
        writeBOLSIGinput();

        // Run the BOLSIG+ code according to the Operating System
        #ifdef _WIN32
            system("bolsigminus_win bolsigInput.dat > /null 2>&1");
        #elif __unix__
            system("./bolsigminus_unix bolsigInput.dat > /dev/null 2>&1");
        #else
        {
            printf("Error: The current OS is not recognised, cannot run BOLSIG+ !\n");
            exit(EXIT_FAILURE);
        }
        #endif

        // Read information from the BOLSIG+ output file
        readRateCoeff(K);
        readThresholdEnergies(Ethr);
        Te = calculateTe();

        // Calculate additional parameters
        M = (fabs(nHplus)*mH+fabs(nH2plus)*mH2+fabs(nH3plus)*mH3)/(fabs(nHplus)+fabs(nH2plus)+fabs(nH3plus));
        uB = sqrt(kB*fabs(Te*eVtoK)/M);
        ns = ne;
        rhoi = pin/(RH2*Tgi);
        Q = (Tg/Tgi)*(2*n/(2*n-nH-nHplus+nH3plus))*Qi;
        // rho = p/(RH2*Tg);


        // ----------------------------------------------------------------------------------
        // Solve energy equation
        // ----------------------------------------------------------------------------------
        // Calculate powers for energy equation
        PinletHeat = rhoi*Qi*Cp*Tgi;
        Pion = V*Ethr[4][0]*K[4][0]*ne*nH + V*Ethr[2][0]*K[2][0]*ne*nH2 + V*Ethr[3][0]*K[3][0]*ne*nH2;
        Pdis = V*Ethr[1][0]*K[1][0]*ne*nH2;
        Pele = V*Ethr[20][1]*K[20][1]*ne*nH + V*Ethr[20][2]*K[20][2]*ne*nH + V*Ethr[20][3]*K[20][3]*ne*nH + V*Ethr[18][1]*K[18][1]*ne*nH2 + V*Ethr[18][2]*K[18][2]*ne*nH2 + V*Ethr[18][3]*K[18][3]*ne*nH2 + V*Ethr[19][1]*K[19][1]*ne*nH2 + V*Ethr[19][2]*K[19][2]*ne*nH2 ;
        Pvib = V*Ethr[21][1]*K[21][1]*ne*nH2 + V*Ethr[21][2]*K[21][2]*ne*nH2;
        Prot = V*Ethr[22][0]*K[22][0]*ne*nH2;
        Pela = V*ne*nH*(3*me/mH)*Te*eVtoJ*K[24][0] + V*ne*nH2*(3*me/mH2)*Te*eVtoJ*K[23][0];
        Piw  = (0.5+log(M/(2*pi*me)))*Te*eVtoJ*ns*uB*Ai;
        Pew  = 2.0*Te*eVtoJ*ns*uB*Ai;
        PDH12 = V*DH12*K[12][0]*nH*nH*nH;
        PDH13 = V*DH13*K[13][0]*nH*nH*nH2;
        PDH14 = V*DH14*K[14][0]*nH;

        // Solve the energy equation
        count_Tg = 0;
        while ( err_Tg>1.0e-8 || count_Tg<1 )
        {
            count_Tg++;
            Tg = (1.0-r3)*Tg_0 + r3*(PinletHeat + Pela + Piw + Pew + Pvib + Prot - PDH12 - PDH13 - PDH14 + h*Ai*Tatm + epsilon*sigma*Ai*(pow(Tatm,4)-pow(Tg_0,4)))/(rho*Q*Cp+h*Ai);
            // Tg = (1.0-r3)*Tg_0 + r3*(PinletHeat + Pela + Piw + Pew + Pvib + Prot - PDH12 - PDH13 - PDH14 + h*Ai*(Tatm-Tg_0) + epsilon*sigma*Ai*(pow(Tatm,4)-pow(Tg_0,4)))/(rho*Q*Cp);
            err_Tg = relativeError(Tg,Tg_0);
            Tg_0 = Tg;

            if (fmod(count_Tg,50000000)==0)
                printf("\tTemperatures: Tg=%.2f Te=%.2f Tg Iter=%d\n", Tg, Te, count_Tg );
        }

        // Print temperature results
        printf("Temperatures: Tg=%.2f Te=%.2f Tg_count=%d\n", Tg, Te, count_Tg);

        // Calculate relative errors
        err_e = relativeError(ne,ne_old);
        err_H = relativeError(nH,nH_old);
        err_H2 = relativeError(nH2,nH2_old);
        err_Hplus = relativeError(nHplus,nHplus_old);
        err_H2plus = relativeError(nH2plus,nH2plus_old);
        err_H3plus = relativeError(nH3plus,nH3plus_old);
        err_Tg = relativeError(Tg,Tg_old);
        err_Te = relativeError(Te,Te_old);

        printf("Errors: H2=%.2e H=%.2e H+=%.2e H2+=%.2e H3+=%.2e\n\n",err_H2, err_H, err_Hplus, err_H2plus, err_H3plus);

        // Store solution for the next iteration
        ne_0 = ne;
        nH_0 = nH;
        nH2_0 = nH2;
        nHplus_0 = nHplus;
        nH2plus_0 = nH2plus;
        nH3plus_0 = nH3plus;
        Tg_0 = Tg;
        ne_old = ne;
        nH_old = nH;
        nH2_old = nH2;
        nHplus_old = nHplus;
        nH2plus_old = nH2plus;
        nH3plus_old = nH3plus;
        Tg_old = Tg;
        Te_old = Te;
    }

    // Print screen of rate constants or threshold energies
    printScreen_K_Ethr();

    // Print final results
    printScreen_finalResults();

    return 0;
}




