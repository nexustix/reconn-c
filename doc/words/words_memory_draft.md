## memory



### copy ( destination:ptr source:ptr length:int -- )
### resize ( target:ptr size:int -- )
resize while preserving contents, non zeroed
### free ( :ptr -- )

### peek ( :ptr -- value:u8 )
retrieve octet at adress
### poke ( :ptr value:u8 -- )
set octet at adress

### reserve ( octet_count:int -- :ptr ) COMPILE
reserve given amount of space in memory
### creserve ( octet_count:int -- :ptr ) COMPILE
reserve given amount of cleared/zeroed space in memory