#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "../include/Hash.h"


void usage()
{
	printf("USAGE : Hash string [OPTION..]\nOPTIONS:\n\t-f FILE:\tprint the hash of the FILE.\n\t-S:\tprint only SHA256.\n\t-M:\tprint only MD5.\n\t-h:\tprint the help page.\n\nAUTHORED BY : OMAR SHEHATA\n");
	exit(0);
}


//////////////**********///////////////////////
// TO GET THE SIZE FROM A FILE DESCRIPTOR
size_t get_size(int fd) 
{
	struct stat *st;
	int chck;

	if(chck = fstat(fd, st) == -1)
	{
		perror("[-]ERROR IN STAT ");
		exit(1);
	}
	return st->st_size;
}


//////////////**********///////////////////////
// TURN THE UNSIGNED BYTES OF CHARACTERS INTO HEX
char* return_hash(unsigned char *buf, size_t siz)
{
	static char hash[200]; //NOTE THAT BECAUSE IT WILL BE RETURNED, IT HAS TO BE STATIC.
	for (int i = 0; i < siz; i++)
		// EACH BYTE OF CHAR IS REPERSENTED IN TWO VALUES OF 
		// HEX (THAT'S WHY WE DO : hash+i*2)
		sprintf(hash+i*2, "%02x", buf[i]);
	return hash;
}
