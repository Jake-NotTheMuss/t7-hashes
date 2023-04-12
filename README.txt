A repository for keeping track of hashes in T7 scripts.

The `src/' subdirectory contains 2 programs: `hash.c' and `log.c'.

`hash.c' outputs the FNV1A hash value for each string argument passed to
it.

`log.c' writes each string argument and their respective FNV1A hash
values to the file `hashes.csv'.

`hashes_augmented.csv' contains hashes for augmented variables
(variables generated in foreach loops when a key variable is not
specified).

`hashes_strings.csv' contains hashes of strings using the
sys::hashstring() function at compile-time (e.g. #"on_player_connect").

`hashes_ud.csv' contains hashes of campaign cheatcodes using the same
hash function as `Engine.UserData'
