#include <stdio.h>

int main () {
    int storage, bucket_size, input_packet_size, output_packet_size, size_left, no_of_queries;
    int i;

    storage = 0;
    bucket_size = 10;
    input_packet_size = 4;
    output_packet_size = 1;
    no_of_queries = 4;

    for(i=0;i<no_of_queries;i++) {
        size_left = bucket_size - storage;
        if(size_left >= input_packet_size) {
            storage = storage + input_packet_size;
            printf("Buffer size = %d out of bucket size %d\n", storage, bucket_size);
        }
        else {
            storage = bucket_size;
            printf("Packet Loss = %d\n", input_packet_size-size_left);
            printf("Buffer size = %d out of bucket size %d\n", storage, bucket_size);
        }
        storage = storage - output_packet_size;
    }
}