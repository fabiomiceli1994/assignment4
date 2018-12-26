# input files
TEX=u1894945-assignment4.tex
PLOTSCRIPTS=plotscriptEvolveFE.gpl plotscriptEvolveFE2.gpl plotscriptEvolveBE.gpl plotscriptEvolveBE2.gpl plotscriptEvolveHeun3.gpl plotscriptEvolveHeun32.gpl

# generated files
REPORT=u1894945-assignment4.pdf
REPORTExtra=u1894945-assignment4.aux u1894945-assignment4.log u1894945-assignment4.synctex.gz u1894945-assignment4.toc
RESULTStrash=$(wildcard *.dat)
RESULTS=HE_kappa_%_N_%_scheme_%_time_%.dat
PROGRAM=myProgram
OBJS=main.o sparse.o vector.o
PLOTS=HE_plot_N_%_kappa_evolve_%.pdf

# additional variables
CPPFLAGS=-std=c++11

all: $(PLOTS)
#
# $(REPORT): $(PLOTS) $(TEX)
# 		pdflatex -interaction=batchmode report.tex
# 		pdflatex -interaction=batchmode report.tex  # do latex twice
# #
$(PLOTS): $(RESULTS) $(PLOTSCRIPTS)
	gnuplot plotscriptEvolveFE.gpl
	gnuplot plotscriptEvolveFE2.gpl
	gnuplot plotscriptEvolveBE.gpl
	gnuplot plotscriptEvolveBE2.gpl
	gnuplot plotscriptEvolveHeun3.gpl
	gnuplot plotscriptEvolveHeun32.gpl

$(RESULTS): $(PROGRAM)
	./$(PROGRAM) 50 1.0 0
	./$(PROGRAM) 100 0.01 0
	./$(PROGRAM) 16 1.0 1
	./$(PROGRAM) 20 0.1 1
	./$(PROGRAM) 16 1.0 2
	./$(PROGRAM) 100 0.01 2

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -Ofast -Wall -Wfatal-errors $(CPPFLAGS) -c $^ -o  $@


clean:
	rm -rf $(PROGRAM) $(RESULTStrash) $(OBJS) $(filter-out u1894945-assignment4.pdf, $(wildcard *.pdf)) $(PLOTS) $(REPORTExtra)
