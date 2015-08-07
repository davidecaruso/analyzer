<?php
require_once 'common/config.php';

if ( isset( $_GET['type'] ) && !empty( $_GET['type'] ) ) {
    $request = $_GET['type'];

    if ( isset( $_GET['accountId'] ) && !empty( $_GET['accountId'] ) ) {
        $accountId = $_GET['accountId'];

        if( $request == 'property' ) { # Cicla le webProperties collegate ad un account

            $props = $analytics->management_webproperties->listManagementWebproperties( $accountId );
            $items = $props->getItems();

            $webProperties = array();
            $i = 0;
            foreach ( $items as $key => $property ) {
                $webProperties [$i]['id'] = $property->id;
                $webProperties [$i]['name'] = $property->websiteUrl;
                $i++;
            }

            Dev_Tools::sort_array( $webProperties, 'name' );
            print json_encode( $webProperties );

        } else if ( $request == 'profile' ) { # Cicla le profileList collegate ad una webProperty

            $propertyId = isset( $_GET['propertyId'] ) && !empty( $_GET['propertyId'] ) ? $_GET['propertyId'] : null;

            $props = $analytics->management_profiles->listManagementProfiles( $accountId, $propertyId );
            $items = $props->getItems();


            $profilesList = array();

            $c = 0;
            foreach ( $items as $key => $property ) {
                $profilesList [$c]['id'] = $property->id;
                $profilesList [$c]['name'] = $property->name;
                $c++;
            }

            Dev_Tools::sort_array( $profilesList, 'name' );
            print json_encode( $profilesList );

        } else if ( $request == 'all' ) { # Cicla sia le profileList che le webProperties


            $props = $analytics->management_webproperties->listManagementWebproperties( $accountId );
            $items = $props->getItems();

            $webProperties = array();
            $k = 0;
            foreach ( $items as $key => $property ) {
                $webProperties [$k]['id'] = $property->id;
                $webProperties [$k]['name'] = $property->websiteUrl;
                $k++;
            }

            $propertyId = isset( $_GET['propertyId'] ) && !empty( $_GET['propertyId'] ) ? $_GET['propertyId'] : null;

            $props = $analytics->management_profiles->listManagementProfiles( $accountId, $propertyId );
            $items = $props->getItems();


            $profilesList = array();

            $j = 0;
            foreach ( $items as $key => $property ) {
                $profilesList [$j]['id'] = $property->id;
                $profilesList [$j]['name'] = $property->name;
                $j++;
            }


            $allProperties = array( 
                'webProperties' => $webProperties,
                'profilesList'  => $profilesList
            );

            Dev_Tools::sort_array( $webProperties, 'name' );
            Dev_Tools::sort_array( $profilesList, 'name' );
            print json_encode( $allProperties );
        }
    }
}