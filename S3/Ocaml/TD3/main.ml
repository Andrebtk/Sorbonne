let rec add_freq (c: 'a) (l: ('a*int) list) : ('a*int) list = 
	match l with 
		| [] -> [(c, 1)]
		| (x, count)::t -> if (x=c) 
			then (x, count+1)::t
			else (x, count)::add_freq c t
;;

assert ((add_freq 'A' [] = [('A', 1)]));;
assert ((add_freq 'A' [('D',1); ('E',1); ('A',5); ('B',3); ('C',1)]) = [('D', 1); ('E', 1); ('A', 6); ('B', 3); ('C', 1)]);;
assert ((add_freq 'H' [('D',1); ('E',1); ('A',5); ('B',3); ('C',1)]) = [('D', 1); ('E', 1); ('A', 5); ('B', 3); ('C', 1); ('H', 1)])

let rec freq (l: 'a list) : ('a * int) list =
	match l with
 	| [] -> []
  	| h::t -> add_freq h (freq t)
;;


let add_fst (c: (int*int)): (int*int) = 
	let (n1, n2) = c in (n1+1, n2)
;;

let add_snd (c: (int*int)): (int*int) = 
	let (n1, n2) = c in (n1, n2+1)
;;

let rec nb_of (l: char list) : int*int =
	match l with 
		| [] -> (0,0)
		| h::t -> if h = '>'
			then add_snd (nb_of t)
			else add_fst (nb_of t)
;;

let o_sup_f (l: char list) : bool = 
	let (n1, n2) = nb_of l in 
		n1>=n2
;;

let rec all_o_sup_f(l : (char list) list) : bool = 
	List.for_all o_sup_f l
;;

let dyck (l: char list): bool = 
	all_o_sup_f (prefixes l)
;;


let sum_left (l: int list) : int = 
	List.fold_left (fun x y -> x+y) 0 l
;;

let sum_right (l: int list) : int = 
	List.fold_right (fun x y -> x+y) l 0
;;

assert ((sum_right [3; 7; 2]) = 12);;