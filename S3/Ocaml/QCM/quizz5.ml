type 'a exparith = 
	Var of 'a 
	| Cste of int 
	| Opp of 'a exparith 
	| Plus of 'a exparith * 'a exparith
	| Mult of 'a exparith * 'a exparith
	| Div of 'a exparith * 'a exparith
;;


let ex =
	Mult (Plus (Cste 2, Opp(Var "x")),
	Var "y");;


(* 2 + (a * b) + (a * c)  *)

let q2 = Plus (
	Cste 2,
	Plus (
		Mult (Var "a",Var "b"),
		Mult (Var "a",Var "c")
	)
);;

let env = [("x", 2); ("y", 4); ("z", 8)]

let eval_var (env : (string*int) list) (x : string) : int =
	try List.assoc x env with
	| Not_found -> raise (Invalid_argument (x ^ " indefini"))
;;

let rec eval_e (env : ('a*int) list) (e : 'a exparith) : int =
	match e with 
	| Var x -> eval_var env x
	| Cste n -> n
	| Opp e0 -> - (eval_e env e0)
	| Plus (e1,e2) -> (eval_e env e1) + (eval_e env e2)
	| Mult (e1,e2) -> (eval_e env e1) * (eval_e env e2)
	| Div (e1,e2) -> (eval_e env e1) / (eval_e env e2)
;;

let rec opp (x : 'a exparith) : 'a exparith =
	match x with
	| Var _ -> Opp x
	| Cste i -> Cste (- i)
	| Opp a -> a
	| Plus (a,b) -> Plus (opp a, opp b)
	| Mult (a,b) -> Mult (opp a, opp b)
	| Div (a,b) -> Div (opp a, opp b)
;;


eval_e env (Div (Cste 5, Plus (Var "y", Cste 4)));;