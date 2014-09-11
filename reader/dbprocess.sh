#!/bin/bash

echo 'SELECT * FROM `unprocessed_data` WHERE id > ( (SELECT MAX(id) FROM unprocessed_data ) -10)' |
  mysql -udjap1g11 -papplebanana --skip-column-names feshie |
  while read row
  do
    id=`echo $row | cut -f 1 -d" "`
    timestamp=`echo $row | cut -f 2-3 -d" "`
    data=`echo $row | cut -f 4 -d" "`

#    echo "ID = $id"
#    echo "Timestamp = $timestamp"
#    echo "Data = $data"

    filename=`mktemp`
    echo -n $data | xxd -r -p - $filename

    ./reader $filename

    echo "-------------------------------------"
  done
