#include <stdio.h>

int main(int argc, char *argv[]){
	return !printf((argc > 1)? argv[1]: "hello world\n");
}