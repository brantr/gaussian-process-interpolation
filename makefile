
EXEC   = gp

#CC       =  icc
#CPP      =  icpc -E 
CC       =  gcc
OPTIMIZE =  -O2 -Wall -g        # sets optimization and warning flags


OPTIONS =  $(OPTIMIZE) $(OPT)  
#OPTIONS =  $(OPTIMIZE) $(OPT)  -DMKL_ILP64 -m64 -I${MKLROOT}/include

INTEL_LIBS = ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_sequential.a ${MKLROOT}/lib/libmkl_core.a -lpthread -lm -ldl

OBJS   = main.o gaussian_process.o

INCL   = gaussian_process.h

CFLAGS = $(OPTIONS) $(GSL_INCL) $(FFTW_INCL) $(MPI_INCL) $(CFITSIO_INCL) $(LAPACK_INCL)

LIBS   =  $(MPI_LIBS) $(GSL_LIBS) $(FFTW_LIBS) $(CFITSIO_LIBS) $(LAPACK_LIBS) $(INTEL_LIBS)

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS)   -o  $(EXEC)  

$(OBJS): $(INCL) 


clean:
	rm -f $(OBJS) $(EXEC)
