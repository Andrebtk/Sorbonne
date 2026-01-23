type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let bt_sujet = Node(5, Node(2,Node(1,Empty,Empty),Node(4,Node(3,Empty,Empty),Empty)),Node(6,Empty,Node(7,Empty,Node(8,Empty,Empty))))

let bt_1 = Node(2,Node(4,Empty,Empty),Empty) 
let bt_2 = Node(4,Node(6,Empty,Empty),Empty)
let bt_3 = Node(4,Node(5,Empty,Empty),Empty)
let bt_4 = Node(4,Node(3,Empty,Empty),Empty)
let bt_5 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(6,Empty,Node(7,Empty,Empty)))
let bt_6 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(3,Empty,Node(7,Empty,Empty)))
let bt_7 = Node(5,Node(2,Node(1,Empty,Empty),Node(4,Empty,Empty)),Node(7,Empty,Node(6,Empty,Empty)))
let bt_8 = Node(3,Node(1,Empty,Node(2,Empty,Node(2,Empty,Node(2,Empty,Empty)))),Node(5,Empty,Node(31,Node(18,Empty,Empty),Node(42,Empty,Empty))))

let b_test = Node(2,Node(2,Node(7,Empty,Empty),Empty),Node(4,Empty,Node(1,Empty,Empty)))


let rec lt_btree (t: 'a btree) (x:'a) : bool = 
  match t with 
    | Empty -> true
    | Node (a,g,d) -> (a<x) && (lt_btree g x) && (lt_btree d x)
;;

assert ((lt_btree bt_1 5)=true);;

let rec ge_btree (t: 'a btree) (x:'a) : bool = 
  match t with 
  | Empty -> true
  | Node (a,g,d) -> (a>=x) && (ge_btree g x) && (ge_btree d x)
;;

assert (( ge_btree bt_3 4)=true);;
assert (( ge_btree bt_4 4) = false);;
assert (( ge_btree Empty 5) = true);;



let rec is_abr (bt:'a btree) : bool =
  match bt with 
    | Empty -> true
    | Node (a,g,d) -> (ge_btree d a) && (lt_btree g a) && (is_abr g) && (is_abr d)
;;

assert ((is_abr Empty) = true);;
assert ((is_abr bt_5) = true);;
assert ((is_abr bt_6) = false);;
assert ((is_abr bt_7) = false);;


let rec mem (bt: 'a btree) (x:'a) : bool = 
  match bt with 
    | Empty -> false
    | Node (a,g,d) -> if (x=a) then true
      else if (a>x) then (mem g x)
        else (mem d x)  
;;
assert ((mem Empty 4) = false);;
assert ((mem bt_5 4) = true);;
assert ((mem bt_5 8) = false);;


assert ((mem b_test 1)=false);;
assert ((mem b_test 7)=false);;


let rec insert (bt : 'a btree) (x:'a) : 'a btree = 
  match bt with 
    | Empty -> Node (x, Empty, Empty)
    | Node (a,g,d) -> if (x>a) then  Node (a, g, (insert d x)) else Node (a, (insert g x), d)
;;

assert ((insert Empty 4) = Node (4, Empty, Empty));;
assert ((insert bt_5 3) = Node (5,Node (2, Node (1, Empty, Empty), Node (4, Node (3, Empty, Empty), Empty)),Node (6, Empty, Node (7, Empty, Empty))));;

let rec abr_of_list (l:'a list):'a btree = 
  match l with 
    | [] -> Empty
    | h::t -> insert (abr_of_list (t)) h
;;

assert ((abr_of_list [3;1;2;5;31;2;42;18;2]) = Node(3,Node (1, Empty, Node (2, Empty, Node (2, Empty, Node (2, Empty, Empty)))),Node(5, Empty, Node (31, Node (18, Empty, Empty), Node (42, Empty, Empty)))));;