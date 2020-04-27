# Reconn words

This is a draft for potential words. Items marked with `?` are on shaky ground and might be removed from this draft; items makred with `✓` are implemented.

Stack effect notations are in format `( top second third ... nth -- top second third ... nth )` where "top" is the top of the stack, "second" is the second element on the stack, "third" is the third, etc.. The elements inside of the stack effect declarations are formatted like `name:type`, where "name" is the name of the value and "type" the type. The elements are seperated by whitespace. Seperated by `--` the left side of the declaration represents the state of the stack before execution of the word, and the right side the state of the stack after execution of said word.

### TODO

- logical shifts
- arithmetic shifts
- logical operations
- bitwise operations