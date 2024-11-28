########## Variables ##########

CXX = clang++					# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = $(wildcard *.cc)			# source files (*.cc)
OBJECTS = cell.o player.o ability.o board.o game.o link.o subject.o textobserver.o \
          download.o linkboost.o firewall.o scan.o polarize.o roadworkahead.o bomb.o roulette.o main.o			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = raiinet					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
