#Stephen Stengel <stephen.stengel@cwu.edu> 40819903
#Makefile

#Makes the executable
calc: calc.o
	gcc -Wall -o calc calc.o

#Makes object file
calc.o: calc.c calc.h
	gcc -Wall -c calc.c


#Miscellaneous

#Cleans folder
.PHONY: clean
clean:
	rm -f *.o calc

#Runs my remote backup script
.PHONY: backup
backup:
	ssh-backup-pi | lolcat

#Makes a zip of the project files.
.PHONY: zip
zip:
	7z a source_stengel_stephen.zip calc calc.h calc.c Makefile HowTo.txt
