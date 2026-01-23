let rec bin_to_int (i: int list) : int =
	match i with 
		| [] -> raise(Invalid_argument "Empty list")
		| [h] -> h
		| h::t -> h + 2*(bin_to_int t) 
;;

let rec int_to_bin (i : int) : int list = 
	if (i<2)
		then [i] 
		else if (i mod 2)=0 
			then (0)::(int_to_bin (i/2))
			else (1)::(int_to_bin (i/2))
;;

let rec comp_bin (l : int list) (n : int) : int list = 
	match l with 
		| h::t -> h::(comp_bin t (n-1))
		| [] -> if n<0 
			then raise(Invalid_argument "comp_bin")
			else if (n=0) 
				then []
				else (0)::comp_bin [] (n-1) 
;;

type int_set = 
	| N of int_set * int_set
	| E of bool
;;

let ex =
	N(N(E true,
		E true),
	N(E false,
		E true))
		
exception Not_perfect
exception No_fit


let rec hauteur_equilibre (t: int_set): int =
	match t with
	| E b -> 0
	| N (g,d) -> 
		let gh = (hauteur_equilibre g) in
		let dh = (hauteur_equilibre d) in
		if (gh <> dh) then raise (Not_perfect )
			else 1 + (max (hauteur_equilibre g) (hauteur_equilibre d))
;;

assert ((hauteur_equilibre ex) == 2);;
assert ((hauteur_equilibre (E true)) == 0);;
(* (hauteur_equilibre (N(N(E true,E true),E false))) ;; *)





(*
let rec aux (t: int_set) (acc:int): int list=
	match t with
	| E b -> if b then [acc] else []
	| N (g,d) -> (aux g (2*acc)) @ (aux d (1 + 2*acc))
;;

aux ex 0;;

let rec mem (x: int) (t: int_set) : bool = 
	let xbin = (int_to_bin x) in
	
	
	let rec aux1 (xbin: int list) (x:int):bool = 
		match xbin with
		| [] -> false
		| h::t -> h=x || (aux1 t x)
	in aux1 xbin x
;;
*)
let rec mem (x: int) (t: int_set) : bool = 
	match t with 
	| E b -> b
	| N (g,d) -> 
		let t = (x mod 2) in
		if t=1 then mem (x/2) d 
			else mem (x/2) g
;;

assert ((mem 2 ex) == true);;
assert ((mem 1 ex) == false);;


let rec insert_exn (t: int_set) (x: int): int_set =
	let xbin = (int_to_bin x) in
	
	let rec aux (xbin: int list) (t: int_set): int_set =
		match (t, xbin) with
		| (E b, []) -> E true
		| (E b, h::t) -> raise No_fit
		| (N (g,d), []) -> raise No_fit
		| (N (g,d), h::t) -> if (h=1) then N (g,(aux t d)) else N ((aux t g),d)
	in aux (xbin) t
;;



