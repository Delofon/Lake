#ifndef PANIC_H_
#define PANIC_H_

// TODO: Move to some CPU architecture agnostic header file?
void savereg();
void printreg();

void panic(const char *msg);

#endif

