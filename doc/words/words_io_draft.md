## io (merge with file ?)



### key ( -- :int ) 
read single octet from stdin
### emit ( :int -- ) 
write single octet to stdout
### ? newline ( -- ) 
### ? cr ( -- )
### ? lf ( -- )

### ✓ print( :string -- )
write octets of string to stdout
### eprint( :string -- )
write octets of string to stderr
### ✓ println( :string -- )
write octets of string to stdout, adding newline
### eprintln( :string -- )
write octets of string to stderr, adding newline

### ✓ flush( -- )
flush stdout buffer
### eflush ( -- )
flush stderr buffer

### ✓ inputln( -- nread:int :string)
read line from stdin
### inputn ( max:int -- nread:int :string )
read stdin until reaching max octets or EOF