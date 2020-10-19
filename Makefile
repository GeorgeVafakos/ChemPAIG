# Makefile

CC = gcc
GFLAGS = -lm

SOURCES_MAIN = main.c
# SOURCES = $(SOURCES_MODULES) $(SOURCES_SUBPROGRAMS) $(SOURCES_MAIN)
SOURCES = $(SOURCES_MAIN)
EXECUTABLE = solve

PROGRESS = \033[1;91mProgress:\033[0m

PERCENT = 0.01

execname: $(SOURCES)
	@echo "\033[1mStart compiling"
	@echo -ne '$(PROGRESS) \033[1m  ..........                                                                                              \033[91m[10%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  ...............                                                                                         \033[91m[10%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  ....................                                                                                    \033[91m[20%]\033[0m\r'
	@sleep $(PERCENT)
		
	@echo -ne '$(PROGRESS) \033[1m  .........................                                                                               \033[91m[20%]\033[0m\r'
	@sleep $(PERCENT)
		
	@echo -ne '$(PROGRESS) \033[1m  ..............................                                                                          \033[91m[30%]\033[0m\r'
	@sleep $(PERCENT)
		
	@echo -ne '$(PROGRESS) \033[1m  ...................................                                                                     \033[91m[30%]\033[0m\r'
	@sleep $(PERCENT)
		
	@echo -ne '$(PROGRESS) \033[1m  ........................................                                                                \033[91m[40%]\033[0m\r'
	@sleep $(PERCENT)
		
	@echo -ne '$(PROGRESS) \033[1m  .............................................                                                           \033[91m[40%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  ..................................................                                                      \033[91m[50%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  .......................................................                                                 \033[91m[50%]\033[0m\r'
	@sleep $(PERCENT)
		@ @$(CC) $(SOURCES_MAIN) $(GFLAGS) -o $(EXECUTABLE)
	@echo -ne '$(PROGRESS) \033[1m  ............................................................                                            \033[91m[60%]\033[0m\r'
	@sleep $(PERCENT)
	
	@echo -ne '$(PROGRESS) \033[1m  .................................................................                                       \033[91m[60%]\033[0m\r'
	@sleep $(PERCENT)
	
	@echo -ne '$(PROGRESS) \033[1m  ......................................................................                                  \033[91m[70%]\033[0m\r'
	@sleep $(PERCENT)
	
	@echo -ne '$(PROGRESS) \033[1m  ...........................................................................                             \033[91m[70%]\033[0m\r'
	@sleep $(PERCENT)
	@echo -ne '$(PROGRESS) \033[1m  ................................................................................                        \033[91m[80%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  .....................................................................................                   \033[91m[80%]\033[0m\r'
	@sleep $(PERCENT)
	@echo -ne '$(PROGRESS) \033[1m  ..........................................................................................              \033[91m[90%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  ...............................................................................................         \033[91m[90%]\033[0m\r'
	@sleep $(PERCENT)

	@echo -ne '$(PROGRESS) \033[1m  ....................................................................................................    \033[91m[100%]\033[0m\r'
	@echo -ne '\n'
	@echo "\033[1mExecutable created"
	@echo "Compilation was successful!"

clean:
	rm -rf *.o *.mod $(EXECUTABLE)
	rm -rf Make
	@echo "\033[1mFiles removed!"

