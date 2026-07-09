<?php
    $sandbox = '/www/sandbox/' . md5("orange" . $_SERVER['REMOTE_ADDR']);
    @mkdir($sandbox);
    @chdir($sandbox) or die("err?");
 
    $msg = @$_GET['msg'];
    if (isset($msg) && strlen($msg) <= 30) {
        usleep(random_int(133, 3337));

        $db = new SQLite3(".db");
        $db->exec(sprintf("
            CREATE TABLE msg (content TEXT);
            INSERT INTO msg VALUES('%s');
        ", $msg));
        $db->close();

        unlink(".db");
    } else if (isset($_GET['reset'])) {
        @exec('/bin/rm -rf ' . $sandbox);
    } else {
        highlight_file(__FILE__);
    }