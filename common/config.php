<?php

session_start();

# CONSTANTS #
# ├ SITE
# └ AUTH

# Site
define ( 'ROOT', dirname( dirname( __FILE__ ) ) . '/' );
define ( 'COMPONENTS', 'components/' );
define ( 'VENDOR', ROOT . 'vendor/' );
define ( 'COMMON', ROOT . 'common/' );

# Auth
define( 'CLIENT_ID', '' );
define( 'CLIENT_SECRET', '' );
define( 'DEVELOPER_KEY', '' );
define( 'REDIRECT_URI', "http://{$_SERVER['HTTP_HOST']}" . strtok( $_SERVER['REQUEST_URI'], '?' ) );
define( 'APPLICATION_NAME', 'Analyzer' );
define( 'APPROVAL_PROMPT', 'force' );
define( 'ACCESS_TYPE', 'offline' );
$SCOPES = ['https://www.googleapis.com/auth/analytics.readonly'];



# REQUIRES #
# ├ LIBRARIES
# └ CONFIGS

# Libraries
require_once VENDOR . 'autoload.php';

# Configs
require_once COMMON . 'client.inc';
require_once COMMON . 'materialize-random-color.inc';