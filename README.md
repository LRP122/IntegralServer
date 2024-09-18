# Integral Server

This is a programm to calculate different integrals, making the request from a client and the calculations on a server.

To use this, navigate to integral_cpp/TCP and create the executabale files using 

```bash
make all
```

You can then create a localhost server choosing a portnumber (e.g 8080) and using

```bash
./server [port number]
```

Connect to this via 
```bash
./client [port number]
```
You will then see the instructions for choosing a integral, lower and upper bound and will receive the solution. You can add more functions in the integral_cpp/src/functions.h file.


