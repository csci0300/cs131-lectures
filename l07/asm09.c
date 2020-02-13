//! -O1

extern unsigned long long a;
extern int b;

int sum() {
    return (a & 0xFFFFFFFF) + b;
}
