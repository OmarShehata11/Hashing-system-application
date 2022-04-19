#include "Hash.c"

int main(int argc, char *argv[])
{

	int fd, chck, fflag=0, Sflag=1, Mflag=1, opt;
	size_t SizeOfFile, SizeOfString;
	char *FileData, *FileName; // FileData FOR MMAP RETURNED VALUE


	if (argc == 1)
		usage();

	opterr = 0;

	while ( (opt =getopt(argc, argv, ":f:SMh")) != -1 )
	{
		switch (opt)
		{

			case 'h':
				usage();
				break;

			case 'f' : // TO ACCEPT A FILE
				fflag = 1;
				FileName = optarg;
				break;

			case 'S' : // TO CHOOSE ONLY SHA265
				(Sflag == 0) ? Sflag=Mflag : (Mflag = 0); 
				// I PUT THIS SO IF THE USER ENTERED -SM , IT WILL PRINT BOTH.
				break;


			case 'M' : // TO CHOOSE ONLY MD5
				(!Mflag) ? Mflag = Sflag : (Sflag = 0);
				break;


			case '?' : 
				fprintf(stderr, "unknown argument : -%c\n\n", optopt);
	
		}
	}


	if(fflag)
	{

		if((fd = open(FileName, O_RDONLY)) == -1 )
		{
			perror("[-]ERROR ");
			exit(1);
		}

		SizeOfFile = get_size(fd);

		// MAPPING THE FILE INTO MEMORY
		if ((FileData = mmap(NULL, SizeOfFile, PROT_READ, MAP_PRIVATE, fd, 0)) == NULL)
		{
			perror("[-]ERROR WHILE MAPPING ");
			exit(1);
		}
		
		if(Sflag)
		{
			//GET THE CHARACTER BYTES FROM FUNCTION, THEN PASS IT 
			//TO A FUNCTION TO RETURN THE HEX VALUE, THEN PRINT IT
			//AS ASCII

			SHA256((unsigned char*)FileData, SizeOfFile, SHA256_hash_file);
		    char *SHA256_hash_file_final = return_hash(SHA256_hash_file, sizeof(SHA256_hash_file));
			printf("SHA256 for file: %s\n", SHA256_hash_file_final);
		}

		if(Mflag)
		{
			MD5((unsigned char*)FileData, SizeOfFile, MD5_hash_file);
		    char *MD5_hash_file_final = return_hash(MD5_hash_file, sizeof(MD5_hash_file));
			printf("MD5 for file: %s\n", MD5_hash_file_final);
		}

		// UNMAPING AND RELEASE THE HANDLE FOR THE FILE		
		if ((chck = munmap(FileData, SizeOfFile)) == -1)
		{
			perror("[-]ERROR WHILE UNMAPPING ");
			exit(1);
		}
		
		if ((chck = close(fd)) == -1)
		{
			perror("[-]ERROR WHILE CLOSING ");
			exit(1);
		}
	
		printf("\n"); // TO SEPERATE BETWEEN DIFFERENTE FILES.
	
	}
	
	// TO CHECK FOR NON-OPTIONAL ARGUMENTS "ONLY STRING
	// TO HASH NOT FILES".

	for (int i = optind; i < argc; i++)
	{
		SizeOfString = strlen(argv[i]);

		if (Sflag)
		{
			SHA256(argv[i], SizeOfString, SHA256_hash);
			char *SHA256_hash_final = return_hash(SHA256_hash, sizeof(SHA256_hash));
			printf("SHA256 for '%s': %s\n", argv[i], SHA256_hash_final);
		}
		
		if(Mflag)
		{
			MD5(argv[i], SizeOfString, MD5_hash);
			char *MD5_hash_final = return_hash(MD5_hash, sizeof(MD5_hash));
			printf("MD5 for  '%s'  : %s\n", argv[i], MD5_hash_final);
		}
		
		printf("\n"); // TO SEPERATE BETWEEN DIFFERENTE STRINGS.	
	}

	exit(0);
}