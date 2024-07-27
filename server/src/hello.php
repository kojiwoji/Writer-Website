<html>
<body>

<form method="POST" action="<?php echo $_SERVER['PHP_SELF'];?>">
</form>
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $Json = file_get_contents('data.json');
    echo $Json;

}
?>

</body>
</html>
