#!/bin/sh

removedupes(){
    tempfile=$(mktemp $1.XXXXXX)
    awk "
        {
            numseen = lines[\$0]++;
            # If this is a duplicate line and
            # it has not been counted, add it
            # to the list of dupes
            if (numseen == 1)
                dupes[count++]=\$0;
            # if it is not a dupe print it
            else if (numseen == 0)
                print > \"$tempfile\";
        }
        END {
            if (count > 0)
            {
                print \"Duplicates found\n---\";
                for(i in dupes)
                    { print dupes[i]; }
                print \"---\";
            }
            else
            {
                print \"No duplicates found\";
            }
        }" $1
    mv -f -- $tempfile $1
}

while test -n "$1"; do
    removedupes $1
    shift
done
