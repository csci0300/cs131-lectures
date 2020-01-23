import java.util.*;

// Java implementation of QuickSort
class QuickSort
{
	static LinkedList<Integer> sort(LinkedList<Integer> list)
	{
    // If the list is empty, we're done
    if (list.isEmpty()) {
      return new LinkedList<Integer>();
    }

    Integer pivot = list.getFirst(); // first element as pivot

    LinkedList<Integer> left = new LinkedList<Integer>();
    LinkedList<Integer> right = new LinkedList<Integer>();

    ListIterator<Integer> it = list.listIterator(1);

    // copy elements into left and right lists, depending
    // whether they are less than or greater/equal to pivot
    while (it.hasNext()) {
      Integer element = it.next();
      if (element < pivot) {
        left.add(element);
      } else if (element >= pivot) {
        right.add(element);
      }
    }

    // recursively call quicksort on the two lists
    LinkedList<Integer> sorted_left = QuickSort.sort(left);
    LinkedList<Integer> sorted_right = QuickSort.sort(right);

    // add pivot, merge the two lists and return the result
    sorted_right.addFirst(pivot);
    sorted_left.addAll(sorted_right);
    return sorted_left;
	}

	// A utility function to print start of list
	static void printList(LinkedList list)
	{
		int n = list.size();
    System.out.print("[");
    if (n == 0) {
      System.out.print("]");
    }
		for (int i = 0; i < n; ++i) {
			System.out.print(list.get(i));
      if (i < n-1) {
        System.out.print(", ");
      } else {
        System.out.print("]");
        break;
      }
      if (i >= 20) {
        System.out.print("... ]");
        break;
      }
    }
		System.out.println();
	}

	// Driver program
	public static void main(String args[])
	{
		LinkedList<Integer> list = new LinkedList<Integer>();

    if (args.length < 1) {
      System.out.println("usage: QuickSort N -- sorts N integers");
      return;
    }

		int n = Integer.parseInt(args[0]);

    for (int i = 0; i < n; i++) {
      list.add(Integer.valueOf(i));
    }

    java.util.Collections.shuffle(list);

    printList(list);

		LinkedList<Integer> sorted = QuickSort.sort(list);

		printList(sorted);
	}
}
