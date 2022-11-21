multi:
	gcc main.cpp -lstdc++ -o multiThread -fopenmp
run_single:
	gcc main.cpp -lstdc++ -o single
	#gnome-terminal -- htop
	DATA_SIZE=91500 time -p ./single
run_multi:
	gcc main.cpp -lstdc++ -o multiThread -fopenmp 
	MAX_THREADS=4 DATA_SIZE=91500 time -p ./multiThread
test_multi:
	gcc main.cpp -lstdc++ -o multiThread -fopenmp 
	#gnome-terminal -- htop
	MAX_THREADS=4 DATA_SIZE=91500 time -p ./multiThread


