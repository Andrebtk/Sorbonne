type tree = 
| Leaf
| Node of int * tree * tree;;

let rec inver_tree(root: tree) : tree = 
  match root with 
  | Leaf -> Leaf
  | Node(head, l, r) -> Node(head, inver_tree r, inver_tree l)
;;


let rec max_depth(root: tree) : int =
	match root with 
	| Leaf -> 0
	| Node(v, l, r) -> 1 + max (max_depth l) (max_depth r)
;;

let rec hamming_weight (n: int) : int =
	if n>0 then
		if (n mod 2) == 1 
			then 1 + hamming_weight (n / 2)
			else hamming_weight (n/2)
	else 0
;;

