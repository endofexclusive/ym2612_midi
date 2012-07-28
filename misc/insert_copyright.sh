#!/bin/sh

for file in `find .. -name "*.[ch]"`
do
  if ! grep -q Copyright $file
  then
    cat copyright.txt $file >$file.new && mv $file.new $file
  fi
done

