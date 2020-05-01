## list


### list ( -- ) COMPILE
create new list and add pointer to it into the compiled word
### lset ( :ptr index:int value:? -- )
set value of list element
### lget ( :ptr index:int -- value:? )
get value of list element
### ldel ( :ptr -- )
delete/free list