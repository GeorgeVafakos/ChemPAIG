/*  ---------------------------------------------------------------------------------------------
                                                          |
  ____                          _____       ____          | Version: 1.0
 //   \ ||                      ||  \\ ||  //  \\         | Developers: CFD Lab,
||      ||___   ___  _ __  ___  ||__// || ||              |             High-Voltage Lab
||      ||  \\ //__\ |/ \\// \\ ||     || ||  ====        |   
 \\___/ ||  || \\__  ||  ||  || ||     ||  \\__//         | Developed in 
                                                          |        University of Patras, Greece
                                                          |     
-------------------------------------------------------------------------------------------------

File info
=========
    File name:          functions.h
    Type:               header file
    Short Description:  This file contains all the functions used in the code.

Function name                   Type        Description
=============                   ====        ===========
- allocate                      void        Allocate an array (int or double) according to the input argumets
- readfile                      void        Read the variables of the input file.
- writeBOLSIGinput              void        Write the BOLSIG+ inpur file.
- countBolsigReactions          int         Count how many reactions exist in the BOLSIG+ cross section file.
- mapRateCoeffs                 void        Sort the reactions written in the BOLSI+ cross section file in the correct order.
- readRateCoeff                 void        Read the rate constants from the BOLSIG+ output file.
- readThresholdEnergies         void        Read the threshold energies from the BOLSIG+ output file.
- calculateTe                   double      Calculate the electron temperature Te from the BOLSIG+ output file.
- relativeError                 double      Calculate the reletive error between the two input values.
- printScreen_beginning         void        Display in screen the initial information of the simulation.
- printScreen_K_Ethr            void        Display in screen the reaction rates or/and the threshold energies.
- printScreen_finalResults      void        Display in screen the final results.

---------------------------------------------------------------------------------------------  */


// --------------------------------------------------------------------------------------------------------
// Allocate 2D array
// --------------------------------------------------------------------------------------------------------
void allocate_int (int*** arr, int row, int col)
{
  *arr = (int**)calloc(row , sizeof(int*));
  for(i=0 ; i<row ; i++)
    (*arr)[i] = (int*)calloc(col , sizeof(int));
} 

void allocate_double (double*** arr, int row, int col)
{
  *arr = (double**)calloc(row , sizeof(double*));
  for(i=0 ; i<row ; i++)
    (*arr)[i] = (double*)calloc(col , sizeof(double));
} 

// Perform function overload. If the array to be allocated is int perform the allocate_int function, if it is
// double perform the allocate_double function. The new function is the allocate function.
#define allocate(arr, row, col ) _Generic(arr, int***: allocate_int, double***: allocate_double)(arr, row, col)


// --------------------------------------------------------------------------------------------------------
// Read variables from the input file
// --------------------------------------------------------------------------------------------------------
void readfile (char filename[MAXCHAR])
{
    // Local variables
    char str_local[MAXCHAR];

    // Open file
    FILE * fp;
    fp = fopen(filename,"r");

    // Checκ if file exists
    if (fp==NULL)
    {
        printf("Error: The file %s was not found!\n",filename);
        exit(EXIT_FAILURE);
    }

    while (!feof(fp))
    {
        // The purpose of each one of the following ifs, is to read the corresponding variable from the input file.
        // The user must write the variable name, afterwars the input value and finally a semicolon (;). Spaces
        // don't matter at all.
        // CAUTION: when adding a new input variable, be careful to use the functions 'atoi', 'atof' or 'strcpy'
        // for ints, floats/doubles or strings respectively.

        // Clear string
        memset(str,'\0', strlen(str));

        // Read word
        fscanf(fp, "%s", str);

        if (strcmp(str, "neutralSpecies") == 0)
        {
            i=0;
            NoNeutralSpecies=0;
            fscanf(fp, "%s", str);
            while (str[0] != ';')
            {
                NoNeutralSpecies++;
                if (str[strlen(str)-1] == ';')
                {
                    str[strlen(str)-1] = '\0';
                    strcpy(neutralSpecies[i],str);
                    i++;
                    break;
                }
                else
                {
                    strcpy(neutralSpecies[i],str);
                    fscanf(fp, "%s", str);
                    i++;
                }
            }
        }

        if (strcmp(str,"react_num") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                react_num = (atoi(str)+1);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    react_num = (atoi(str)+1);
            }
        }

        if (strcmp(str,"subreact_num") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                subreact_num = (atoi(str)+1);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    subreact_num = (atoi(str)+1);
            }
        }

        if (strcmp(str,"R") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                R = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    R = atof(str);
            }
        }

        if (strcmp(str,"L") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                L = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    L = atof(str);
            }
        }

        if (strcmp(str,"Te") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Te = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Te = atof(str);
            }
        }

        if (strcmp(str,"Tg") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Tg = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Tg = atof(str);
            }
        }

        if (strcmp(str,"Tgi") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Tgi = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Tgi = atof(str);
            }
        }

        if (strcmp(str,"p") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                p = atof(str)*TorrtoPa;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    p = atof(str)*TorrtoPa;
            }
        }

        if (strcmp(str,"pin") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                pin = atof(str)*TorrtoPa;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    pin = atof(str)*TorrtoPa;
            }
        }

        if (strcmp(str,"r1") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                r1 = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    r1 = atof(str);
            }
        }

        if (strcmp(str,"r2") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                r2 = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    r2 = atof(str);
            }
        }

        if (strcmp(str,"r3") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                r3 = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    r3 = atof(str);
            }
        }

        if (strcmp(str,"r4") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                r4 = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    r4 = atof(str);
            }
        }

        if (strcmp(str,"Qi") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Qi = atof(str)*sccmtom3s;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Qi = atof(str)*sccmtom3s;
            }
        }

        if (strcmp(str,"E") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                E = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    E = atof(str);
            }
        }

        if (strcmp(str,"freq") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                freq = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    freq = atof(str);
            }
        }

        if (strcmp(str,"Pmw") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Pmw = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Pmw = atof(str);
            }
        }

        if (strcmp(str,"Cp") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Cp = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Cp = atof(str);
            }
        }

        if (strcmp(str,"h") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                h = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    h = atof(str);
            }
        }

        if (strcmp(str,"RH2") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                RH2 = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    RH2 = atof(str);
            }
        }

        if (strcmp(str,"DH12") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                DH12 = atof(str)*eVtoJ;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    DH12 = atof(str)*eVtoJ;
            }
        }

        if (strcmp(str,"DH13") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                DH13 = atof(str)*eVtoJ;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    DH13 = atof(str)*eVtoJ;
            }
        }

        if (strcmp(str,"DH14") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                DH14 = atof(str)*eVtoJ;
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    DH14 = atof(str)*eVtoJ;
            }
        }

        if (strcmp(str,"epsilon") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                epsilon = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    epsilon = atof(str);
            }
        }

        if (strcmp(str,"Tatm") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                Tatm = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    Tatm = atof(str);
            }
        }

        if (strcmp(str,"patm") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                patm = atof(str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    patm = atof(str);
            }
        }


        if (strcmp(str,"BOLSIG_input") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                strcpy(BOLSIG_input, str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    strcpy(BOLSIG_input, str);
            }
        }

        if (strcmp(str,"BOLSIG_output") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                strcpy(BOLSIG_output, str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    strcpy(BOLSIG_output, str);
            }
        }

        if (strcmp(str,"BOLSIG_crossSections") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                strcpy(BOLSIG_crossSections, str);
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                    strcpy(BOLSIG_crossSections, str);
            }
        }

        if (strcmp(str,"printScreenK") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                if (strcmp(str,"true") == 0 || strcmp(str,"TRUE") == 0 || strcmp(str,"True") == 0 )
                    printScreenK = true;
                else if (strcmp(str,"false") == 0 || strcmp(str,"FALSE") == 0 || strcmp(str,"False") == 0 )
                    printScreenK = false;
                else
                {
                    printf("ERROR\n");
                }
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                {
                    if (strcmp(str,"true") == 0 || strcmp(str,"TRUE") == 0 || strcmp(str,"True") == 0 )
                        printScreenK = true;
                    else if (strcmp(str,"false") == 0 || strcmp(str,"FALSE") == 0 || strcmp(str,"False") == 0 )
                        printScreenK = false;
                    else
                    {
                    printf("Error: Unknown input value in printScreenK in the file: input.txt\n");
                    exit(EXIT_FAILURE);
                    }
                }
            }
        }

        if (strcmp(str,"printScreenEthr") == 0)
        {
            fscanf(fp, "%s", str);
            if (str[strlen(str)-1] == ';')
            {
                str[strlen(str)-1] = '\0';
                if (strcmp(str,"true") == 0 || strcmp(str,"TRUE") == 0 || strcmp(str,"True") == 0 )
                    printScreenEthr = true;
                else if (strcmp(str,"false") == 0 || strcmp(str,"FALSE") == 0 || strcmp(str,"False") == 0 )
                    printScreenEthr = false;
                else
                {
                    printf("Error: Unknown input value in printScreenEthr in the file: input.txt\n");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                fscanf(fp, "%s", str_local);
                if (str_local[0] == ';')
                {
                    if (strcmp(str,"true") == 0 || strcmp(str,"TRUE") == 0 || strcmp(str,"True") == 0 )
                        printScreenEthr = true;
                    else if (strcmp(str,"false") == 0 || strcmp(str,"FALSE") == 0 || strcmp(str,"False") == 0 )
                        printScreenEthr = false;
                    else
                    {
                        printf("ERROR\n");
                    }
                }
            }
        }


    }

    // Close file
    fclose(fp);
}


// --------------------------------------------------------------------------------------------------------
// Write VOLSIG input file
// --------------------------------------------------------------------------------------------------------
void writeBOLSIGinput ()
{
    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_input,"w");

    fprintf(fp, "! Comment\n");
    fprintf(fp, "/ Comment\n");
    fprintf(fp, "\n");

    fprintf(fp, "/NOSCREEN\n");
    fprintf(fp, "\n");

    fprintf(fp, "CLEARCOLLISIONS\n");
    fprintf(fp, "\n");

    fprintf(fp, "READCOLLISIONS\n");
    fprintf(fp, "%s\t\t/ File\n", BOLSIG_crossSections);
    for (i=0 ; i<NoNeutralSpecies ; i++)
        fprintf(fp, "%s\t", neutralSpecies[i]);
    fprintf(fp, "\t\t\t\t/ Species\n");
    fprintf(fp, "%d\t\t\t\t\t\t/ Extrapolate: 0= No 1= Yes\n", 1);
    fprintf(fp, "\n");

    fprintf(fp, "CONDITIONS\n");
    fprintf(fp, "%.4lf\t\t\t\t\t/ Electric field / N (Td) \n", Vm2toTd*E/(nH+nH2));
    fprintf(fp, "%.4e\t\t\t\t/ Angular field frequency / N (m3/s) \n", freq/(nH+nH2));
    fprintf(fp, "0.0\t\t\t\t\t\t/ Cosine of E-B field angle  \n");
    fprintf(fp, "%.2lf\t\t\t\t\t/ Gas temperature (K)  \n",Tg);
    fprintf(fp, "0.0\t\t\t\t\t\t/ Excitation temperature (K)\n");
    fprintf(fp, "0.0\t\t\t\t\t\t/ Transition energy (eV)\n");
    fprintf(fp, "%.4e\t\t\t\t/ Ionization degree \n", fabs(ne/(nH+nH2)));
    // fprintf(fp, "%.4e\t\t\t\t/ Ionization degree \n", 0.0);
    // fprintf(fp, "%.1e\t\t\t\t\t/ Plasma density (1/m3) \n",n);
    fprintf(fp, "%.1e\t\t\t\t\t/ Plasma density (1/m3) \n",ne);
    fprintf(fp, "%.1f\t\t\t\t\t\t/ Ion charge parameter \n",1.0);
    fprintf(fp, "%.4e\t\t\t\t/ Ion/neutral mass ratio \n", ((nHplus+nH2plus+nH3plus)/(nHplus/mH+nH2plus/mH2+nH3plus/mH3))*((nH/n)/mH+(nH2/n)/mH2) );
    // fprintf(fp, "%.4e\t\t\t\t/ Ion/neutral mass ratio \n", 1.0 );
    // fprintf(fp, "%.4e\t\t\t\t/ Ion/neutral mass ratio \n", (nHplus/mH + nH2plus/mH2 + nH3plus/mH3)/(nH/mH + nH2/mH2) );
    fprintf(fp, "%d\t\t\t\t\t\t/ e-e momentum effects: 0=No; 1=Yes* \n",0);
    fprintf(fp, "%d\t\t\t\t\t\t/ Energy sharing: 1=Equal*; 2=One takes all \n", 1);
    fprintf(fp, "%d\t\t\t\t\t\t/ Growth: 1=Temporal*; 2=Spatial; 3=Not included; 4=Grad-n expansion \n", 1);
    fprintf(fp, "%.1f\t\t\t\t\t\t/ Maxwellian mean energy (eV) \n", 0.0);
    fprintf(fp, "%d\t\t\t\t\t\t/ # of grid points \n", 200);
    fprintf(fp, "%d\t\t\t\t\t\t/ Manual grid: 0=No; 1=Linear; 2=Parabolic \n", 0);
    fprintf(fp, "%.1f\t\t\t\t\t\t/ Manual maximum energy (eV) \n", 1.0);
    fprintf(fp, "%.1e\t\t\t\t\t/ Precision \n", 1.0e-10);
    fprintf(fp, "%.1e\t\t\t\t\t/ Convergence \n", 1.0e-4);
    fprintf(fp, "%d\t\t\t\t\t/ Maximum # of iterations \n", 2000);
    fprintf(fp, "%f  %f\t\t/ Gas composition fractions \n", nH2/(nH+nH2), nH/(nH+nH2) );
    fprintf(fp, "%d\t\t\t\t\t\t/ Normalize composition to unity: 0=No; 1=Yes \n", 1);
    fprintf(fp, "\n");

    fprintf(fp, "RUN\n");
    fprintf(fp, "\n");

    fprintf(fp, "SAVERESULTS\n");
    fprintf(fp, "%s\t\t/ File\n", BOLSIG_output);
    fprintf(fp, "%d\t\t\t\t\t\t/ Format: 1=Run by run; 2=Combined; 3=E/N; 4=Energy; 5=SIGLO; 6=PLASIMO\n", 1);
    fprintf(fp, "%d\t\t\t\t\t\t/ Conditions: 0=No; 1=Yes\n", 1);
    fprintf(fp, "%d\t\t\t\t\t\t/ Transport coefficients: 0=No; 1=Yes\n", 1);
    fprintf(fp, "%d\t\t\t\t\t\t/ Rate coefficients: 0=No; 1=Yes\n", 1);
    fprintf(fp, "%d\t\t\t\t\t\t/ Reverse rate coefficients: 0=No; 1=Yes\n", 0);
    fprintf(fp, "%d\t\t\t\t\t\t/ Energy loss coefficients: 0=No; 1=Yes\n", 0);
    fprintf(fp, "%d\t\t\t\t\t\t/ Distribution function: 0=No; 1=Yes\n", 0);
    fprintf(fp, "%d\t\t\t\t\t\t/ Skip failed runs: 0=No; 1=Yes\n", 0);
    fprintf(fp, "\n");

    fprintf(fp, "END\n");

    fclose(fp);
}

// --------------------------------------------------------------------------------------------------------
// Correspond reaction number in BOLSIG+ with reaction number in reference paper
// --------------------------------------------------------------------------------------------------------
int countBolsigReactions ()
{
    // Local variables
    int count_R=0;

    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_crossSections,"r");

    // Read line-by-line the crossSection file
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Delete '\n' character from string
        str[strcspn(str, "\n")] = 0;

        // Count the reactions
        if (strcmp(str,"ELASTIC")==0 || strcmp(str,"EFFECTIVE")==0 || strcmp(str,"IONIZATION")==0 || strcmp(str,"ATTACHMENT")==0 || strcmp(str,"EXCITATION")==0 || strcmp(str,"ROTATION")==0)
            count_R++;
    }

    // Close file
    fclose(fp);

    // Return the number of reactions
    return (count_R+1);
}


// --------------------------------------------------------------------------------------------------------
// Correspond reaction number in BOLSIG+ with reaction number in reference paper
// --------------------------------------------------------------------------------------------------------
void mapRateCoeffs (int **array_map)
{
    // Local variables
    char reaction_str[MAXCHAR], subreaction_str[MAXCHAR];
    int count_R=0;
    char str_species[MAXCHAR], str_local[MAXCHAR];
    int *array_species;
    int **array_map_temp;

    // Allocate local arrays
    array_species = (int*) calloc(count_BOLSIG, sizeof(int));
    allocate(&array_map_temp, count_BOLSIG, 2);

    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_crossSections,"r");

    // Read line-by-line the crossSection file
    count_R=0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Delete '\n' character from string
        str[strcspn(str, "\n")] = 0;

        // Read the reaction and subreaction number
        if (strcmp(str,"ELASTIC")==0 || strcmp(str,"EFFECTIVE")==0 || strcmp(str,"IONIZATION")==0 || strcmp(str,"ATTACHMENT")==0 || strcmp(str,"EXCITATION")==0 || strcmp(str,"ROTATION")==0)
        {
            // Count reactions as they appear in BOLSIG+ cross-section file
            count_R++;

            // Determine the neutral species of each reaction 
            fscanf(fp, "%s", str_species);

            // Check if there are more neutral spieces in the cross-sections file tham in the input file
            for (i=0 ; i<NoNeutralSpecies ; i++)
            {
                if (strcmp(str_species,neutralSpecies[i]) == 0)
                {
                    break;
                }
                if (i == NoNeutralSpecies-1)
                {
                    printf("Error: Unknown neutral species in a reaction in the file: %s\n", BOLSIG_crossSections);
                    exit(EXIT_FAILURE);
                }
            }

            // Search for the "REACTION:" entry of the reaction
            fscanf(fp, "%s", str);
            while (!feof(fp))
            {
                strncpy(str_local,str,8);   // check for the 'REACTION' word inside the cross section info of each reaction
                str_local[8] = 0;   // terminate the string at the 8th position
                if (strcmp(str_local,"REACTION") == 0)
                {
                    // Clear the strings contents (optional)
                    memset(reaction_str,'\0', strlen(reaction_str));
                    memset(subreaction_str,'\0', strlen(subreaction_str));

                    // Read the rest of the line that begins with "REACTION:"
                    fgets(str, MAXCHAR, fp);

                    // Read every character of the rest of the line and determine which one is for the reaction and which the subreaction
                    i=0;
                    j=0;
                    k=0;
                    while (str[i]!='\n')
                    {
                        // If the character is one of the following characters, ignore it
                        if (str[i]==' ' || str[i]==':' || str[i]=='-' || str[i]==',' || str[i]=='(' || str[i]==')' || str[i]=='[' || str[i]==']' || str[i]=='_')
                        {
                            i++;
                            continue;
                        }

                        // Check is the character is digit of letter
                        if (isdigit(str[i]))
                        {
                            reaction_str[j]=str[i];
                            j++;
                        }
                        else if (isalpha(str[i]))
                        {
                            subreaction_str[k]=str[i];
                            k++;
                        }
                        else
                        {
                            printf("Error: Unknown character '%c' in reaction No.%d in the file: %s\n",str[i],count_R,BOLSIG_output);
                            exit(EXIT_FAILURE);
                        }

                        // Go to the next character
                        i++;
                    }

                    // End strings with the end character '\n' to avoid errors
                    reaction_str[j] = 0;
                    subreaction_str[k] = 0;

                    // Match the subreaction letters to numbers for the int-type array
                    for (i=0 ; i<NoNeutralSpecies ; i++)
                    {
                        if (strcmp(str_species,neutralSpecies[i]) == 0)
                        {
                            // Correspond neutral species with reaction
                            array_species[count_R] = i;

                            // Convert the reaction number into int
                            array_map_temp[count_R][0] = atoi(reaction_str);

                            if (strcmp(subreaction_str,"") == 0);
                            else if (strcmp(subreaction_str,"a") == 0 || strcmp(subreaction_str,"A") == 0)
                                array_map_temp[count_R][1] = 1;
                            else if (strcmp(subreaction_str,"b") == 0 || strcmp(subreaction_str,"B") == 0)
                                array_map_temp[count_R][1] = 2;
                            else if (strcmp(subreaction_str,"c") == 0 || strcmp(subreaction_str,"C") == 0)
                                array_map_temp[count_R][1] = 3;
                            else
                            {
                                printf("Error: Unknown character '%s' in a subreaction in the file: %s. Availiable subreactions: a, b or c.\n",subreaction_str,BOLSIG_crossSections);
                                exit(EXIT_FAILURE);
                            }
                        }
                    }

                    // Go to another reaction
                    break;
                }
                else
                    fscanf(fp, "%s", str);
            }
        }
    }

    // Put the reactions in the order that they appear in the BOLSIG output file
    j=0;
    for (i=0 ; i<NoNeutralSpecies ; i++)
        for (count_R = 1; count_R < count_BOLSIG; count_R++)
            if (array_species[count_R]==i)
            {
                j++;
                array_map[j][0] = array_map_temp[count_R][0];
                array_map[j][1] = array_map_temp[count_R][1];
            }


    // Close file
    fclose(fp);
}


// --------------------------------------------------------------------------------------------------------
// Read rate coefficients from BOLSIG++ output file
// --------------------------------------------------------------------------------------------------------
void readRateCoeff (double **K_local)
{
    // Local variables
    double K_value;

    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_output,"r");

    // Checκ if file exists
    if (fp==NULL)
    {
        printf("Error: The file %s was not found!\n",BOLSIG_output);
        exit(EXIT_FAILURE);
    }

    // Map rate coefficients according to the order they appear in the BOLSIG output file
    mapRateCoeffs(map_reactions);

    // Read line-by-line the BOLSIG output file
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        str[strcspn(str, "\n")] = 0;

        // Read the BOLSIG output  file coefficients
        if (strcmp(str,"Rate coefficients (m3/s)") == 0)
        {
            for (i = 1; i < count_BOLSIG; i++)
            {
                fscanf(fp, "%s", str);
                fscanf(fp, "%s", str);
                fscanf(fp, "%s", str);

                if (strcmp(str,"Elastic") == 0)
                {
                    fscanf(fp, "%lf", &K_value);
                }
                else
                {
                    fscanf(fp, "%s", str);
                    fscanf(fp, "%s", str);
                    fscanf(fp, "%lf", &K_value);
                }
                K_local[map_reactions[i][0]][map_reactions[i][1]] = K_value;
            }

        }
    }

    // Close file
    fclose(fp);
}


// --------------------------------------------------------------------------------------------------------
// Read threshold energies from BOLSIG++ corss-sections file
// --------------------------------------------------------------------------------------------------------
void readThresholdEnergies (double** Ethr_local)
{
    // Local variables
    double Ethr_value;

    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_output,"r");

    // Checκ if file exists
    if (fp==NULL)
    {
        printf("Error: The file %s was not found!\n",BOLSIG_output);
        exit(EXIT_FAILURE);
    }

    // Map rate coefficients according to the order they appear in the BOLSIG output file
    mapRateCoeffs(map_reactions);

    // Read line-by-line the BOLSIG output file
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        str[strcspn(str, "\n")] = 0;

        // Read the BOLSIG output file threshold energies
        if (strcmp(str,"Rate coefficients (m3/s)") == 0)
        {
            for (i = 1; i < count_BOLSIG; i++)
            {
                fscanf(fp, "%s", str);
                fscanf(fp, "%s", str);
                fscanf(fp, "%s", str);

                if (strcmp(str,"Elastic") == 0)
                    Ethr_value = 0.0;
                else
                    fscanf(fp, "%lf", &Ethr_value);

                // Go to the next line
                fgets(str, MAXCHAR, fp);

                // Insert the energies in the right position in the array in Joules
                // Ethr_temp[map_reactions[i][0]][map_reactions[i][1]] = Ethr_value*eVtoJ;
                Ethr_local[map_reactions[i][0]][map_reactions[i][1]] = Ethr_value*eVtoJ;
            }

        }
    }

    // Close file
    fclose(fp);
}


// --------------------------------------------------------------------------------------------------------
// Read threshold energies from BOLSIG++ corss-sections file
// --------------------------------------------------------------------------------------------------------
double calculateTe()
{
    // Local variables
    double Te_BOLSIG, Emean;
    char str_local[MAXCHAR];

    // Open file
    FILE * fp;
    fp = fopen(BOLSIG_output,"r");

    // Read word-by-word the BOLSIG output file
    while (!feof(fp))
    {
        // Clear string
        memset(str,'\0', strlen(str));

        // Read word
        fscanf(fp, "%s", str);
        if (strcmp(str, "Mean") == 0)
        {
            fscanf(fp, "%s", str);
            if (strcmp(str, "energy") == 0)
            {
                fscanf(fp, "%s", str);
                fscanf(fp, "%lf", &Emean);
                break;
            }
        }
    }

    Te_BOLSIG = (2.0*Emean)/dgrFreedom;

    // Close file
    fclose(fp);

    return Te_BOLSIG;
}


// --------------------------------------------------------------------------------------------------------
// Calculate the relative error between two values
// --------------------------------------------------------------------------------------------------------
double relativeError(double f_new, double f_old)
{
    return fabs(f_new-f_old)/fabs(f_new);
}


// --------------------------------------------------------------------------------------------------------
// Printd screen functions
// --------------------------------------------------------------------------------------------------------
void printScreen_beginning()
{

    printf("/*  --------------------------------------------------------------------------------------------- \n");
    printf("                                                          | \n");
    printf("  ____                          _____       ____          | Version: 1.0 \n");
    printf(" //   \\ ||                      ||  \\\\ ||  //  \\\\         | Developers: CFD Lab, \n");
    printf("||      ||___   ___  _ __  ___  ||__// || ||              |             High-Voltage Lab \n");
    printf("||      ||  \\\\ //__\\ |/ \\\\// \\\\ ||     || ||  ====        |   \n");
    printf(" \\\\___/ ||  || \\\\__  ||  ||  || ||     ||  \\\\__//         | Developed in \n");
    printf("                                                          |        University of Patras, Greece \n");
    printf("                                                          |     \n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf(" \n");
    printf(" \n");
    printf("Variables loaded ....................... [OK]\n");
    printf(" \n");
    printf("Arrays allocated ....................... [OK]\n");
    printf(" \n");
    printf("Initial conditions implemented ......... [OK]\n");
    printf(" \n");
    printf("Simulation Info\n");
    printf("===============\n");
    printf("Tube radius             R = %.2f\t[cm]\n",R*1.0e2);
    printf("Tube length             L = %.2f\t[cm]\n",L*1.0e2);
    printf("Working pressure        p = %.2f\t[Torr]\n",p*PatoTorr);
    printf("Inlet temperature       Tgi = %.2f\t[K]\n", Tgi);
    printf("Inlet flow rate         Qi = %.2f\t[sccm]\n",Qi*m3stosccm);
    printf("Electric field          E = %.2f\t[V/m]\n", E);
    printf("Frequency               freq = %.3f\t[GHz]\n",freq*1.0e-9);
    printf(" \n");
    printf("Starting the simulation\n");
    printf(" \n");
}


void printScreen_K_Ethr()
{
    if (printScreenK)
    {
        printf("Rate coefficients\n");
        printf("=================\n");
        for (i = 1; i < react_num; i++)
        {
            printf("K[%d] = ",i);
            for (j = 0; j < subreact_num; j++)
            {
                if (K[i][j] != 0)
                    printf("%.4e ",K[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    if (printScreenEthr)
    {
        printf("Threshold energies\n");
        printf("==================\n");
        for (i = 1; i < react_num; i++)
        {
            printf("E[%d] = ",i);
            for (j = 0; j < subreact_num; j++)
            {
                if (Ethr[i][j] != 0)
                    printf("%.4e ",Ethr[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void printScreen_finalResults()
{
    printf("Final results\n");
    printf("=============\n");
    printf("Iterations=%d n=%.4e ne=%.4e nH=%.4e nH2=%.4e nH+=%.4e nH2+=%.4e nH3+=%.4e Tg=%.2f Te=%.2f \n",count,n,ne,nH,nH2,nHplus,nH2plus,nH3plus,Tg,Te);
    printf("\n");
    printf("End of simulation!\n");
}