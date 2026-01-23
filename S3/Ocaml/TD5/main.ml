let rec map_cons (e : 'a) (l : 'a list list): 'a list list =
	match l with
		| [] -> []
		| a::b -> (e::a) :: (map_cons e b);;

let rec all_in_list (l1 : 'a list) (l2 : 'a list) : bool =
	match l1 with
		| [] -> true
		| a::b -> 
			if (List.mem a l2) 
				then (all_in_list b l2)
				else false ;;


				
let rec is_prefix (l1 : 'a list) (l2 : 'a list) : bool = 
	match l1 with 
		| [] -> true
		| a::b ->
			match l2 with 
				| [] -> false
				| c::d -> 
						if a=c 
							then (is_prefix b d)
							else false ;;

let rec prefixes (l : 'a list) : 'a list list =
	match l with 
		| [] -> [ [] ]
		| a::b -> []::(map_cons a (prefixes b));;

let rec all_prefix_in (l1 : 'a list) (l2 : 'a list list) : bool = 
	let prefL1 = (prefixes l1) in
	all_in_list prefL1 l2 
;;



let rec pref_complete (l: ('a list) list) : bool = 
	List.for_all (fun e -> all_prefix_in e l) l 
;;


assert ((pref_complete [[];[0];[0;1];[1];[1;0];[1;0;0];[1;1];[1;1;0];[1;1;1]]) = true);;
assert ((pref_complete [[];[0];[0;1];[1];[1;0;0];[1;1];[1;1;0];[1;1;1]]) = false);;


let rec is_max_pref2 (l1: 'b list) (l2: ('a * ('b list)) list) : bool = 
	List.for_all (fun (x,c) -> (((is_prefix l1 c) && (l1=c))||(not (is_prefix l1 c)))) l2
;;

assert ((is_max_pref2 [0;1] [('a',[]);('b',[0]);('c',[0;1]);('d',[1]);('e',[1; 0]);('f',[1;0;0]);('g',[1;1]);('h',[1;1;0]);('i',[1;1;1])]) = true);;
assert ((is_max_pref2 [1;0] [('a',[]);('b',[0]);('c',[0;1]);('d',[1]);('e',[1; 0]);('f',[1;0;0]);('g',[1;1]);('h',[1;1;0]);('i',[1;1;1])]) = false);;

let max_pre_list2 (l: ('a * ('b list)) list) : ('a * ('b list)) list =
	List.filter (fun (x,c) -> is_max_pref2 c l) l
;;


assert (((max_pre_list2 [('a',[]);('b',[0]);('c',[0;1]);('d',[1]);('e',[1; 0]);('f',[1;0;0]);('g',[1;1]);('h',[1;1;0]);('i',[1;1;1])])) = [('c', [0; 1]); ('f', [1; 0; 0]); ('h', [1; 1; 0]); ('i', [1; 1; 1])]);;


type 'a btree = Empty | Node of 'a * ('a btree) * ('a btree)
let tree1 = Node('a',Node('b',Empty,Node('c',Empty,Empty)),
				Node('d',Node('e',Node('f',Empty,Empty),Empty),
					Node('g',Node('h',Empty,Empty),
						Node('i',Empty,Empty))));;


let rec at_path (t:'a btree) (c: int list) : 'a =
	match (t,c) with 
	| (Empty, []) -> raise (Invalid_argument "at_path")
	| (Empty, h::t) -> raise (Invalid_argument "at_path")
	| (Node (e,g,d), []) -> e
	| (Node (e,g,d), h::t) -> if h=1 then at_path d t 
								else if h=0 at_path g t
								else raise (Invalid_argument "at_path")


;;


assert ((at_path tree1 []) = 'a');;
assert ((at_path tree1 [1;0]) = 'e');;
(*
at_path tree1 [0;0];;
at_path tree1 [2;0];;
*)

let rec path_tree (t: 'a btree) : ('a * (int list)) list =
	match t with 
	| Empty -> []
	| Node (e,g,d) -> 
		let gList = (path_tree g) in
		let dList = (path_tree d) in
		[(e,[])] @ (List.map (fun (e,l) -> (e,0::l)) gList) @ (List.map (fun (e,l) -> (e,1::l)) dList)
;;

assert ((path_tree tree1) = [('a', []); ('b', [0]); ('c', [0; 1]); ('d', [1]); ('e', [1; 0]);('f', [1; 0; 0]); ('g', [1; 1]); ('h', [1; 1; 0]); ('i', [1; 1; 1])]);;

let rec is_tree (l: (int list) list) : bool =
	pref_complete l
;;

assert ((is_tree (List.map snd (path_tree tree1))) = true);;
assert ((is_tree [[]; [1]; [1; 0]; [1; 0; 1; 1]]) = false);;

let rec leaves_list (l: ('a * (int list)) list) : 'a list =
	let is_leaf (_, c1) =
	  not (List.exists (fun (_, c2) -> c1 <> c2 && is_prefix c1 c2) l)
	in
	List.map fst (List.filter is_leaf l)
  ;;
  

assert ((leaves_list (path_tree tree1)) = ['c'; 'f'; 'h'; 'i']);;
