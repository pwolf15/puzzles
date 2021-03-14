val x = [ 2, 8, 5 ]

fun printInt (x) = print (Int.toString(x))

val test = map printInt x

val logs = ["d2/","d2/","../","d21/","./"]
val logs2 = ["d1/","../","../","../"]
val logs3 = ["1/"]

fun min_operations([]) = 0
  | min_operations(x::xs) =
    if String.sub(x, 0) = #"." andalso String.sub(x, 1) = #"." then
      let 
        val result = min_operations(xs) 
      in
        if result < 0 then
          0
        else 
          result - 1
      end
    else if String.sub(x, 0) = #"." then
      min_operations(xs)
    else
      min_operations(xs) + 1
  