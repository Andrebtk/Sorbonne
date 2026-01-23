let rec iter_f (n: int) (f: 'a -> 'a) (x: 'a) : 'a =
	if n=0 then x
		else f (iter_f (n-1) f x) 
;;

let foo (n: int ): int = 
	let next = fun (a,b) -> (a-1, a*b)
	in (snd (iter_f n next (n,1)))
;;

let rec fibo (n: int) : int =
	if n=0 then 0
		else if n=1 then 1
			else (fibo (n-1)) + (fibo (n-2))
;;

let fibo2 (n: int) : int =
	let rec aux (n: int) (a1 : int) (a2 : int) : int =
		if n=0 then a2
			else aux (n-1) (a1+a2) (a1)

	in aux n 1 0
;;

let rec f (x:int):int = 
	if x=0 then 0 
		else if x=1 then 2 
			else (f (if (x mod 2)=0 then 0 else 1))
;;


let add_5 (l:int list): int list =
	let rec aux (la:int list) (acc:int list): int list = 
		match la with
		| [] -> List.rev acc
		| h::t -> (aux t ((5+h)::acc))
	in (aux l []) 
;;

add_5 [1;2;3];;


type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let t_ex = Node(5,
	Node(3,Node(4,Empty,Empty),Node(5,Empty,Empty)),
	Node(2,Node(3,Empty,Node(7,Empty,Empty)),Empty));;


let rec size (bt: int btree) : int =
	match bt with
	| Empty -> 0
	| Node (_,g,d) -> 1 + size(g) + size(d)
;;

size t_ex;;

let size2 (bt: 'a btree) : int =
	let rec aux (acc: int) (lt: ('a btree) list):int = 
		match lt with
		| [] -> acc
		| Empty::t -> aux acc (t)
		| Node (e,g,d)::t -> aux (acc+1) (g::d::t)
	in aux 0 [bt]
;;

size2 t_ex;;


let t_ex = Node(5,
                	Node(3,Node(4,Empty,Empty),Node(5,Empty,Empty)),
                	Node(2,Node(3,Empty,Node(7,Empty,Empty)),Empty));;


let traversal (bt : 'a btree) : 'a list =
	let rec aux (bta : 'a btree) (l : ('a btree) list) (acc : 'a list) =
		match (bta,l) with
		| (Empty,[]) -> List.rev acc
		| (Empty,(h :: t)) -> aux h t acc
		| (Node(e,g,d),lt) -> aux g (d :: lt) (e :: acc)
	in aux bt [] [] 
;;

let rec pre (t : 'a btree) : 'a list = match t with
	| Empty -> []
	| Node(e,g,d) -> e :: ((pre g) @ (pre d))
;;

traversal t_ex ;;
pre t_ex;;


let rec iter_f (n: int) (f: 'a -> 'a) (x: 'a) : 'a =
	if n=0 then x
		else f (iter_f (n-1) f x) 
;;

let rec fiboB (n: int) : int =
	if n=0 then 0
		else if n=1 then 1
			else (fibo (n-1)) + (fibo (n-2))
;;

fiboB 10;;

let fiboa (n:int) : int =
	let next = fun (a,b) -> (b,a+b)
	in if n=0 then 0 else
	(fst (iter_f n next (0,1)))
;;
	
let fibob (n:int) : int =
	let next = fun (a,b) -> (b,a+b)
	in if n=0 then 0 else
	(snd (iter_f (n-1) next (0,1)))
;;

fiboa 10;;