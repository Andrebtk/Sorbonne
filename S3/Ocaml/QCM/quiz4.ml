type couleur = Vert | Orange | Rouge;;

let next (x : couleur) : couleur =
  match x with
    | Vert -> Orange
    | Orange -> Rouge
    | Rouge -> Vert
;;

type nombre = Entier of int | Flottant of float 

let float_of_nombre (n : nombre) : float =
  match n with 
    | Entier x -> float_of_int x
    | Flottant y -> y
;;

type 'a option = None | Some of 'a ;;

let nombre_to_int (n : nombre) : int option =
  match n with
    | Entier x -> Some x
    | _ -> None
;;

type 'a btree = Empty | Node of 'a * ('a btree) * ('a btree);;

let t =
    Node(5,Node(3,
      Node(4,Empty,Empty),
      Node(5,Empty,Empty)),
     Node(2,
      Node(1,
        Empty,
        Node(7,Empty,Empty)),
      Empty));;


let label_root (t : 'a btree) : 'a = 
  match t with 
    | Empty -> raise (Invalid_argument "label_root")
    | Node (e,g,d) -> e
;;

let sag (t: 'a btree) : 'a btree = 
  match t with 
    | Empty -> raise (Invalid_argument "sag")
    | Node (e,g,d) -> g
;;

let sad (t: 'a btree) : 'a btree = 
  match t with 
    | Empty -> raise (Invalid_argument "sag")
    | Node (e,g,d) -> d
;;

let rec height (t : 'a btree) : int =
  match t with 
    | Empty -> 0
    | Node (e,g,d) -> 1 + (max (height g) (height d))
;;

let rec mem (t : 'a btree) (x : 'a) : bool =
  match t with 
    | Empty -> false
    | Node (e,g,d) -> e=x || (mem g x) || (mem d x)
;;


let rec pref (t : 'a btree) : 'a list =
  match t with 
    | Empty -> []
    | Node (e,g,d) -> e::((pref g) @ (pref d))
;;

let t2 = Node (1, Node (2, Empty, Empty), Node (3, Empty, Empty)) ;;

type i_or_f = I of int | F of float ;;

match x with Invalid_argument