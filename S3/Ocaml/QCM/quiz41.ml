type i_or_f = I of int | F of float

let test (x : i_or_f) : bool =
    match x with 
        | I 10 -> true 
        | F 8. -> false 
        | _ -> false


type 'a btree = Empty | Node of 'a * ('a btree) * ('a btree)

let rec f (x : 'a) (t : 'a btree) : bool = match t with
  | Empty -> false
  | Node (e,_,y) -> e=x || f x y

let t = Node (2, Node (1, Empty, Empty),Node (2, Node (3, Empty, Empty), Empty));;

f 3 t ;;
(*
let tes (x : i_or_f) : bool =
    match x with 
        | I 10 -> true 
        | F _ -> false 
        | I _ -> false 
        | I 9 -> true
*)

let sag (t : 'a btree) : 'a btree = match t with
   Empty -> raise (Invalid_argument "sag")
 | Node (e,g,d) -> g

let sad (t : 'a btree) : 'a btree = match t with
   Empty -> raise (Invalid_argument "sad")
 | Node (e,g,d) -> d


let t = Node (2, Node (1, Empty, Empty), Node (2, Node (3, Empty, Empty), Empty)) ;;

(sad (sag (sad t))) ;;