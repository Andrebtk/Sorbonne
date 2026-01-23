let tab = 1::(2::(3::[]));;

let is_empty (l : 'a list) = 
  match l with 
    | [] -> true
    | h::t -> false ;;
    
let rec sum_l (l : 'a list) = 
  match l with 
    | [] -> 0
    | h::t -> h + (sum_l t);;
   

let head (l : 'a list) = 
  match l with 
    | [] -> raise (Invalid_argument "empty list")
    | h::t -> h ;;

let rec add_end (x : 'a) (l : 'a list) : 'a list = 
  match l with 
    | [] -> [x]
    | h::t -> h::(add_end x t) ;;

let rec add_start (x : 'a) (l : 'a list) : 'a list = x :: l ;;

let rec length (l : 'a list) : int = 
  match l with 
    | [] -> 0
    | h::t -> 1 + (lenght t) ;;

let rec mem (e : 'a) (l : 'a list) : bool =
  match l with 
    | [] -> false
    | h::t -> if h=e then true else (mem e t) ;;
