# producer-consumer
KSU CS33211 Operating systems

Fixing the producer consumer problem with the use of semaphores where we put the produced item into a container to be used by the consumer we use semaphores and mutual exclusion to prevent race condition. 

the producer.c and consumer.c files are under master branch

gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
