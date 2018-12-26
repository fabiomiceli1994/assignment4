################################################################################

                        C1 - ASSIGNMENT 4 - ID 1894945

################################################################################

To execute the program type "make" into the terminal (" " are not required) and
hit enter. The program is run through a Makefile, provided in .zip folder, so
that no other commands are needed.
For clarity reasons, every integration correctly performed by the program is
printed on the terminal runtime along with the time up to which such an
integration is made: the user can thus have a firmer grip on the
operations that are being performed.
The program has been designed in such a way that other possible tests can be
simply executed by means of a simple change of parameters in the  Makefile: a
suitable check of consistency for the given set of parameters has been inserted
as well and in case a wrong insertion happens, a suitable usage-message is
printed on the terminal for the user.
Every time the program is run, the arguments have to be inserted in following
order after the "./MyProgram" instruction:
"Nx" "kappa" "scheme"
In particular:
- to test with FE insert 0;
- to test with BE insert 1;
- to test with Heun3 insert 2.
Plotscripts needed by gnuplot to produce plots are provided and the final .tex
document is generated automatically by the Makefile.
