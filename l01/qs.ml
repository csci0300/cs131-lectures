(* Ocaml quicksort *)
let rec qs = function
     | []    -> []
     | pivot::xs ->
           let left  = List.filter (fun y -> y < pivot)  xs
           and right = List.filter (fun y -> y >= pivot) xs
           in  (qs left) @ [pivot] @ (qs right);;



(* Helper functions *)
let rec range a b =
    let rec aux a b l =
        if a > b then l else aux a (b - 1) (b :: l)
    in aux a b [];;

let shuffle l =
    let nl = List.rev_map (fun c -> (Random.bits (), c)) l in
    let shuffled = List.sort compare nl in
    List.rev_map snd shuffled;;

let rec print_list i l =
    if i = 0 then print_string "[";
    if i < 20 then
        match l with
        | []      -> print_string "]\n"
        | x :: xs -> if i <> 0 then print_string ", ";
                     print_int x;
                     print_list (i + 1) xs
    else
        print_string ", ...]\n";;

Random.self_init ();;
let list = shuffle (range 0 99999) in
let sorted = qs list in
print_list 0 list;
print_list 0 sorted
