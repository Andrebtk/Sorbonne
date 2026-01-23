let rec sum_impaire (n: int) : int =
  if n > 0 then (2*n-1) + sum_impaire (n-1) else 0
;;


let sum_impaire_inf (n:int) = 
  if n mod 2 = 1 
    then sum_impaire (n-1)
    else sum_impaire (n-2);;



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