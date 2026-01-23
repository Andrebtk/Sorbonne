type 'a htree =
	Leaf of int * 'a
	| Branch of int * 'a htree * 'a htree

let t_msg = Branch(17,Leaf(8,'A'),Branch(9,Branch(4,Branch(2,Leaf(1,'C'),Leaf(1,'G')),Branch(2,Leaf(1,'H'),Leaf(1,'F'))),Branch(5,Branch(2,Leaf(1,'E'),Leaf(1,'D')),Leaf(3,'B'))))
let msg = ['A';'A';'B';'A';'C';'B';'A';'G';'H';'A';'A';'F';'E';'A';'D';'B';'A']
let msg_01 = [0;0;1;1;1;0;1;0;0;0;1;1;1;0;1;0;0;1;1;0;1;0;0;0;1;0;1;1;1;1;0;0;0;1;1;0;1;1;1;1;0]

let t1 = Leaf(3,'B')
let t2 = Branch(5,Leaf(2,'Z'),Leaf(3,'B'))
let t3 = Branch(5,Leaf(2,'Z'),Leaf(3,'W'))
let t4 = Leaf(3,'K')

let l1 = [Leaf(8,'A');Leaf(3,'B');Leaf(1,'D');Leaf(1,'E');Leaf(1,'F');Leaf(1,'H');Leaf(1,'G');Leaf(1,'C')]
let l2 = [('A',8);('B',3);('D',1);('E',1);('F',1);('H',1);('G',1);('C',1)]


let rec huff_tab (t: 'a htree) : ('a * (int list)) list =
	match t with
	| Leaf  (e,a) -> [ (a,[]) ]
	| Branch (e,g,d) -> 
		let glist = huff_tab g in
		let dlist = huff_tab d in 
			(List.map (fun (e, list) -> (e, 0::list)) glist) @ (List.map (fun (e, list) -> (e, 1::list)) dlist)
;;

assert ((huff_tab t_msg) = [('A', [0]); ('C', [1; 0; 0; 0]); ('G', [1; 0; 0; 1]); ('H', [1; 0; 1; 0]);('F', [1; 0; 1; 1]); ('E', [1; 1; 0; 0]); ('D', [1; 1; 0; 1]);('B', [1; 1; 1])])


let rec code (m: 'a list) (c: ('a * (int list)) list): int list =
	match m with 
	| [] -> []
	| h::t -> (List.assoc h c) @ (code t c)
;;
assert ((code msg (huff_tab t_msg))=[0; 0; 1; 1; 1; 0; 1; 0; 0; 0; 1; 1; 1; 0; 1; 0; 0; 1; 1; 0; 1;0; 0; 0; 1; 0; 1; 1; 1; 1; 0; 0; 0; 1; 1; 0; 1; 1; 1; 1; 0]);;

exception Invalid_input;;
let rec decode1 (l: int list) (t: 'a htree) : ('a * (int list)) =
	match (l,t) with 
	| ([], Leaf (_,e)) -> (e, [])
	| ([], Branch (x,g,d)) -> raise Invalid_input
	| (h::t, Leaf(_,e)) -> (e, h::t)
	| (h::t, Branch (x,g,d)) ->if (h=0) then decode1 t g else decode1 t d
;;


assert ((decode1 [0; 0; 1; 1; 1] t_msg) = ('A', [0; 1; 1; 1]));;
assert ((decode1 [1; 1; 1] t_msg)= ('B', []));;

let rec decode (l: int list) (t : 'a htree) : 'a list =
		match l with 
		| [] -> []
		| _::_ -> 
			let (e, list) = (decode1 l t) in
			e::(decode list t)
;;

assert ((decode msg_01 t_msg) = ['A'; 'A'; 'B'; 'A'; 'C'; 'B'; 'A'; 'G'; 'H'; 'A'; 'A'; 'F';'E'; 'A'; 'D'; 'B'; 'A'])

let rec freq_ht (t: 'a htree) : int =
	match t with 
	| Leaf (e,lettre) -> e 
	| Branch (e,g,d) -> e
;;

assert ((freq_ht t1) = 3);;
assert ((freq_ht t2) = 5);;

let rec ht_less (t1: 'a htree) (t2 : 'a htree) : bool =
	match (t1,t2) with 
	| (Leaf (e1,lettre1), Leaf (e2,lettre2)) ->  e1 < e2
	| (Leaf (e1,lettre1), Branch (x2,g2,d2)) -> e1 < x2
	| (Branch (x1,g1,d1), Leaf(e2,lettre2)) -> x1 < e2
	| (Branch (x1,g1,d1), Branch (x2,g2,d2)) -> x1 < x2
;;

assert ((ht_less t1 t2) = true);;
assert ((ht_less t2 t1) = false);;

exception Invalid_argument;;
(*
let rec min_sauf_min (lt: ('a htree) list) : (('a htree) list) =
	match lt with 
	| [] -> raise Invalid_argument
	| _ -> let min_abr = (List.fold_left (fun i j -> ) [] lt) in
		let lst = List.filter (fun e -> e <> min_abr ) lt in 
;;

assert ((min_sauf_min [t3; t1; t4]) = (Leaf (3, 'K'), [Branch (5, Leaf (2, 'Z'), Leaf (3, 'W')); Leaf (3, 'B')]));;
*)

let rec ht_branch (t1: 'a htree) (t2: 'a htree) : 'a htree =
	match (t1, t2) with 
	| (Leaf (e1,lettre1), Leaf (e2,lettre2)) -> Branch (e1+e2, Leaf (e1,lettre1), Leaf (e2,lettre2))
	| (Leaf (e1,lettre1), Branch (x2,g2,d2)) -> Branch (e1+x2, Leaf (e1,lettre1), Branch (x2,g2,d2))
	| (Branch (x1,g1,d1), Leaf(e2,lettre2)) -> Branch (x1+e2,Branch (x1,g1,d1), Leaf(e2,lettre2))
	| (Branch (x1,g1,d1), Branch (x2,g2,d2)) -> Branch (x1+x2, Branch (x1,g1,d1), Branch (x2,g2,d2))
;;

assert ((ht_branch t3 t1) = Branch (8, Branch (5, Leaf (2, 'Z'), Leaf (3, 'W')), Leaf (3, 'B')));;

let rec leaf_list (f: ('a * int) list) : ('a htree) list =
	List.map (fun (lettre, freq) -> Leaf (freq, lettre) ) f
;;

assert ((leaf_list l2) = [Leaf (8, 'A'); Leaf (3, 'B'); Leaf (1, 'D'); Leaf (1, 'E'); Leaf (1, 'F');Leaf (1, 'H'); Leaf (1, 'G'); Leaf (1, 'C')]);;

(*
let rec huff_of_freq (f: ('a*int) list) : 'a htree =

;;

huff_of_freq l2;;
*)