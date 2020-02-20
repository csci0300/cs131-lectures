extern void f(long arg1, long arg2, long arg3, long arg4,
              long arg5, long arg6);

int a[10];

int main() {
  int i = 99;
  f(1, 100, 123, 45, 42, i);
}
