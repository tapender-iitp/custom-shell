LDFLAG = ./mydir/
targets = install

install-CS34: 
	gcc -Wall CS34.c -o CS34
	$(CC) -Wall $(LDFLAG)pwd.c -o $(LDFLAG)pwd

$(targets): install-CS34

test : install-CS34
	./CS34 test.bat
doc :
	pdflatex doc.tex
clean :
	rm -f doc.pdf
	rm -f CS34
	rm -f $(LDFLAG)pwd
	rm -f doc.log
	rm -f doc.aux
	rm -f file.txt
	
