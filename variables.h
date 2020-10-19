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
    File name:          variables.h
    Type:               header file
    Short Description:  This file contains all the global variables used in the main
                        code and in every function.

---------------------------------------------------------------------------------------------  */

// Physical constants
#define pi 3.14159
#define kB 1.3806503e-23
#define NA 6.02214076e23
#define sigma 5.670367e-08
#define dgrFreedom 3.0
#define e 1.602176565e-19
#define me 9.1094e-31
#define mp 1.6726e-27
#define mH mp
#define mH2 2*mp
#define mH3 3*mp

// Conversion units
#define eVtoJ 1.602176565e-19
#define JtoeV 6.241509e+18
#define eVtoK (2/(kB*dgrFreedom))*e
#define KtoeV 1.0/(eVtoK)
#define TorrtoPa 133.322
#define PatoTorr 1.0/(TorrtoPa)
#define sccmtom3s 1.666667e-8
#define m3stosccm 1.0/sccmtom3s
#define TdtoVm2 1.0e-21
#define Vm2toTd 1.0e+21

// Spiecies concentration - volume averaged
double n, ne, nH, nH2, nHplus, nH2plus, nH3plus;
double ne_0, nH_0, nH2_0, nHplus_0, nH2plus_0, nH3plus_0;
double ne_old, nH_old, nH2_old, nHplus_old, nH2plus_old, nH3plus_old;

// Errors
double err_e, err_H, err_H2, err_Hplus, err_H2plus, err_H3plus, err_Tg, err_Te;

// Rate constants and threshold energies
// These are 2D arrays, rows are the number of reactions, columns are the subreactions
// of each reaction. If a reaction does not have any subreactions then the value is stored 
// in the zeroth column. The K[0][..] and Ethr[0][..] values are not used.
double **K, **Ethr;

// State variables
double p, pin, patm, Tg, Te, Tgi, Tatm, rhoi, rho;
double Tg_0, Tg_old, Te_old;

// Power palance terms
double PinletHeat, Pmw, Piw, Pew, Pela, Pion, Pdis, Pele, Pvib, Prot, PDH12, PDH13, PDH14;

// Geometric variables
double R, L, V, Ai;

// Other variables
double Gamma, uB, ns, M, Q, Qi, Cp, h, epsilon, E, freq, DH12, DH13, DH14, RH2;
double r1, r2, r3, r4;

// Auxiliary programming variables
#define MAXCHAR 150
char str[MAXCHAR];
int **map_reactions;
int i=0, j=0, k=0, count=0, count_SB=0, count_Tg=0, count_Te=0, count_BOLSIG=0;
int react_num, subreact_num;
char neutralSpecies[15][MAXCHAR]={0};
int NoNeutralSpecies;
bool printScreenK, printScreenEthr;

// BOLSIG+ file names
char BOLSIG_input[MAXCHAR];
char BOLSIG_output[MAXCHAR];
char BOLSIG_crossSections[MAXCHAR];

