int add(int a, int b) {
    return a + b;
}

unsigned add(unsigned a, unsigned b) {
    return a + b;
}

char* add(char* a, unsigned b) {
    return &a[b];
}

const unsigned char add[] = { 0x8d, 0x04, 0x37, 0xc3 };
