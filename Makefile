# input files
TEX=report.tex
PLOTSCRIPTS=plotscript1.gpl plotscript2.gpl plotscript3.gpl

# generated files
REPORT=report.pdf
REPORTExtra=report.aux report.log report.synctex.gz report.toc
RESULTS = out.dat $(wildcard *.dat) HE_kappa_1.000000_N_16_scheme_0.dat HE_kappa_0.100000_N_16_scheme_0.dat HE_kappa_1.000000_N_16_scheme_2.dat HE_kappa_0.100000_N_16_scheme_2.dat HE_kappa_1.000000_N_16_scheme_1.dat HE_kappa_0.100000_N_16_scheme_1.dat
PROGRAM=myProgram
OBJS=main.o sparse.o vector.o
PLOTS=HE_plot_FE.pdf HE_plot_Heun3.pdf HE_plot_BE.pdf

# additional variables
# CPPFLAGS=-std=c++11
CPPFLAGS=-std=c++11 -g

all: $(RESULTS)

$(REPORT): $(PLOTS) $(TEX)
		pdflatex -interaction=batchmode report.tex
		pdflatex -interaction=batchmode report.tex  # do latex twice

$(PLOTS): $(RESULTS) $(PLOTSCRIPTS)
	gnuplot plotscript1.gpl
	gnuplot plotscript2.gpl
	gnuplot plotscript3.gpl

$(RESULTS): $(PROGRAM)
	./$(PROGRAM) 16 1.0 0
	./$(PROGRAM) 16 0.1 0
	./$(PROGRAM) 16 1.0 1
	./$(PROGRAM) 16 0.1 1
	./$(PROGRAM) 16 1.0 2
	./$(PROGRAM) 16 0.1 2

#g++ -O1 -Wall -Wfatal-errors -pedantic $(CPPFLAGS) $(OBJS) -o $(PROGRAM)
$(PROGRAM): $(OBJS)
	g++ -Ofast -Wall -Wfatal-errors -pedantic $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

#g++ -O3 -Wall -Wfatal-errors -pedantic $(CPPFLAGS) -c $^ -o $@
$(OBJS): %.o: %.cc
	g++ -Ofast -Wall -Wfatal-errors $(CPPFLAGS) -c $^ -o  $@


clean:
	rm -rf $(PROGRAM) $(RESULTS) $(OBJS) $(PLOTS) $(REPORTExtra)
