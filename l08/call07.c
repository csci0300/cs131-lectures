//! -O0
// Now with frame pointers!

extern long a[];

void f(long arg1, long arg2) {
    a[0] = arg1;
    a[1] = arg2;
}
