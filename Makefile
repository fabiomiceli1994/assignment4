# input files
TEX=report.tex
PLOTSCRIPTS=plotscript1.gpl

# generated files
REPORT=report.pdf
REPORTExtra=report.aux report.log report.synctex.gz report.toc
RESULTS = out.dat $(wildcard *.dat) HE_kappa_1.000000_N_16_scheme_0.dat HE_kappa_0.001000_N_16_scheme_0.dat HE_kappa_1.000000_N_16_scheme_2.dat HE_kappa_0.001000_N_16_scheme_2.dat
PROGRAM=myProgram
OBJS=main.o sparse.o vector.o
PLOTS=HE_plot_FE.pdf HE_plot_Heun3.pdf

# additional variables
CPPFLAGS=-std=c++11

all: $(REPORT)

$(REPORT): $(PLOTS) $(TEX)
		pdflatex -interaction=batchmode report.tex
		pdflatex -interaction=batchmode report.tex  # do latex twice

$(PLOTS): $(RESULTS) $(PLOTSCRIPTS)
	gnuplot plotscript1.gpl
	gnuplot plotscript3.gpl

$(RESULTS): $(PROGRAM)
	./$(PROGRAM) 16 1.0 0
	./$(PROGRAM) 16 0.001 0
	# ./$(PROGRAM) 16 1.0 1
	# ./$(PROGRAM) 16 0.001 1
	./$(PROGRAM) 16 1.0 2
	./$(PROGRAM) 16 0.001 2

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -Ofast -Wall -Wfatal-errors $(CPPFLAGS) -c $^ -o  $@


clean:
	rm -rf $(PROGRAM) $(RESULTS) $(OBJS) $(PLOTS) $(REPORTExtra)
