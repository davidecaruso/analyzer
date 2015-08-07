<?php

# Parameters
$account_get    = isset( $_GET['account'] )     && !empty( $_GET['account'] )       ? $_GET['account']      : ''; # Account ID
$property_get   = isset( $_GET['property'] )    && !empty( $_GET['property'] )      ? $_GET['property']     : ''; # Property ID
$profile_get    = isset( $_GET['profile'] )     && !empty( $_GET['profile'] )       ? $_GET['profile']      : ''; # Profile ID
$from_get_label = isset( $_GET['from'] )        && !empty( $_GET['from'] )          ? $_GET['from']         : ''; # From label ( 1 January, 1980 )
$to_get_label   = isset( $_GET['to'] )          && !empty( $_GET['to'] )            ? $_GET['to']           : ''; # To label ( 25 December, 1980 )
$from_get       = isset( $_GET['from_submit'] ) && !empty( $_GET['from_submit'] )   ? $_GET['from_submit']  : ''; # From value ( 15-01-01 )
$to_get         = isset( $_GET['to_submit'] )   && !empty( $_GET['to_submit'] )     ? $_GET['to_submit']    : ''; # To value ( 15-12-25 )
$submit         = isset( $_GET['submit'] )                                          ? $_GET['submit']       : ''; # Submit button

# If form was submitted
$submitted = ( bool ) ( $account_get && $property_get && $profile_get && $from_get && $to_get );

# If form was submitted, we can build a permalink and redirect to it
$permalink = '?_=_';
if ( $submitted ) {

    foreach ( $_GET as $key => $value ) {

        if ( $key != 'submit' )
            $permalink .= "&{$key}={$value}";
        else
            continue;

    }

}

# 1. Creating Client Object
$client = new Google_Client();
$client->setApplicationName( APPLICATION_NAME );

# 2. Client ID, secret and key is taken from API Console
$client->setClientId( CLIENT_ID );
$client->setClientSecret( CLIENT_SECRET );
$client->setDeveloperKey( DEVELOPER_KEY );
$client->setRedirectUri( REDIRECT_URI );
$client->setScopes( $SCOPES );
$client->setAccessType( ACCESS_TYPE );

# 3. Create Analytics object
$analytics = new Google_Service_Analytics( $client );

# 4. If url contains logout query string, clear session
if ( isset( $_GET['logout'] ) ) {
    session_destroy();
    Dev_Tools::redirect( filter_var( REDIRECT_URI, FILTER_SANITIZE_URL ) );
}

# 5. Reading code to authenticate
if ( isset( $_GET['code'] ) ) {

    $client->authenticate( $_GET['code'] );
    $_SESSION['access_token'] = $client->getAccessToken();
    Dev_Tools::redirect( filter_var( REDIRECT_URI . $permalink, FILTER_SANITIZE_URL ) );

}

# 6. Setting Access Token
if ( isset( $_SESSION['access_token'] ) ) $client->setAccessToken( $_SESSION['access_token'] );

$logged = ( bool ) $client->getAccessToken();
$authUrl = $client->createAuthUrl();