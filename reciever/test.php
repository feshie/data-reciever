<?php

ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(-1);

require_once("../db.inc.php");

$mysqli = new mysqli($__HOST, $__USERNAME, $__PASSWORD, $__DATABASE);

$query = "SELECT * FROM `unprocessed_data` WHERE `id`='0fda'";

  $result = $mysqli->query($query);
  $row = $result->fetch_array(MYSQLI_NUM);
  //{
    //foreach($row as $r)
    //  echo $r;
    
  //}

  header('Content-Type: x-application-protobuf');

  echo $row[2];

?>
