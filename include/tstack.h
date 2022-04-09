// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
T a[500];
int head;
 public:
TStack(): head(-1) { }
T get() const {
return a[head];
}
bool Empty() const {
return head == -1;
}
bool Full() const {
return head == (size-1);
}
void del() {
if(!Empty())
head--;
}
void push(T value) {
if(!(Full()))
a[++head] = value;
}
};
#endif  // INCLUDE_TSTACK_H_
