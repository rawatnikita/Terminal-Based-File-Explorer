all: fileExplorer
fileExplorer: main.o rawmode.o directory.o commandMode.o navigate.o 
			  g++ main.o rawmode.o directory.o  commandMode.o navigate.o -o fileExplorer
main.o: main.cpp
		g++ -c main.cpp
rawmode.o: rawmode.cpp
		   g++ -c rawmode.cpp
directory.o: directory.cpp
		     g++ -c directory.cpp
commandMode.o: commandMode.cpp
				g++ -c commandMode.cpp
navigate.o: navigate.cpp
		     g++ -c navigate.cpp
clean: rm -rf *o fileExplorer