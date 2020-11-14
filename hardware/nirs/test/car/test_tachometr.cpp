#include <modules/CIrcularBuffer/CircularBuffer.h>
#include <cstdio>

int main() {
    CircularBuffer<int, 5> buffer;
    buffer.put(1);
    buffer.put(2);
    buffer.put(3);
    buffer.put(4);
    buffer.put(5);
    buffer.put(6);
    for(auto i = buffer.begin(); i != buffer.end(); ++i) {
        printf("%d\n", *i);
    }
}