<?php

ini_set('display_errors',1);
ini_set('display_startup_errors',1);
ini_set('always_populate_raw_post_data',true);
error_reporting(-1);

require_once("../db.inc.php");


// From http://stackoverflow.com/questions/444966/working-with-ipv6-addresses-in-php
function ExpandIPv6Notation($Ip) {
    if (strpos($Ip, '::') !== false)
        $Ip = str_replace('::', str_repeat(':0', 8 - substr_count($Ip, ':')).':', $Ip);
    if (strpos($Ip, ':') === 0) $Ip = '0'.$Ip;
    return $Ip;
}

function lastIPv6Group($ipv6) {
        # Check the address is valid
        if(!preg_match('/^(((?=.*(::))(?!.*\3.+\3))\3?|([\dA-F]{1,4}(\3|:\b|$)|\2))(?4){5}((?4){2}|(((2[0-4]|1\d|[1-9])?\d|25[0-5])\.?\b){4})\z/i', $ipv6))
                return false;
        $ipv6_long = ExpandIPv6Notation($ipv6);
        $tokens = explode(":", $ipv6_long);
        return str_pad($tokens[7], 4, "0", STR_PAD_LEFT);
}

//echo $_GET["ip"];

$mysqli = new mysqli($__HOST, $__USERNAME, $__PASSWORD, $__DATABASE);

if($mysqli->connect_errno) {
        header("HTTP/1.0 501");
        echo "Unable to connect to database server";
        exit();
}

$id = lastIPv6Group($_GET["ip"]);
if(!$id) {
        header("HTTP/1.0 502");
        echo "Invalid IPv6 address";
        exit();
}
$timestamp = time();

$contents = file_get_contents('php://input');//$HTTP_RAW_POST_DATA;

$stmt = $mysqli->prepare(
        "INSERT INTO `test_unprocessed_data`
        (`device_id`, `timestamp`, `data`)
        VALUES (?, FROM_UNIXTIME(?), ?)");

$stmt->bind_param("sis", $id, $timestamp, $contents);
$stmt->execute();
$stmt->close();

?>

