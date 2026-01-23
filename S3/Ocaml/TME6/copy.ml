let rec bin_to_int (i: int list) : int =
	match i with 
		| [] -> raise(Invalid_argument "Empty list")
		| [h] -> h
		| h::t -> h + 2*(bin_to_int t) 
;;

let rec int_to_bin (i : int) : int list = 
	if i = 1 then [1; 0]  (* Special case for 1 *)
	else if i < 2 then [i]  (* Base case for other single-digit numbers *)
	else if (i mod 2) = 0 
	  then 0 :: int_to_bin (i / 2)
	  else 1 :: int_to_bin (i / 2)
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

let rec display_tree (t: int_set) (indent: string) : unit =
	match t with
	| E b -> 
		Printf.printf "%sE (%b)\n" indent b  (* Print leaf node with current indentation *)
	| N (left, right) ->
		Printf.printf "%sN\n" indent;  (* Print the node *)
		display_tree left (indent ^ "  ");  (* Increase indentation for left subtree *)
		display_tree right (indent ^ "  ")  (* Increase indentation for right subtree *)
  ;;
let show_tree t = display_tree t "";;




let ex =
	N(N(E true,
		E true),
	N(E false,
		E true));;

exception Not_perfect;;
exception No_fit;;

let rec hauteur_equilibre (t: int_set) : int =
 match t with 
 | E b -> 0
 | N (g,d) -> let hg = hauteur_equilibre g in 
	let hd  = hauteur_equilibre d in 
	if (hg <> hd) then raise Not_perfect else 1 + (max (hauteur_equilibre g) (hauteur_equilibre d))
;;

assert ((hauteur_equilibre ex) = 2);;
(* hauteur_equilibre (N(N(E true,E true),E false));; *)

let rec mem (x: int) (t: int_set) : bool = 
	match t with
	| E b -> b
	| N (g,d) -> if (x mod 2 = 1) then mem (x/2) d else mem (x/2) g
;;

assert ((mem 2 ex) = true);;
assert ((mem 1 ex) = false);;


let insert_exn (t:int_set) (x:int) : int_set=
	let x_bin = (int_to_bin x) in 

	let rec aux (lst : int list) (t:int_set): int_set=
		match (t, lst) with 
		| (E b, []) -> E (true)
		| (N (g,d), []) -> raise No_fit
		| (E b, h::t2) -> raise No_fit
		| (N (g,d), h::t2) -> if h=0 then N ( (aux t2 g), d) else N (g, (aux t2 d))
	in  aux x_bin t
;;

assert ((insert_exn ex 1) = N(N(E true,E true),N(E true,E true)));;

let rec increase_height (t: int_set) : int_set = 
	match t with 
	| E b -> if not b 
		then N (E false, E false)
		else N (E true, E false)
	| N (g,d) -> N ((increase_height g), (increase_height d))
;;

(*show_tree (increase_height ex);; *)

let rec insert (x: int) (t: int_set) : int_set =
	try (insert_exn t x) with 
	| No_fit -> insert x (increase_height t)
;;

(* show_tree (insert 1 ex);; *)

let rec list_to_tree (l : int list) : int_set =
	List.fold_left (fun e x -> insert x e ) (E false) l
;;

assert ((list_to_tree [])= E false);;

(* assert ((list_to_tree [0;2;3]) = ex);; Erreur a cause de int_to_bin dans insert_exn*)

let rec path_list (t: int_set) : ((int list) * bool) list =
	match t with 
	| E b -> [([],b)]
	| N (g,d) -> 
		let glst = path_list g in 
		let dlst = path_list d in 
			(List.map (fun (l,x) -> (0::l,x)) glst) @ (List.map (fun (l,x) -> (1::l,x)) dlst)
;;

assert ((path_list ex) = [([0; 0], true); ([0; 1], true); ([1; 0], false); ([1; 1], true)]);;

let tree_to_list (t: int_set) : int list = 
	let p_list = path_list t in 
		List.rev (List.fold_left (fun x (l,y) -> if y then (bin_to_int l)::x else x) [] p_list)
;;


assert ((tree_to_list ex) = [0; 2; 3]);;