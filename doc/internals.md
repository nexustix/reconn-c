# Internals - draft

## value stack
- stores values
- values can be of any type
- should only care about a single datatype (unsigned integers ?) by default (TBD)
- words have access to the value stack and can push/pop values

## execution stack
- stores words to be executed
- only stores words
- words have access to the execution stack and can push/pop words
- not for value storage (not even temporary)

## word buffer
- area where new words are assembled
- only stores words (for now)
- baking non-word values into words is not intended (yet)

## ? virtual stacks (TBD)
- used to send/receive work to/from other threads/workers (TBD)

## ? string buffers
- means to store bytestrings
- buffers have a given length and can contain null characters
- bytes inside of buffers can be accessed and modified by words
- rough analog to "screens" or "blocks"
- can be seen as in-memory files

## variables
- stores values
- doesn't care about type of the data
- basically just a generalized place to store and retrieve stuff
- value can be set
- value can be gotten
