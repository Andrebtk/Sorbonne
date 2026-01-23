let add (x : int) (y : int) : int = x + y ;;

let op (x:int) = -x ;;

(*
let foo l = 
  match l with 
    | [] -> 3 
    | x::y::z -> x + y;;


let foo l = 
  match l with
    | [x] :: [[x]] -> x > 0
    | _ -> false


let foo l = 
  match l with
    | [[x]] @ [[x]] -> x > 0
    | _ -> false;;

let foo l = 
  match l with
    | [[x]] @ [[y]] -> (x=y) && (x > 0)
    | _ -> false


let foo1 l = 
  match l with
    | [x] :: [[y]] -> (x=y) && (x > 0)
    | _ -> false;;


let foo7 l = 
  match l with 
    | [] -> true 
    | n :: _ -> n > 0 
    | _ -> false ;;


let rec foo8 l = 
  match l with 
    | [] -> [] 
    | e :: r -> e :: (foo8 r) ;;

let rec foo9 l = 
  match l with 
    | [] -> [] 
    | e :: r -> (foo9 r) ;;

let rec foo10 l = 
  match l with 
    | [] -> [] 
    | e :: r -> (foo10 (e :: r)) ;;

let foo4 l = 
  match l with 
  | [] -> 3 
  | x::y::z -> x + y ;;



let foo l = match l with 
  | n :: _ -> n > 0 
  | [] -> true 
  | _ -> false
*)

(List.map (fun x -> 2 * x) [1; 2; 3]) ;;
assert ( (List.map (fun x -> 2 * x) [1; 2; 3]) = [2; 4; 6]) ;;

(List.exists (fun x -> x = 0) [0; 1; 0]) ;;
(List.for_all (fun x -> x = 0) [0; 1; 0]) ;;


List.fold_left (fun x y -> x ^ y) "" ["a"; "b"; "c"] ;;

List.fold_right (fun x y -> x ^ y) ["a"; "b"; "c"] "" ;;