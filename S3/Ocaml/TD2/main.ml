let rec pgcd (n : int) (m : int) : int = 
	let r = (n mod m) in  
		if r=0 
			then m
			else (pgcd m r);;


assert ((pgcd 96 36) = 12) ;;
assert ((pgcd 36 96) = 12) ;;
assert ((pgcd 7 19) = 1) ;;

let rec repeat (n : int) (e : 'a) : 'a list = 
	if n=0
		then []
		else e::(repeat (n-1) e);;

assert ((repeat 0 'p') = []) ;;
assert ((repeat 4 'p') = ['p';'p';'p';'p';]) ;;

let rec all_in_list (l1 : 'a list) (l2 : 'a list) : bool =
	match l1 with
		| [] -> true
		| a::b -> 
			if (List.mem a l2) 
				then (all_in_list b l2)
				else false ;;

assert ((all_in_list [] [2; -1]) = true) ;;
assert ((all_in_list [-3; 8] [2; -3; -5; 8; -1]) = true) ;;
assert ((all_in_list [4; 8] []) = false) ;;
assert ((all_in_list [-3; 4; 8] [2; -3; -5; 8; -1]) = false) ;;

let rec range_inter (a : int) (b : int) : int list = 
	if a>b 
		then []
		else if (a-1)=b 
			then []
			else a::(range_inter (a+1) b) ;;

assert ((range_inter 7 2) = []) ;;
assert ((range_inter 2 7) = [2;3;4;5;6;7]) ;;
assert ((range_inter 2 2) = [2]) ;;

let rec map_cons (e : 'a) (l : 'a list list): 'a list list =
	match l with
		| [] -> []
		| a::b -> (e::a) :: (map_cons e b);;


assert ((map_cons 3 []) = []) ;;
assert ((map_cons 'x' [ [] ]) = [ ['x'] ]) ;;
assert ((map_cons true [ [true; false; false]; [false; true]; [] ]) = [ [true; true; false; false]; [true; false; true]; [true] ]) ;;

let rec is_prefix (l1 : 'a list) (l2 : 'a list) : bool = 
	match l1 with 
		| [] -> true
		| a::b ->
			match l2 with 
				| [] -> false
				| c::d -> 
						if a=c 
							then (is_prefix b d)
							else false ;;

assert ((is_prefix [] [1;2;3]) = true) ;;
assert ((is_prefix [1;2] [1;2;3;4;5]) = true);
assert ((is_prefix [1;2] [1;2]) = true) ;;
assert ((is_prefix [2;3] [1;2;3]) = false) ;;
assert ((is_prefix [1;2;3] [1;2]) = false) ;;

let rec prefixes (l : 'a list) : 'a list list =
	match l with 
		| [] -> [ [] ]
		| a::b -> []::(map_cons a (prefixes b));;

assert ((prefixes []) = [ [] ]) ;;
assert ((prefixes ['x']) = [ []; ['x'] ]) ;;
assert ((prefixes ['h'; 'o'; 'u'; 'x']) = [ []; ['h']; ['h'; 'o']; ['h'; 'o'; 'u']; ['h'; 'o'; 'u'; 'x'] ]) ;;
assert ((prefixes ['c'; 'h'; 'o'; 'u'; 'x']) = [ []; ['c']; ['c'; 'h']; ['c'; 'h'; 'o']; ['c'; 'h'; 'o'; 'u']; ['c'; 'h'; 'o'; 'u'; 'x'] ]) ;;

let rec all_prefix_in (l1 : 'a list) (l2 : 'a list list) : bool = 
	let prefL1 = (prefixes l1) in
	all_in_list prefL1 l2 ;;

assert ((all_prefix_in [1;0;0] [[];[0];[0;1];[1];[1;0];[1;0;0];[1;1];[1;1;0];[1;1;1]]) = true) ;;
assert ((all_prefix_in [1;0;0] [[];[0];[0;1];[1];[1;0;0];[1;1];[1;1;0];[1;1;1]]) = false) ;;