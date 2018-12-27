# input files
TEX=u1894945-assignment4.tex
PLOTSCRIPTS=plotscriptFE.gpl plotscriptFE_2.gpl plotscriptBE.gpl plotscriptBE_2.gpl plotscriptHeun3.gpl plotscriptHeun3_2.gpl

# generated files
REPORT=u1894945-assignment4.pdf
REPORTExtra=u1894945-assignment4.aux u1894945-assignment4.log u1894945-assignment4.synctex.gz u1894945-assignment4.toc
RESULTStrash=$(wildcard *.dat)
RESULTS=HE_k_%_N_%_tau_%_scheme_%_t_%.dat
PROGRAM=myProgram
OBJS=main.o sparse.o vector.o
PLOTS=HE_plot_N_%_tau_%_k_%_%.pdf

# additional variables
CPPFLAGS=-std=c++11

all: $(REPORT)

$(REPORT): $(PLOTS) $(TEX)
		pdflatex -interaction=batchmode u1894945-assignment4.tex
		pdflatex -interaction=batchmode u1894945-assignment4.tex  # do latex twice

$(PLOTS): $(RESULTS) $(PLOTSCRIPTS)
	gnuplot plotscriptFE.gpl
	gnuplot plotscriptFE_2.gpl
	gnuplot plotscriptBE.gpl
	gnuplot plotscriptBE_2.gpl
	gnuplot plotscriptHeun3.gpl
	gnuplot plotscriptHeun3_2.gpl

$(RESULTS): $(PROGRAM)
	./$(PROGRAM) 20 1.0 0 0.001
	./$(PROGRAM) 16 0.1 0 0.001
	./$(PROGRAM) 20 1.0 1 0.001
	./$(PROGRAM) 16 0.1 1 0.001
	./$(PROGRAM) 20 1.0 2 0.001
	./$(PROGRAM) 16 0.1 2 0.001

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -Ofast -Wall -Wfatal-errors $(CPPFLAGS) -c $^ -o  $@


clean:
	rm -rf $(PROGRAM) $(RESULTStrash) $(OBJS) $(filter-out u1894945-assignment4.pdf, $(wildcard *.pdf)) $(PLOTS) $(REPORTExtra)
