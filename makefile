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
PROG1 = list
PROG2 = new
PROG3 = newdir
PROG4 = rmall
PROG5 = size
PROG6 = fonction.c

SCRS = tsh.c util.c 
SCRS1 = list.c
SCRS2 = new.c
SCRS3 = newdir.c
SCRS4 = rmall.c
SCRS5 = size.c
SCRS6 = fonction.c
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
	$(CC) $(CFLAGS) $(SCRS6) $(SCRS1) -o $(PROG1)
		mv $(PROG1) $(prefix)
	$(CC) $(CFLAGS) $(SCRS6) $(SCRS2) -o $(PROG2)
		mv $(PROG2) $(prefix)
	$(CC) $(CFLAGS) $(SCRS6) $(SCRS3) -o $(PROG3)
		mv $(PROG3) $(prefix)
	$(CC) $(CFLAGS) $(SCRS6) $(SCRS4) -o $(PROG4)
		mv $(PROG4) $(prefix)
	$(CC) $(CFLAGS) $(SCRS6) $(SCRS5) -o $(PROG5)
		mv $(PROG5) $(prefix)
#---------------------------------
	
# Pour les dependannces maintenant 
# Pour obtenir l executable dup.o on inclut (dup.c et les include 
# qui se trouvent dans le fichier dup.c a savoir affichage.h,fonction.h)
tsh.o:  tsh.c util.h 
util.o: util.c util.h
#--------------------------------
#----------------------------------------
clean:
	/bin/rm  -f core *~ $(OBJS)	
