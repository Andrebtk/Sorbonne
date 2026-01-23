type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let t_ex = Node(5,
                	Node(3,Node(4,Empty,Empty),Node(5,Empty,Empty)),
                	Node(2,Node(3,Empty,Node(7,Empty,Empty)),Empty));;

let rec at_prof_list (n:int) (t : 'a btree) : int list = 
	match t with 
		| Empty -> []
		| Node (e,g,d) -> if n=0 
			then [e]
			else (at_prof_list (n-1) g) @ (at_prof_list (n-1) d)
;;



let etiq_prof_list (x : 'a) (t : 'a btree) : int list =
	let rec aux (x: 'a) (t: 'a btree) (acc : int) : int list =
		match t with 
		| Empty -> []
		| Node (e,g,d) -> if e=x then acc::((aux x g (acc+1)) @ (aux x d (acc+1))) else (aux x g (acc+1)) @ (aux x d (acc+1))
	in aux x t 0
;;

assert ((etiq_prof_list 3 t_ex) = [1;2]);;

let rec prof_max (t: 'a btree) : int =
	match t with 
	| Empty -> -1
	| Node (e,g,d) -> 1 + max (prof_max g) (prof_max d)
;;

assert ((prof_max t_ex) = 3);;

let rec max_prof_etiq (x: 'a) (t: 'a btree) : int = 
	let lst = etiq_prof_list x t in 
	List.fold_left (fun a b -> if a > b then a else b ) (-1) lst
;;

assert ((max_prof_etiq 5 t_ex) = 2);;
assert ((max_prof_etiq 7 t_ex) = 3);;


type value = B of bool | I of int;;
exception TYPE_ERROR of int;;

let not1 (v : value) : value = 
	match v with 
		| B v -> B (not v)
		| I u -> raise (TYPE_ERROR u)
;;

(*
not1 (B true) ;;
not1 (I 4);;
*)

let not2 (v : value) : value =
	try (not1 v) with 
		| TYPE_ERROR err -> 
			match v with
				| I u -> B (u=0)

exception DIV_BY_0 of int

let div1 (v1 : value) (v2 : value) : value =
	match v1 with 
		| B bo -> raise (Invalid_argument "div")
		| I i -> match v2 with 
			| B bo2 -> raise (Invalid_argument "div")
			| I i2 -> if i2=0 
				then raise (DIV_BY_0 i)
				else  I (i/i2)
;;

let div2 (v1:value) (v2:value) : value option =
	try Some (div1 v1 v2) with 
		| DIV_BY_0 u -> None
;;