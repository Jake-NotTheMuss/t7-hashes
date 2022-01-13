A repository for keeping track of hashes in T7 scripts.

src/ directory contains 2 programs, hash and log:
hash outputs the hash value for any strings passed in, for example './hash player_connected_time playerconnectedtime time_player_connected timeplayerconnected'
log writes any strings passed as arguments and their hashes to the file 'hashes.csv', for example './log player_connected_time timeplayerconnected'.

hashes.csv contains some strings that match hash values seen in the decompiled T7 scripts.
