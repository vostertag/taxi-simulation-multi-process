# Taxi Simulation using multiple processes

This is a Linux C program that simulates a taxi call terminal. One process reads what are the upcoming calls and send them through a message queue to the other processes which are acting as taxis, taking each call when they are available.

## Index

## How to use

Go to the "src" folder with a terminal and execute the make command:

```
make
```

To run the code, use this command, with N being the number of taxis you would like to have (I advise using 2 to 4):

```
.\launcher N
```

## What does it do

Once you ran the code with N taxis, N+1 new terminal will open, one for each process. The process **readData** will read the file where the demands are stored, display them and send them to the other processes in real time. The other processes are simulating taxis that will take each new call if they are available (e.g. if they are not currently driving a client somewhere).  

Here is an example of what it will look like:
![Alt Text](https://image.ibb.co/byGVM6/taxis.jpg)

On the left is the readData process, sending and displaying the demands. The other processes are the taxis.

## Create new demands

The demands are read in the "src/data/demandes.dat" file:

![Alt Text](https://image.ibb.co/heVEzG/demandes.jpg)

Each demand must be written like this:  
Number of seconds until next client  
Client Name ;Number of seconds it will take to take this call
