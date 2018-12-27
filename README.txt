################################################################################

                        C1 - ASSIGNMENT 4 - ID 1894945

################################################################################

To execute the program type "make" into the terminal (" " are not required) and
hit enter. The program is run through a Makefile, provided in .zip folder, so
that no other commands are needed.
For clarity reasons, the conclusion of every integration performed by the program
is printed on the terminal runtime: the user can thus have a firmer grip on the
operations that are being performed. Specifically, the time required by each
integration performed, computed in terms of calls to specific functions contained
in  models.hh, is printed after each integration is performed. A suitable message
is printed in case the method used is not stable for that particular choice of
parameters.
The program has been designed in such a way that other possible tests can be
simply executed by means of a simple change of parameters in the  Makefile: a
suitable check of consistency for the given set of parameters has been inserted
as well and in case a wrong insertion happens, a suitable usage-message is
printed on the terminal for the user.
Every time the program is run, the arguments have to be inserted in following
order after the "./MyProgram" instruction:
"Nx" "kappa" "scheme" "tau"
In particular:
- to test with FE insert 0;
- to test with BE insert 1;
- to test with Heun3 insert 2.
Plotscripts needed by gnuplot to produce plots are provided and the final .tex
document is generated automatically by the Makefile. Plots are produced also in
the case of a blow-up of the solution to the given equation: it has been chosen
to plot a constant line of height 0.9 in this case. Finally, in the plots,
the legend t_0 refers to a sampling of the solution at time tau, tau being the
temporal stepsize, whereas t_i, i in {1, 2, 3, 4, 5} refers to the sampling of
teh solution ot times iT/5, T being the total integration time.
