OBJS	= main.o functions.o JobScheduler.o Job.o Queue.o vertex.o list.o bucket.o hashTable.o negativeList.o vector.o BF.o
SOURCE	= main.cpp functions.cpp JobScheduler.cpp Job.cpp Queue.cpp vertex.cpp list.cpp bucket.cpp hashTable.cpp negativeList.cpp vector.cpp BF.cpp
HEADER	= functions.h JobScheduler.h Job.h Queue.h vertex.h list.h bucket.h hashTable.h negativeList.h vector.h BF.h
OUT	= project3
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	g++ functions.cpp hashTable.cpp list.cpp vertex.cpp Job.cpp Queue.cpp JobScheduler.cpp bucket.cpp negativeList.cpp BF.cpp tests.cpp -o tests -lpthread

functions.o: functions.cpp
	$(CC) $(FLAGS) functions.cpp -std=c++14

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14

JobScheduler.o: JobScheduler.cpp
	$(CC) $(FLAGS) JobScheduler.cpp -std=c++14

Job.o: Job.cpp
	$(CC) $(FLAGS) Job.cpp -std=c++14

Queue.o: Queue.cpp
	$(CC) $(FLAGS) Queue.cpp -std=c++14

vertex.o: vertex.cpp
	$(CC) $(FLAGS) vertex.cpp -std=c++14

list.o: list.cpp
	$(CC) $(FLAGS) list.cpp -std=c++14

bucket.o: bucket.cpp
	$(CC) $(FLAGS) bucket.cpp -std=c++14

hashTable.o: hashTable.cpp
	$(CC) $(FLAGS) hashTable.cpp -std=c++14

negativeList.o: negativeList.cpp
	$(CC) $(FLAGS) negativeList.cpp -std=c++14

vector.o: vector.cpp
	$(CC) $(FLAGS) vector.cpp -std=c++14

BF.o: BF.cpp
	$(CC) $(FLAGS) BF.cpp -std=c++14


clean:
	rm -f $(OBJS) $(OUT)
