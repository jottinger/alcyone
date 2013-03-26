#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__ 1

#define BUFFERSIZE 13

class Debouncer {
private:
    int buffer[BUFFERSIZE];
    int index;
protected:
public:
    Debouncer();

    int debounce(int input);
};

#endif