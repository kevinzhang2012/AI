 * `node.hpp`
```cpp
Node
{ state, path }
```
 * default_cost_func.hpp
```cpp
DefaultCostFunc (node) -> node.path.size() 
```
 * priority_queue.hpp
```cpp
 Using pseudocodes from "Introduction to Algorithms 3rd edition" aka C.L.R.S.
```
 * time_record.hpp
```cpp
//a timer implemented with RAII style
TimeRecord
{
  constructor(reference)
    start timer
  
  destructor()
    stop timer
    write time duration to outside by reference 
}
```
 * heuristic_func.hpp
```cpp
ManhattanDistance (curr, goal)
  ret = 0
  for i = 0 to length(goal) - 1
    if ('0' != curr[i])
      digit = curr[i] - '0'
      ret += abs(i / 3 - digit / 3) + abs(i % 3 - digit % 3)
  return ret
  
MisplacedTiles (curr, goal)
  count = 0
  for i = 0 to length(goal) - 1
    if (curr[i] != goal[i]) 
       count = count + 1
  return count
```
 * function_dictionary.hpp
```cpp
//this class implmented a function dictionary mapping each position of `0` to its possible children state.
FunctionDictionary 
{
  constructor()
    fill_dictionary()
    
  fill_dictionary()
    lambda : u(position) -> position - 3
    lambda : d(position) -> position + 3
    lambda : l(position) -> position - 1
    lambda : r(position) -> position + 1
    
    lambda : make_child(parent, move_lambda, direction)
      pos = state(parent).find('0')
      stt = state(parent)
      swap(stt[pos], stt[move_lambda(pos)])
      return Node(stt, path(parent) + direction)
    
    lambda : up(parent) -> make_child(parent, u, 'U')
    lambda : dw(parent) -> make_child(parent, d, 'D')
    lambda : lt(parent) -> make_child(parent, l, 'L')
    lambda : rt(parent) -> make_child(parent, r, 'R')
    
    this[0] = LambdaList{ dw, rt }
    this[2] = LambdaList{ dw, lt }
    this[6] = LambdaList{ up, rt }
    this[8] = LambdaList{ up, lt }
    this[1] = LambdaList{ dw, lt, rt }
    this[3] = LambdaList{ up, dw, rt }
    this[5] = LambdaList{ up, dw, lt };
    this[7] = LambdaList{ up, lt, rt };
    this[4] = LambdaList{ up, dw, lt, rt };
}
```
 