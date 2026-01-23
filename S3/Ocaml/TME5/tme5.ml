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


let rec huff_tab (t:'a htree) : (('a * (int list)) list) =
  match t with 
  | Leaf (_, lettre) -> [((lettre, []))];
  | Branch (_, g,d) ->
    let gtmp = (huff_tab g) in
    let dtmp = (huff_tab d) in 
    (List.map (fun (lettre, lst) -> (lettre, 0::lst)) gtmp) @ (List.map (fun (lettre, lst) -> (lettre, 1::lst)) dtmp) 
;;

assert ((huff_tab t_msg)=[('A', [0]); ('C', [1; 0; 0; 0]); ('G', [1; 0; 0; 1]); ('H', [1; 0; 1; 0]);('F', [1; 0; 1; 1]); ('E', [1; 1; 0; 0]); ('D', [1; 1; 0; 1]);('B', [1; 1; 1])])


let rec code (m: 'a list) (c : ('a * (int list)) list) : int list = 
  match m with
  | [] -> []
  | h::t -> (List.assoc h c) @ (code t c);;
;;

assert ((code msg (huff_tab t_msg)) = [0; 0; 1; 1; 1; 0; 1; 0; 0; 0; 1; 1; 1; 0; 1; 0; 0; 1; 1; 0; 1; 0; 0; 0; 1; 0; 1; 1; 1; 1; 0; 0; 0; 1; 1; 0; 1; 1; 1; 1; 0])

exception Invalid_input;;
let rec decode1 (l: int list) (t: 'a htree) : ('a * (int list)) =
  match t with
  | Leaf (_, lettre) -> (lettre, l)
  | Branch (_, g, d) -> match l with
    | [] -> raise Invalid_input
    | h::t2 -> if h=0 then (decode1 t2 g) else (decode1 t2 d)
;;

assert ((decode1 [0; 0; 1; 1; 1] t_msg) = ('A', [0; 1; 1; 1]));;
assert ((decode1 [1; 1; 1] t_msg)= ('B', []));;


let rec decode (l: int list) (t : 'a htree) : 'a list =
  List.fold_left (fun x,chiffre -> ) [] l 
;;

assert ((decode msg_01 t_msg)=['A'; 'A'; 'B'; 'A'; 'C'; 'B'; 'A'; 'G'; 'H'; 'A'; 'A'; 'F';'E'; 'A'; 'D'; 'B'; 'A'])
