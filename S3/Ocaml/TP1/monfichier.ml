let rec sum_chiffres (n: int) : int = 
  if n=0 then 0 else (n mod 10) + (sum_chiffres (n/10));;

assert ((sum_chiffres 125) = 8) ;;

let rec nb_chiffres (n : int) : int = 
  if n=0 then 0 else 1 + (nb_chiffres (n/10)) ;;

assert ((nb_chiffres 125) = 3);;

let rec less_divider (i : int) (n : int) : int = 
  if (i=n) then 0
  else if (n mod i)=0 
    then i 
    else (less_divider (i+1) n);;
    
assert ((less_divider 2 19) = 0) ;;
assert ((less_divider 5 21) = 7) ;;
assert ((less_divider 7 21) = 7) ;;
assert ((less_divider 9 21) = 0) ;;

(* 1.2 2)  int->int->int *) 

let prime (n: int) : bool = 
  if n=1 
    then false
    else ((less_divider 2 n) = 0) ;;

assert ((prime 1) = false) ;;
assert ((prime 21) = false) ;;
assert ((prime 19) = true) ;;

let rec next_prime (n : int) : int = 
  if (prime n) 
    then n 
    else next_prime (n+1) ;;

assert ((next_prime 0) = 2) ;;
assert ((next_prime 15) = 17) ;;

let rec nth_prime (n : int) : int = 
  if n=0
    then 2
    else next_prime (nth_prime(n-1)+1) ;;


assert ((nth_prime 0) = 2) ;;
assert ((nth_prime 2) = 5) ;;
assert ((nth_prime 12) = 41) ;;
assert ((nth_prime 1) = 3) ;;
assert ((nth_prime 3) = 7) ;; 

let y = 6 ;; (* E1 *)
let foo (x : int) : int = x + y ;; 
(foo 4);; (* 10 *)
let y = 18 ;; (* E2*)
(foo 4) ;; (* 10  car comme foo a été defini dans E1, y sera toujours 6*)
