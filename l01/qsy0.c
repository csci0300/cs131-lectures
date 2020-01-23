static void iswap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void qs(int* array, int n) {
    int pivot = array[n / 2];
    int left = 0, right = n;
    while (left < right) {
        if (array[left] <= pivot) {
            ++left;
        } else if (array[right - 1] > pivot) {
            --right;
        } else {
            iswap(&array[left], &array[right - 1]);
        }
    }
    qs(&array[0], left);
    qs(&array[left], n - left);
}
