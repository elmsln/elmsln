<html>
<head>
  <title>HAXcms Installation</title>
</head>
<body>
<?php
// check for core directories existing, redirect if we do
if (is_dir('_sites') && is_dir('_config') && is_dir('_published') && is_dir('_archived')) {
    header("Location: index.php");
    exit();
} else {
  include_once 'system/lib/Git.php';
  // add git library
  if (!is_dir('_config')) {
    // gotta config some place now don't we
    if (!mkdir('_config')) {
      print "
    <h1>Install issues</h1>
    <p>You need to give write access to the haxcms directory to be installed or
    if you can run commands from the server itself, run this command: <strong>bash " . __DIR__ . "/scripts/haxtheweb.sh</strong></p>
  </body>
</html>";
      exit();
    }
    // place for the ssh key chain specific to haxcms if desired
    mkdir('_config/.ssh');
    // tmp directory for uploads and other file management
    mkdir('_config/tmp');
    // node modules for local theme development if desired
    mkdir('_config/node_modules');
    // make config.json boilerplate
    copy(
      'system/boilerplate/systemsetup/config.json',
      '_config/config.json'
    );
    // make a file to do custom theme development in
    copy(
      'system/boilerplate/systemsetup/my-custom-elements.js',
      '_config/my-custom-elements.js'
    );
    // make a config.php boilerplate for larger overrides
    copy('system/boilerplate/systemsetup/config.php', '_config/config.php');
    // htaccess file
    copy('system/boilerplate/systemsetup/.htaccess', '_config/.htaccess');
    // set permissions
    chmod("_config", 0755);
    chmod("_config/tmp", 0777);
    chmod("_config/config.json", 0777);
    // set SALT
    file_put_contents(
      '_config/SALT.txt',
      uniqid() . '-' . uniqid() . '-' . uniqid() . '-' . uniqid()
    );
    // set things in config file from the norm
    $configFile = file_get_contents('_config/config.php');
    // private key
    $configFile = str_replace(
      'HAXTHEWEBPRIVATEKEY',
      uniqid() . '-' . uniqid() . '-' . uniqid() . '-' . uniqid(),
      $configFile
    );
    // user
    if(isset($_POST['user'])){
      $configFile = str_replace('jeff', $_POST['user'], $configFile);
    }
    else{
      $configFile = str_replace('jeff', 'admin', $configFile);
    }
    // support POST for password in this setup phase
    // this is typial of hosting environments that need
    // to see the login details ahead of time in order
    // to set things up correctly
    if(isset($_POST['pass'])){
      $pass = $_POST['pass'];
    }
    else {
      // pass
      $alphabet =
          'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789';
      $pass = array(); //remember to declare $pass as an array
      $alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
      for ($i = 0; $i < 12; $i++) {
          $n = rand(0, $alphaLength);
          $pass[] = $alphabet[$n];
      }
      $pass = implode($pass);
    }
    $configFile = str_replace('jimmerson', $pass, $configFile);
    // work on base path relative to where this was just launched from
    // super sneaky and locks it to where it's currently installed but required
    // or we don't know where to look for anything
    $basePath = str_replace('install.php', '', $_SERVER['SCRIPT_NAME']); 
    $configFile = str_replace("->basePath = '/'", "->basePath = '$basePath'", $configFile);
    file_put_contents('_config/config.php', $configFile);
    $git = new Git();
    $git->create('_config');
  }
  if (!is_dir('_sites')) {
    // make sites directory
    mkdir('_sites');
    chmod("_sites", 0777);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_sites', get_current_user());
    @chgrp('_sites', get_current_user());
    $git = new Git();
    $git->create('_sites');
  }
  if (!is_dir('_published')) {
    // make published directory so you can have a copy of these files
    mkdir('_published');
    chmod("_published", 0775);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_published', get_current_user());
    @chgrp('_published', get_current_user());
  }
  if (!is_dir('_archived')) {
    // make published directory so you can have a copy of these files
    mkdir('_archived');
    chmod("_archived", 0775);
    // attempt to set the user / group on sites
    // these probaly won't work
    @chown('_archived', get_current_user());
    @chgrp('_archived', get_current_user());
  }
} ?>
  <h1>Welcome to the decentralization</h1>
  <pre>
  <?php
  print "║                Welcome to the decentralization.               ║" .
      "\n";
  print "║                                                               ║" .
      "\n";
  print "║     H  H      AAA     X   X     CCC      M   M     SSSS       ║" .
      "\n";
  print "║     H  H     A   A     X X     C   C    M M M M   S           ║" .
      "\n";
  print "║     HHHH     AAAAA      X      C        M  M  M    SSSS       ║" .
      "\n";
  print "║     H  H     A   A     X X     C   C    M     M        S      ║" .
      "\n";
  print "║     H  H     A   A    X   X     CCC     M     M    SSSS       ║" .
      "\n";
  print "║                                                               ║" .
      "\n";
  print "╟───────────────────────────────────────────────────────────────╢" .
      "\n";
  print "║ If you have issues, submit them to                            ║" .
      "\n";
  print "║   http://github.com/elmsln/haxcms/issues                      ║" .
      "\n";
  print "╟───────────────────────────────────────────────────────────────╢" .
      "\n";
  print "║ ✻NOTES✻                                                       ║" .
      "\n";
  print "║ All changes should be made in the _config/config.php file     ║" .
      "\n";
  print "║ which has been setup during this install routine              ║" .
      "\n";
  print "║                                                               ║" .
      "\n";
  print "╠───────────────────────────────────────────────────────────────╣" .
      "\n";
  print "║ Use  the following to get started:                            ║" .
      "\n";
  print "║                                                               ║" .
      "\n";
  print "║    user name:    admin                                        ║" .
      "\n";
  print "║    password:     $pass                                     ║" . "\n";
  print "║                                                               ║" .
      "\n";
  print "║    To change these values edit them in _config/config.php     ║" .
      "\n";
  print "║                        ✻ Ex  Uno Plures ✻                    ║" .
      "\n";
  print "║                        ✻ From one, Many ✻                    ║" .
      "\n";
  ?>
  </pre>
  <p style="font-size:40px;"><a href="index.php">Click here to access your HAXcms site mananger!</a></p>
</body>
</html>