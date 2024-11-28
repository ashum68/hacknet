########## Variables ##########

CXX = clang++					# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD	-I/opt/X11/include	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = window.cc \
          ability.cc firewall.cc linkboost.cc download.cc polarize.cc scan.cc \
          roadworkahead.cc roulette.cc \
          link.cc cell.cc board.cc \
          player.cc subject.cc observer.cc textobserver.cc graphicsobserver.cc \
          game.cc main.cc


OBJECTS = ${SOURCES:.cc=.o}			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = raiinet					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@ -L/opt/X11/lib -lX11		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
