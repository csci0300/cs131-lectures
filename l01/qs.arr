import lists as L

# Pyret quicksort
fun qsort(l):
  cases (List) l:
    | empty => empty
    | link(pivot, rest) => block:
        left = qsort(rest.filter(lam(x): x < pivot end))
        right = qsort(rest.filter(lam(x): x >= pivot end))
        lists.append(left, right.push(pivot))
      end
  end
where:
  qsort(empty) is empty
  qsort([list: 6, 2, 9, 2, 1]) is [list: 1, 2, 2, 6, 9]
end

# Helper functions
fun print_list(i, l) block:
  when i == 0 block:
    print("[")
  end
  if i < 20:
    cases (List) l:
      | empty => print("]\n")
      | link(x, rest) => block:
          when i <> 0 block:
              print(", ")
          end
          print(x)
          print_list(i + 1, rest)
        end
    end
  else:
    print(", ...]\n")
  end
end

l = range(0, 1000)

print_list(0, L.shuffle(l))
print_list(0, qsort(l))
