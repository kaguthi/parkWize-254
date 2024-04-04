<?php
// Read the variables sent via POST from our API
$sessionId   = $_POST["sessionId"];
$serviceCode = $_POST["serviceCode"];
$phoneNumber = $_POST["phoneNumber"];
$text        = $_POST["text"];
include "db.php";

if ($text == "") {
    $response  = "CON Welcome to ParkWise 254 \n";
    $response .= "1. Parking Management \n";
    $response .= "2. User park searching \n";
    $response .= "3. User parking";

} else if ($text == "1") {
    $response = "CON Parking Management \n";
    $response .= "1. Parking Manager to register parking site \n";
    $response .= "2. Parking Manager to open or close parking site"; 
} else if ($text == "2") {
    $response = "CON User park searching \n";
    $response .= "1. County name";

} else if ($text == "3") {
    $response = "CON User Parking \n";
    $response .= "1. Parking site \n";
    $response .= "2. Car plate number \n";
} else if($text == "1*1") { 
    $response = "CON Enter Parking site Name";
} else if($text == "1*2"){
    $response = "CON Searching for a parking near you";
} else if ($text == "1*3"){
    $response = "CON User Parking \n";
    $response .= "1. Parking site name \n";
} else if ($text == "1*1*") {
    $response = "END County name added successfully";
    $add_county = "INSERT INTO users (user_id, name, gender) VALUES (NULL, $text, 'female')";
    $query = mysqli_query($connect, $add_county);
}

header('Content-type: text/plain');
echo $response;