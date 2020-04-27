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