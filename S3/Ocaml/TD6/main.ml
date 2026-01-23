let sum_impair (n:int) : int =
	let rec aux (n: int) (acc : int) : int =
		if n=0 then acc
			else aux (n-1) (acc + 2*n-1)
	in aux n 0
;;
sum_impair 4;;


let rec iter_f (n:int) (f: 'a -> 'a) (x: 'a) : 'a =
	let y = (f x) in
	if n=1 then y
		else iter_f (n-1) f y
;;

iter_f 5 (fun x -> x+1) 0;;

let rec rev_append (l1: 'a list) (l2: 'a list) : 'a list =
	match l1 with 
		| [] -> l2
		| h::t -> rev_append t (h::l2)
;;

rev_append [1;2] [3;4;5;6];;

let rev (l1: 'a list): 'a list =
	let rec aux (l1: 'a list) (l2: 'a list) : 'a list =
		match l1 with 
			| [] -> l2
			| h::t -> aux t (h::l2)
	in aux l1 []
;;	

rev [1;2;3;4;5];;

let append (l1: 'a list) (l2 :'a list) : 'a list =
	let rec aux (l1: 'a list) (l2: 'a list) (l3 : 'a list) : 'a list =
		match l1 with
			| [] -> (rev l3) @ l2
			| h::t -> aux t l2 (h::l3)
	in aux l1 l2 []
;;

append [1;2] [3;4;5;6];;

let map (f: 'a -> 'b) (l: 'a list) : 'b list =
	let rec aux (f:'a -> 'b) (l: 'a list) (res: 'b list): 'b list =
		match l with 
			| [] -> List.rev res
			| h::t -> aux f t ((f h)::res)
	in aux f l []
;;

map (fun x -> x+1) [1;2;3;4];;
List.map (fun x -> x+1) [1;2;3;4];;

let filter (f : 'a -> bool) (l : 'a list) : 'a list =
	let rec aux (f : 'a -> bool) (l : 'a list) (res: 'a list) : 'a list = 
		match l with
			| [] -> List.rev res
			| h::t -> aux f t (if (f h) then h::res else res)
		in aux  f l []
;;

filter (fun x -> (x mod 2)=0) [1;2;3;4;5;6;7];;
List.filter (fun x -> (x mod 2)=0) [1;2;3;4;5;6;7];;