# input files
# TEX=report.tex
# PLOTSCRIPTS=plotscript1.gpl plotscript2.gpl plotscriptErrorTime.gpl plotscriptErrorTime2.gpl plotscriptErrorTime3.gpl plotscriptErrorTime4.gpl

# generated files
# REPORT=report.pdf
RESULTS = out.dat
PROGRAM=myProgram
OBJS=main.o sparse.o vector.o
# PLOTS=Errors_Model_2_tau_0.100000_J_12_plot.pdf Errors_Model_3_tau_0.100000_J_12_plot.pdf Error_Evolution_Model_2_plots.pdf Error_Evolution_Model_3_plots.pdf Error_Evolution_Model_2_plots_2.pdf Error_Evolution_Model_3_plots_2.pdf

# additional variables
CPPFLAGS=-std=c++11

all: $(RESULTS)

# $(REPORT): $(PLOTS) $(TEX)
# 		pdflatex -interaction=batchmode report.tex
# 		pdflatex -interaction=batchmode report.tex  # do latex twice
#
# $(PLOTS): $(RESULTS1) $(RESULTS2) $(ERROREVOLUTION) $(PLOTSCRIPTS)
# 	gnuplot plotscript1.gpl
# 	gnuplot plotscript2.gpl
# 	gnuplot plotscriptErrorTime.gpl
# 	gnuplot plotscriptErrorTime2.gpl
# 	gnuplot plotscriptErrorTime3.gpl
# 	gnuplot plotscriptErrorTime4.gpl

$(RESULTS): $(PROGRAM)
	./$(PROGRAM) 16 1.0

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -Ofast -Wall -Wfatal-errors $(CPPFLAGS) -c $^ -o  $@


clean:
	rm -rf $(PROGRAM) $(RESULTS) $(OBJS)
