# Reconn words

This is a draft for potential words, items marked with `?` are on shaky ground and might be removed from this draft

Stack effect notations are in format `( top second third ... nth -- top second third ... nth )` where "top" is the top of the stack, "second" is the second element on the stack, "third" is the third, etc.. The elements inside of the stack effect declarations are formatted like `name:type`, where "name" is the name of the value and "type" the type. The elements are seperated by whitespace. Seperated by `--` the left side of the declaration represents the state of the stack before execution of the word, and the right side the state of the stack after execution of said word.

## core



### def
start word definition
### end
end word definition and put word into dictionary
### lambda
end word definition, put word into dictionary and put word name on the stack

### #enter ( :string -- ) 
enter namespace
### #leave ( -- ) 
revert to namespace before last #enter
### #namespace ( -- :string ) 
get complete namespace

### #plugin ( external_name:string internal_name:string -- success:int )
prepare plugin with given name and enable use as primary module
### #use ( module:string -- )
use primary module
### #useonly ( module:string word:string -- )
use single word from primary module
### #include ( :string -- ) 
include code from user module

### #words ( -- )
list all words
### #stack ( -- )
print current value stack
### #top ( -- )
print top element of stack

### #quote ( -- ) SPECIAL
put string name of next word on stack
### #do ( name:string -- ) 
execute word the given name refers to

### ? #break ( -- ) 
breakpoint, mostly (only ?) for debuggers - TBD

## base



### base ( :int -- )
set base input numbers are interpreted as
### hex ( -- )
set base to hexadecimal
### decimal ( -- )
set base to decimal
### octal ( -- )
set base to octal

## words



### forget ( :string -- )
forget (user defined ?) word
### rename ( :string -- )
rename word
### exists ( :int :string -- :int )
test if word exists
### ? lock ( :string -- )
prevent further execution of last word with given name
### ? lockall ( :string -- )
prevent further execution of all words with given name

## io



### key ( -- :int ) 
read single octet from stdin
### emit ( :int -- ) 
write single octet to stdout
### ? newline ( -- ) 
### ? cr ( -- )
### ? lf ( -- )

### print( :string -- )
write octets of string to stdout
### eprint( :string -- )
write octets of string to stderr
### println( :string -- )
write octets of string to stdout, adding newline
### eprintln( :string -- )
write octets of string to stderr, adding newline

### flush( -- )
flush stdout buffer
### eflush ( -- )
flush stderr buffer

### inputln( -- nread:int :string)
read line from stdin
### inputn ( max:int -- nread:int :string )
read stdin until reaching max octets or EOF

## memory



### copy ( destination:ptr source:ptr length:int -- )
### resize ( target:ptr size:int -- )
resize while preserving contents, non zeroed
### free ( :ptr -- )

### get ( :ptr -- value:? )
### set ( :ptr value:? -- )

### allot ( length:int -- :ptr ) COMPILE
allocate given amount of space in memory
### callot ( length:int -- :ptr ) COMPILE
allocate given amount of zeroed space in memory

## stack



### push
### pop
### swap
### over
### dup
### drop
### rot

## flow



### if
### when

## arithmetic



### +
### -
### *
### /
### %

## file (merge with io ?)



### open
### close
### write
### writeln
### read
### readln

## string



### split
### nth
### concat
### replace

## ? graphics (optional or plugin ?)



### screen
### line
### rectangle
### circle
### sprite
