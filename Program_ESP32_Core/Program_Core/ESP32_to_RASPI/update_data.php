<?php
$servername = "localhost";
$username = "wanda";
$password = "pasbatron";
$dbname = "database_ujicoba";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Get data from URL
$gpio32 = $_GET['gpio32'];
$gpio33 = $_GET['gpio33'];
$gpio25 = $_GET['gpio25'];
$gpio26 = $_GET['gpio26'];
$gpio27 = $_GET['gpio27'];
$gpio14 = $_GET['gpio14'];
$gpio12 = $_GET['gpio12'];

// Insert data into table
$sql = "INSERT INTO sensor_data (gpio32, gpio33, gpio25, gpio26, gpio27, gpio14, gpio12) VALUES ('$gpio32', '$gpio33', '$gpio25', '$gpio26', '$gpio27', '$gpio14', '$gpio12')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
