<?php

# Build all tables exclusive to this database 
function build_tables($db_location, $force_exit){

  $host_table_query = "create table test_post(post_text text not null);";
  create_table($db_location, 'test_post', $host_table_query, $force_exit);

}

function create_table($db_location, $table_name, $insert_query, $force_exit){

  # Check if the table exsists
  $check_table_query = sprintf("select name from sqlite_master where type='table' and name = '%s';", $table_name);
  $db = new SQLite3($db_location);
  $results = $db->query($check_table_query)->fetchArray();
  if($results != NULL)
    return True;# if table exsists

  # Create the table and run again to varify table exsists and return true
  if ($insert_query != NULL and $force_exit == False){
    $db->exec($insert_query);
    $db->close();
    return create_table($db_location, $table_name, $insert_query, $forece_exit);
  }

  return False;# if no table was created
}


# Start

# Check all needed data was included inside the upload reject if any are missing
/*
$keys = ['download','upload','ping', 'id', 'url', 'distance'];
foreach($keys as $key){
  if(!array_key_exists($key, $_POST)){
    echo "Invalid post data missing key:";
    echo $key;
    exit();
  }
}
 */

# Fetch data out of post request
$results = $_POST;
# $ping = json_decode($results['ping'], true);

# Build querys to insert data into database
$host_query = sprintf("insert into test_post(post_text)values('%s');", 
	               $results['test_post']);

# Insert the data into the database
$db_location = "/srv/databases/sst/test_post.db";
build_tables($db_location, false);
$db = new SQLite3($db_location);
$db->exec($host_query);
$db->close();

echo "Post successfull";
?>
