//! -O1 -fomit-frame-pointer
// Let's figure out the calling conventions on this compiler!

extern int a[];

void f(long arg1, long arg2, long arg3, long arg4,
       long arg5, long arg6) {
    a[0] = arg1;
    a[1] = arg2;
    a[2] = arg3;
    a[3] = arg4;
    a[4] = arg5;
    a[5] = arg6;
}
