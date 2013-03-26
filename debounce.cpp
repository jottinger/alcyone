#include "debounce.h"

Debouncer::Debouncer() {
    index=0;
    for(int j=0; j<BUFFERSIZE; j++) {
        buffer[j]=0;
    }
}

int Debouncer::debounce(int input) {
    static int values[2];

    index=((index+1) % BUFFERSIZE);
    buffer[index]=input;

    values[0]=0;
    values[1]=0;
    // now count the buffer entries
    for(int j=0; j<BUFFERSIZE-1; j++) {
        values[buffer[j]!=0?1:0]++;
    }

    return(values[0]>values[1]?0:1);
}
