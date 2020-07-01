#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<omp.h>
#include<stdint.h>
#include<atomic>

using namespace std;

void ParseArg(int argc, char ** argv, int& nIter, int& nThreads) {
	extern char *optarg;
	extern int optind;
	nIter = -1;
	nThreads = -1;
	char c;

	static char usage[] = "usage: %s -n numberOfThreads -i numIters\n";
	while ((c = getopt(argc, argv, "n:i:")) != -1) {
	  int index = -1;
	  int i;
		switch (c) {
		case 'n':
			nThreads = atol(optarg);
			break;
		case 'i':
			nIter = atol(optarg);
			break;
		case 'h':
		default:
			fprintf(stderr, usage, argv[0]);
			exit(-1);
			break;
		}
	}
/*
nIter = -1;
	nGroups = -1;
	nThreads = -1;
*/
	if (nIter < 0 || nThreads == -1) {
        	fprintf(stderr, usage, argv[0]);
        	exit(-1);
	} 
}
