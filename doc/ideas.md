ideas for potential alterations or improvements

- treat the "vm" more like a word "assembly line"

- let secondary words be more self contained

- get rid of all the silly amounts of strings everywhere, strings are terrible
- multiple stacks ? ( would probably be a mess word wise ) ( might hook into multithreading ? ) ( reduces elegance )
- make stack more homogenous
- make stack contain only unsigned integers ?
- hijack the idea of "blocks" to store and retrieve strings ( in memory, because modern machines have a silly amount of it )
  - hijack the idea of the "editor" to manipulate strings contained in "blocks"
  - allow creation of "blocks" larger that 1 MiB ( otherwise huge strings would need multiple "blocks" to be represented, which would be annoying )
  - might as well call them "buffers" and fully lean into the editor side of things
  - decide if "buffers"/"blocks" should have width and height ( useful for storing bitmaps ), or only a 1D index
    - maybe just keep the buffer itself 1D and add utillity words for extra dimensions. like 2D for bitmaps, 3D for voxel data, 4D for layered voxel data, etc.
  - decice if "buffers"/"blocks" should grow dynamically or should be resized manually
- create a custom POD datatype to contain integer data
- let the stack contain only octets and add some axillary representation of what those octets might mean and how many octets are one element
  - allows stack to hold arbitrary data while still allowing it to be represated as one chunk, whithout having to follow pointers
  - words can/might ignore the datatype of objects, which might be good/bad
  - stack operations can still be used on chunks of differing sizes, without messing up data
  - ! stack elements having arbirary size makes it harder to treat elements in a generic function
    - elements stored on stack might need a size restriction or a way to make their size easily apparent
- add debug mode or flag to "vm"
  - allow program to enter debug mode with advanced logging and/or typechecking ( if aplicable )
  - allow program to skip unessesary safety checks to improve performance ( if desired )
- make VM light enough to allow running multiple of them in paralell or create a master and a worker implementation
- add something like  go- or co-routines ( channels ? ) ( out of scope of project ? )