## core



### ✓ def
start word definition
### ✓ end
end word definition and put word into dictionary
### ✓ lambda
end word definition, put word into dictionary and put word name on the stack

### ✓ #enter ( :string -- ) 
enter namespace
### ✓ #leave ( -- ) 
revert to namespace before last #enter
### #namespace ( -- :string ) 
get complete namespace

### #plugin ( external_name:string internal_name:string -- success:int )
prepare plugin with given name and enable use as primary module
### ✓ #use ( module:string -- )
use primary module
### #useonly ( module:string word:string -- )
use single word from primary module
### ✓ #include ( :string -- ) 
include code from user module
### #quote ( -- ) SPECIAL
put string name of next word on stack
### ✓ #do ( name:string -- ) 
execute word the given name refers to

### ? #words ( -- ) (move to debug ?)
list all words
### ? #stack ( -- ) (move to debug ?)
print current value stack
### ? #top ( -- ) (move to debug ?)
print top element of stack

### ? #break ( -- ) 
breakpoint, mostly (only ?) for debuggers - TBD