let g (x:int) : int = 2 * x + 1;;

(fun x -> x + 1) (g 2);;
(fun x -> x + 2) (g 2);;
let f x = x + 1 in f (g (1 + 1)) ;;


List.assoc 3 [(1,2); (2,4); (3, 6)] = 3;;
List.assoc 3 [(1,2); (2,4); (3, 6)] = 6;;

List.assoc 3 (List.map (fun x -> (x,x)) [1; 2; 3]) = 3 ;;
List.assoc 3 (List.map (fun x -> (x,x - 1)) [1; 2; 3]) = 3;;

let x = (1,2) ;;
let y = (1,2,3) ;;

snd x;;
let (a,b) = x in a;;
let (a,b) = x in b;;

let (a, _, _) = (1,2,3) in a = 2 ;;
let (_, a, _) = (1,2,3) in a = 2 ;;
let (_, _, a) = (1,2,3) in a = 2 ;;
fst (('a', 'b'), 'c');;
