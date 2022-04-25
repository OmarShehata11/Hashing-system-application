# Hash 
- my first system application with C 
- it prints the Hash of a string or a file with two algorithm
	- SHA256
	- MD5
- you can specifiy which one to use, but by default it prints the both
- run the app with no options or "-h" to print the help page

## how to run
```bash
cd  bin
make
./Hash
```

### NOTE
- if the compiler can't find the openssl library, download it on debian 
```bash
sudo apt-get install libssl-dev
```
- WINDOWS 
	- you can change it will compiling with gcc in the command line, by changing the make file with this option :
```bash
	gcc ../src/main.c -o Hash -lcrypto -I ../librariesNeeded/openssl
```
- see this [answer](https://stackoverflow.com/questions/2123699/where-does-my-c-compiler-look-to-resolve-my-includes) for more details

- or you can use the openssl library found in librariesNeeded directory.
