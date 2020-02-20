//! -O1 -fno-if-conversion -fno-if-conversion2

extern int a;
extern int b;

int f() {
    if (a < b) {
        return 0;
    } else {
        return a;
    }
}
