#--------------------------
#Declaration des variables
prefix =~/Bureau/BORJ15048201/inf3172/bin
CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm
#-------------------------

#------COMMENT ON OBTIENT L EXECUTABLE-------------------
#PROG = tsh est le nom qu'on a choisi pour l executable
PROG = tsh 
PROG1 = cd
PROG2 = cdir
PROG3 = list
PROG4 = new
PROG5 = newdir
PROG6 = rmall
PROG7 = size
PROG8 = exit
PROG9 = fonction.c

SCRS = tsh.c util.c 
SCRS1 = cd.c
SCRS2 = cdir.c
SCRS3 = list.c
SCRS4 = new.c
SCRS5 = newdir.c
SCRS6 = rmall.c
SCRS7 = size.c
SCRS8 = exit.c
SCRS9 = fonction.c
#--------------------------

#On obtient les .objets necessaires pour les liens par la conversion des .c des sources (SCRS)
#---------------------------
OBJS =  $(SCRS:.c=.o)
#--------------------------

#----------------------------
#compilation 
$(PROG) : $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)
		mv $(PROG) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS1) -o $(PROG1)
		mv $(PROG1) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS2) -o $(PROG2)
		mv $(PROG2) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS3) -o $(PROG3)
		mv $(PROG3) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS4) -o $(PROG4)
		mv $(PROG4) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS5) -o $(PROG5)
		mv $(PROG5) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS6) -o $(PROG6)
		mv $(PROG6) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS7) -o $(PROG7)
		mv $(PROG7) $(prefix)
	$(CC) $(CFLAGS) $(SCRS9) $(SCRS8) -o $(PROG8)
		mv $(PROG8) $(prefix)	
#----------------------------------
	
# Pour les dependannces maintenant 
# Pour obtenir l executable dup.o on inclut (dup.c et les include 
# qui se trouvent dans le fichier dup.c a savoir affichage.h,fonction.h)
tsh.o:  tsh.c util.h 
util.o: util.c util.h
#--------------------------------
#----------------------------------------
clean:
	/bin/rm  -f core *~ $(OBJS)	
