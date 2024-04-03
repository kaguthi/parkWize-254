<?php
// Read the variables sent via POST from our API
$sessionId   = $_POST["sessionId"];
$serviceCode = $_POST["serviceCode"];
$phoneNumber = $_POST["phoneNumber"];
$text        = $_POST["text"];
include "db.php";

if ($text == "") {
    // This is the first request. Note how we start the response with CON
    $response  = "CON Welcome to ParkWise 254 \n";
    $response .= "1. Create Account \n";
    $response .= "2. Log In";

} else if ($text == "1") {
    // Business logic for first level response
    $response = "CON Enter full Name \n";
    $add_user = "INSERT INTO users (user_id, name, gender) VALUES (NULL, $text, 'male')";
    $query = mysqli_query($connect, $add_user);
} else if ($text == "2") {
    // Business logic for first level response
    // This is a terminal request. Note how we start the response with END
    $response = "CON Choose your area \n";
    $response .= "1. Kinoo";

} else if ($text == "3") {
    $response = "CON Choose your area \n";
    $response .= "1. Nairobi CBD";
} else if($text == "3*1") { 

    // This is a terminal request. Note how we start the response with END
    $response = "CON Available parking slot \n";
    $response .= "1. moi avenue  50 Available \n";
    $response .= "2. Tom Mboya  20 Available";

} else if($text == "3*1*1"){
    $response = "END Welcome to Moi Avenue parking company";
} else if ($text == "3*1*2"){
    $response = "END Welcome to Tom Mboya parking company";
}

// Echo the response back to the API
header('Content-type: text/plain');
echo $response;