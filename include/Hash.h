void usage();
char* return_hash(unsigned char *buf, size_t siz);
size_t get_size(int fd);


// WHERE THE CHARACTER BYTES OF HASH STORED 
unsigned char SHA256_hash[SHA256_DIGEST_LENGTH];
unsigned char MD5_hash[MD5_DIGEST_LENGTH];
unsigned char SHA256_hash_file[SHA256_DIGEST_LENGTH];
unsigned char MD5_hash_file[MD5_DIGEST_LENGTH];

