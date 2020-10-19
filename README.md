# ChemPIGS ver1.0

This is a computational code for calculating the species densities (volume averaged)
and gas temperature of a partially ionized low pressure hydrogen plasma, using the
mathematical 0-D model described by Chen et al. [1]. The electron temeprature and
the ionization, excitation and elastic reactions rate constants were calculated
using the computational software BOLSIG+ [2], using cross sectional data from the 
LXcat project [3]. The rest of the reaction rate constants were obtained by the
literature [4,5]. 

### Platform
The computational code is writen in C programming language, and both the BOLSIG+ 
and the present code can be executed in Unix-based systems and Windows.

### Developers
The ChemPIG code was developed by the Computational Fluid Dynamics (CFD) laboratory, 
and the High-Voltage Laboratory

### References

1. Chun Ku Chen et al. “Modelling the discharge region of a microwave generated
    hydrogen plasma”. In: Journal of Physics D: Applied Physics 32.6 (1999),
    pp. 688–698. issn: 00223727. doi: [10.1088/0022-3727/32/6/015](https://iopscience.iop.org/article/10.1088/0022-3727/32/6/015) .
    
2. http://www.bolsig.laplace.univ-tlse.fr/

3. http://www.lxcat.laplace.univ-tlse.fr

4. A. T. Hjartarson, E. G. Thorsteinsson, and J. T. Gudmundsson. “Low pressure
    hydrogen discharges diluted with argon explored using a global model”. In: Plasma
    Sources Science and Technology 19.6 (2010). issn: 09630252. doi:
    [10.1088/0963-0252/19/6/065008](https://iopscience.iop.org/article/10.1088/0963-0252/19/6/065008) .
    
5. A. A. Matveyev and V. P. Silakov. “Kinetic processes in a highly-ionized
    non-equilibrium hydrogen plasma”. In: Plasma Sources Science and Technology 4.4
    (1995), pp. 606–617. issn: 09630252. doi: [10.1088/0963-0252/4/4/012](https://iopscience.iop.org/article/10.1088/0963-0252/4/4/012) .
