# "Cursed" Tests

These programs test a few things via cursed implementations of a basic program that, given an integer i, prints: 
* Never if i is zero, 
* Once if i is one, 
* Twice if i is two, 
* Thrice if i is three,
* or ith otherwise. 

These programs can be thought of testing a few things, however, specifically, they introduce tests for **binary operators** that were previously untested. 

They also test that (aside from the name of the file/module), `return` can be removed from functions that return a `Unit` without any impact on the generated code or semantics (TODO: test that this is the case even with branches where we may rely on a branch ending in return to help perform type checking).

Finally, they test that the following function type checks.
```bismuth
define func sil_sel_array(int i) : int {
    var arr := [0, 1, 2, 3]; 
    select {
        i < 4: match arr[i] 
                | int s => return s; 
                | Unit u => return -1; 
        true: return i;
    }
}
```
This ensures against an error that used to be raised that would report `(Unit + Var)` is not able to act as an `int` for the match statement. 