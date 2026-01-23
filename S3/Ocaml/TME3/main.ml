let rec is_in (e: 'a) (l : 'a list) : bool = 
  match l with  
    | [] -> false
    | h::t -> e=h || is_in e t
;;
 
assert ((is_in 4 []) = false) ;;
assert ((is_in 3 [1;3;2]) = true) ;;
assert ((is_in 4 [1;3;2]) = false) ;;


let add_elem (e : 'a) (l: 'a list) : 'a list =
  if (is_in e l) 
    then l
    else e::l
;;

assert ((add_elem 4 [1;3;2]) = [4;1;3;2]) ;;
assert ((add_elem 4 [1;3;4;2]) = [1;3;4;2]) ;;
assert ((add_elem 4 []) = [4]);;

let rec is_subset_rec (l1 : 'a list) (l2 : 'a list) : bool =
  match l1 with
    | [] -> true
    | h::t -> (is_in h l2) && is_subset_rec t l2
;;

assert ((is_subset_rec [4;2] [0;2;4;6]) = true);;
assert ((is_subset_rec [] [0;2;4;6]) = true);;
assert ((is_subset_rec [2;3;4] [0;2;4;6]) = false);;
assert ((is_subset_rec [4;2;0;6] [0;2;4;6]) = true);;

let is_subset (l1 : 'a list) (l2 : 'a list) : bool = 
  List.for_all (fun x -> is_in x l2) l1
;;

assert ((is_subset [4;2] [0;2;4;6]) = true);;
assert ((is_subset [] [0;2;4;6]) = true);;
assert ((is_subset [2;3;4] [0;2;4;6]) = false);;
assert ((is_subset [4;2;0;6] [0;2;4;6]) = true);;

let rec eq_set (l1 : 'a list) (l2 : 'a list) : bool =
  (is_subset l1 l2) && (is_subset_rec l2 l1)
;;

assert ((eq_set [4;2] [0;2;4;6]) = false) ;;
assert ((eq_set [4;2;6;0] [0;2;4;6]) = true) ;;
assert ((eq_set [4;2;6;0] [0;2;5;6]) = false) ;;
assert ((eq_set [] []) = true) ;;

let rec intersection_rec (l1 : 'a list) (l2 : 'a list) : 'a list =
  match l1 with 
    | [] -> []
    | h::t -> if ( (is_in h l2) && (is_in h l1) )
      then h::(intersection_rec t l2)
      else (intersection_rec t l2)
;;

assert ((intersection_rec [] [3;5;4;6]) = []) ;;
assert ((intersection_rec [1;2;3;4] [3;5;4;6]) = [3;4]) ;;
assert ((intersection_rec [1;2;3;4] []) = []) ;;


let intersection (l1 : 'a list) (l2 : 'a list) : 'a list =
  List.filter (fun x -> is_in x l2) l1
;;

assert ((intersection [] [3;5;4;6]) = []) ;;
assert ((intersection [1;2;3;4] [3;5;4;6]) = [3;4]) ;;
assert ((intersection [1;2;3;4] []) = []) ;;

let rec union_rec (l1 : 'a list) (l2 : 'a list) : 'a list = 
  match l2 with 
    | [] -> l1
    | h::t -> add_elem h (union_rec l1 t)
;;

assert ((union_rec [1;2;3;4] [3;5;4;6]) = [5; 6; 1; 2; 3; 4]) ;;
assert ((union_rec [] [3;5;4;6]) = [3;5;4;6]) ;;

let union_left (l1 : 'a list) (l2 : 'a list) : 'a list = 
  List.fold_left (fun x y -> (add_elem y x) ) l1 l2
;;

assert ((union_left [1;2;3;4] [3;5;4;6]) = [6; 5; 1; 2; 3; 4]) ;;
assert ((union_left [] [3;5;4;6]) = [6;4;5;3]) ;;

let union_right (l1 : 'a list) (l2 : 'a list) : 'a list = 
  List.fold_right (fun x y -> add_elem x y ) l2 l1
;;
assert ((union_right [1;2;3;4] [3;5;4;6]) = [5; 6; 1; 2; 3; 4]) ;;
assert ((union_right [] [3;5;4;6]) = [3;5;4;6]) ;;

let make_pairs (x : 'a) (l : 'b list) : ('a * 'b) list =
  List.map (fun e -> (x, e)) l
;;

assert ((make_pairs true [3;5]) = [(true, 3); (true, 5)]) ;;
assert ((make_pairs 1 [] = [])) ;;


let rec product_rec (l1 : 'a list) (l2 : 'b list) : ('a * 'b) list =
  match l1 with
    | [] -> []
    | h::t -> (make_pairs h l2) @ (product_rec t l2)
;;
assert ((product_rec [1;2;3] []) = []) ;;
assert ((product_rec [] [1;2;3]) = []) ;;
assert ((product_rec [1;2;3] ['a'; 'b']) = [(1, 'a'); (1, 'b'); (2, 'a'); (2, 'b'); (3, 'a'); (3, 'b')]) ;;


let product (l1 : 'a list) (l2 : 'b list) : ('a * 'b) list =
  List.flatten (List.map (fun x -> make_pairs x l2) l1)
;;

assert ((product [1;2;3] []) = []) ;;
assert ((product [] [1;2;3]) = []) ;;
assert ((product [1;2;3] ['a'; 'b']) = [(1, 'a'); (1, 'b'); (2, 'a'); (2, 'b'); (3, 'a'); (3, 'b')]) ;;


let rec powerset_rec (l: 'a list) : 'a list list = 
  match l with 
    | [] -> [[]]
    | h::t -> [h] :: (powerset_rec t)
;;



powerset_rec [] ;;
powerset_rec [1;2;3] ;;









(*
let rec powerset_rec (l : 'a list) : 'a list list =
  match l with 
    | [] -> [[]]
    | h::t -> 
;;

assert ((powerset_rec []) = [[]]) ;;
assert ((powerset_rec [1;2;3]) = [[]; [3]; [2]; [2; 3]; [1]; [1; 3]; [1; 2]; [1; 2; 3]]) ;;
*)