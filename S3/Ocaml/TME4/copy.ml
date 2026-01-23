type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let bt_sujet = Node(5, Node(2,Node(1,Empty,Empty),Node(4,Node(3,Empty,Empty),Empty)),Node(6,Empty,Node(7,Empty,Node(8,Empty,Empty))))

let bt_1 = Node(2,Node(4,Empty,Empty),Empty) 
let bt_2 = Node(4,Node(6,Empty,Empty),Empty)
let bt_3 = Node(4,Node(5,Empty,Empty),Empty)
let bt_4 = Node(4,Node(3,Empty,Empty),Empty)
let bt_5 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(6,Empty,Node(7,Empty,Empty)))
let bt_6 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(3,Empty,Node(7,Empty,Empty)))
let bt_7 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(7,Empty,Node(6,Empty,Empty)))
let bt_8 = Node(3,Node(1,Empty,Node(2,Empty,Node(2,Empty,Node(2,Empty,Empty)))),Node(5,Empty,Node(31,Node(18,Empty,Empty),Node(42,Empty,Empty))))

let b_test = Node(2,Node(2,Node(7,Empty,Empty),Empty),Node(4,Empty,Node(1,Empty,Empty)))

let rec lt_btree (t: 'a btree) (x: 'a) : bool =
	match t with 
	| Empty -> true
	| Node (e,g,d) -> (e<x) && (lt_btree g x) && (lt_btree d x)
;;

assert ((lt_btree bt_1 5) = true);;
assert ((lt_btree bt_2 5) = false);;
assert ((lt_btree Empty 5) = true);;


let rec ge_btree (t: 'a btree) (x: 'a) : bool =
	match t with 
	| Empty -> true
	| Node (e,g,d) -> (e>=x) && (ge_btree g x) && (ge_btree d x)
;;

assert (( ge_btree bt_3 4) = true);;
assert (( ge_btree bt_4 4) = false);;
assert ((ge_btree Empty 5) = true);;

let rec is_abr (bt: 'a btree) : bool = 
	match bt with
	| Empty -> true
	| Node (e,g,d) -> (is_abr g) && (is_abr d) &&( lt_btree g e) && (ge_btree d e)
;;

assert ((is_abr Empty) = true);;
assert ((is_abr bt_5) = true);;
assert ((is_abr bt_6) = false);;
assert ((is_abr bt_7) = false);;

let rec mem (bt :'a btree) (x:'a) : bool = 
	match bt with
	| Empty -> false
	| Node (e,g,d) -> if(x=e) then true 
		else if (x>e) then (mem d x) else mem g x
;;

assert (( mem Empty 4) = false);;
assert ((mem bt_5 4) = true);;
assert ((mem bt_5 8) = false);;
assert ((mem b_test 1) = false);;
assert ((mem b_test 7) = false);;

let rec insert (bt: 'a btree) (x:'a) : 'a btree =
	match bt with 
	| Empty -> Node (x, Empty, Empty)
	| Node (e,g,d) -> if(x<e) then Node (e, (insert g x), d)
		else Node (e, g, (insert d x))
;;

assert ((insert Empty 4)= Node (4, Empty, Empty));;
assert ((insert bt_5 3)=Node(5,Node (2, Node (1, Empty, Empty), Node (4, Node (3, Empty, Empty), Empty)),Node (6, Empty, Node (7, Empty, Empty))));;
assert ((insert bt_5 4)=Node(5,Node (2, Node (1, Empty, Empty), Node (4, Empty, Node (4, Empty, Empty))),Node (6, Empty, Node (7, Empty, Empty))));;


let rec abr_of_list (l: 'a list) :'a btree =
	List.fold_left (fun e b -> insert e b) Empty l
;;

assert ((abr_of_list [3;1;2;5;31;2;42;18;2])=Node(3,Node (1, Empty, Node (2, Empty, Node (2, Empty, Node (2, Empty, Empty)))),Node(5, Empty, Node (31, Node (18, Empty, Empty), Node (42, Empty, Empty)))))

let rec list_of_abr(bt: 'a btree): 'a list = 
	match bt with 
	| Empty -> []
	| Node (e,g,d) -> (list_of_abr g) @ [e] @ (list_of_abr d)
;;

assert ((list_of_abr bt_8) = [1; 2; 2; 2; 3; 5; 18; 31; 42]);;

let abr_sort (l: 'a list) : 'a list =
	list_of_abr (abr_of_list l)
;;

assert ((abr_sort [12;3;5;42;1;18;21]) = [1; 3; 5; 12; 18; 21; 42]);;