all: defi response

defi: defi3.c
	gcc -g -no-pie -o defi defi3.c
	objdump -R defi

response: response.py
	python2.7 response.py
