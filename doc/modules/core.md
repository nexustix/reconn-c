## core

### ✓ [
wipe compile buffer
enter compile mode
### ✓ ]
leave compile mode
### ✓ []
wipe compile buffer
### ✓ /[
enter compile mode
### ✓ def ( :string -- )
define new secondary word

### ✓ enter ( :string -- )
enter namespace
### ✓ leave
undo last namespace entering
### ? load ( :string -- )
dynamically load library
### use ( :string -- )
use primary module
### include ( :string -- )
include code from user module
### ✓ do ( :string -- )
run word by name
### words ( :string -- )
list registered words
### ✓ stack
print stack contents
### top
print first element on stack
### ? topn ( :int -- )
print n first elements on stack
### ✓ stop
stop execution
### ✓ nop
do nothing
### ✓ if ( :string :string :int -- )
### ✓ when ( :string :int -- )