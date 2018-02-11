# Compiler to be used.
CC = gcc

# Compile time flags to be used.
CFLAGS += -Wall  # For enabling warnings
CFLAGS += -g     # For enabling debugging
CFLAGS += -O0    # For disabling optimization.
                 # If -O1/-O2/... is used, it enables that level of optimization

# Dependencies on header files.
DEPS = utilities.h

# Path of directories containing header files in addition to /usr/include.
# -I flag is used to add user defined header file paths.
INCLUDES = -I/
# INCLUDES += -I/<path of directory> to add more directories in future.

# Library paths in addition to /usr/lib.
# -L flag is used to add user defined library paths.
LFLAGS = -L/
#LFLAGS += -L/<path of directory> to add more directories in future.

# Define any libraries to link into executable.
# -lNAME looks for libNAME.a
# Here -lmylib will try to look for libmylib.a in standard library directory and
# directory specified by -L flag above.
# LIBS = -lmylib -lm

# Define source files. Add new source files here
SRCS = linked_list.c \
	   main.c

# Define object files. It uses suffix replacement MACRO.
# No need to change this with addition of new files.
OBJS = $(SRCS:.c=.o)

# Name of the final executable.
TARGET = my_program.run

# ***** 
#       The following part is generic and it will build and link
#       everything that has been defined in above variables.
# *****

# default rule that gets executed with "make" command
default: linked_list

# linked_list rule to compile linked_list specific files.
# my_program.run executable will be created.
# We are giving only object files in the compile command below because
# there is a default rule in Makefile to get object file from
# corresponding c file. So Makefile first builds source files corresponding
# to object files given below. Then it will execute the below command.
linked_list: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)

# clean rule to delete the object files and executibles.
clean:
	$(RM) *.o *.run
