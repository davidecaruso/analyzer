<?php
require_once 'common/config.php';

$result = null;

if( $submitted ) {

    # It contains the unique id of the site
    $projectId = $profile_get;

    # It contains the start date
    $from = $from_get;

    # It contains the end date
    $to = $to_get;

    # Params (metrics)
    $_params[] = 'Sessions';
    $_params[] = 'Users';
    $_params[] = 'Pageviews';
    $_params[] = 'Pages / Session';
    $_params[] = 'Avg. Session Duration';
    $_params[] = 'Bounce Rate';
    $_params[] = '% New Sessions';

    /*
    # Params (dimensions)
    $_params[] = 'date';
    $_params[] = 'date_year';
    $_params[] = 'date_month';
    $_params[] = 'date_day';
    */

    # Metrics
    $metrics = 'ga:sessions,ga:users,ga:pageviews,ga:pageviewsPerSession,ga:avgSessionDuration,ga:visitBounceRate,ga:percentNewVisits';
    //$dimensions = 'ga:date,ga:year,ga:month,ga:day';

    # Run query, run!
    $data = $analytics->data_ga->get( 'ga:' . $projectId, $from, $to, $metrics );
    $data_graph = $analytics->data_ga->get( 'ga:' . $projectId, $from, $to, 'ga:sessions,ga:pageviews', array('dimensions' => 'ga:date,ga:year,ga:month,ga:day'));

    # Results number
    $totalResult = $data->totalResults;

    # Report
    $result = $data->totalsForAllResults;

    # Change format from s to H:i:s and the number forma of decimals
    $result['ga:avgSessionDuration']    = gmdate("H:i:s", ceil($result['ga:avgSessionDuration']));
    $result['ga:sessions']              = str_replace(',', '.', number_format($result['ga:sessions']));
    $result['ga:users']                 = str_replace(',', '.', number_format($result['ga:users']));
    $result['ga:pageviews']             = str_replace(',', '.', number_format($result['ga:pageviews']));
    $result['ga:pageviewsPerSession']   = number_format($result['ga:pageviewsPerSession'], 2, ',', '');
    $result['ga:visitBounceRate']       = number_format($result['ga:visitBounceRate'], 2, ',', '') . '%';
    $result['ga:percentNewVisits']      = number_format($result['ga:percentNewVisits'], 2, ',', '') . '%';

}

?>
<!DOCTYPE html>
<html>
<head>

    <? # Meta tags ?>
    <meta charset="UTF-8">
    <title>Analyzer</title>

    <? # Icon & theme ?>
    <link rel="apple-touch-icon" sizes="57x57" href="apple-icon-57x57.png" />
    <link rel="apple-touch-icon" sizes="60x60" href="apple-icon-60x60.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="apple-icon-72x72.png" />
    <link rel="apple-touch-icon" sizes="76x76" href="apple-icon-76x76.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="apple-icon-114x114.png" />
    <link rel="apple-touch-icon" sizes="120x120" href="apple-icon-120x120.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="apple-icon-144x144.png" />
    <link rel="apple-touch-icon" sizes="152x152" href="apple-icon-152x152.png" />
    <link rel="apple-touch-icon" sizes="180x180" href="apple-icon-180x180.png" />
    <link rel="icon" type="image/png" sizes="192x192"  href="android-icon-192x192.png" />
    <link rel="icon" type="image/png" sizes="32x32" href="favicon-32x32.png" />
    <link rel="icon" type="image/png" sizes="96x96" href="favicon-96x96.png" />
    <link rel="icon" type="image/png" sizes="16x16" href="favicon-16x16.png" />
    <link rel="manifest" href="manifest.json" />
    <meta name="msapplication-TileColor" content="#039BE5" />
    <meta name="msapplication-TileImage" content="ms-icon-144x144.png" />
    <meta name="theme-color" content="#039BE5" />

    <? # Styles ?>
    <link href="http://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet" />
    <link type="text/css" rel="stylesheet" href="<?= COMPONENTS ?>materialize/dist/css/materialize.min.css"  media="screen,projection" />
    <link type="text/css" rel="stylesheet" href="style.css" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />

</head>
<body>

<? require_once COMMON . 'header.inc' # Header ?>

<? if ( !$logged ) { # User not logged ?>
    <div class="center section login-section">
        <a href="<?= $authUrl ?>" class="btn-floating btn-large waves-effect waves-light <?= $_color ?>" title="Log in"><i class="material-icons">person</i></a>
        <p>Get horny with your Google Analytics account</p>
    </div>
<? } else { # User logged ?>
    <div class="container">
        <?
        # Reading all account
        $props = $analytics->management_accounts->listManagementAccounts();
        $items = $props->getItems();

        $accounts_list = array();

        $i = 0;
        foreach ( $items as $key => $property ) {
            $accounts_list[$i]['id'] = $property->id;
            $accounts_list[$i]['name'] = $property->name;
            $i++;
        }

        if( !empty( $items ) ) { ?>
            <div class="section form-section <?= $submitted ? 'submitted' : null ?>">
                <div class="card hoverable">
                    <div class="<?= $submitted ? 'card-reveal' : 'card-content' ?>">
                        <? if( $submitted ) { ?>
                            <a href="javascript: jQuery('.form-section .card').toggleClass('big');" class="card-title light <?= $_color ?>-text">&nbsp;<i class="material-icons right">close</i></a>
                        <? } ?>
                        <div class="row">
                            <form class="col s12" action="?" method="get">

                                <div class="row">
                                    <h5 class="light <?= $_color ?>-text">Choose site</h5>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <select name="account" id="account">
                                            <option value="" disabled selected>Choose account</option>
                                            <? foreach ($accounts_list as $account) { $selected = $account['id'] == $account_get ? 'selected' : ''; ?>
                                                <option value="<?= $account['id'] ?>" <?= $selected ?>><?= $account['name'] ?></option>
                                            <? } ?>
                                        </select>
                                        <label for="account">Account</label>
                                    </div>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <select name="property" id="property" disabled>
                                            <option value="" disabled selected>Choose webproperty</option>
                                        </select>
                                        <label for="property">Webproperty</label>
                                    </div>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <select name="profile" id="profile" disabled>
                                            <option value="" disabled selected>Choose profile</option>
                                        </select>
                                        <label for="profile">Profile</label>
                                    </div>
                                </div>

                                <div class="row">
                                    <h5 class="light <?= $_color ?>-text">Choose date</h5>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <label for="from">From</label>
                                        <input type="date" name="from" id="from" class="datepicker" value="<?= $from_get_label ? $from_get_label : '' ?>" />
                                    </div>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <label for="to">To</label>
                                        <input type="date" name="to" id="to" class="datepicker" value="<?= $to_get_label ? $to_get_label : '' ?>" />
                                    </div>
                                </div>

                                <div class="row">
                                    <div class="input-field col s12">
                                        <button class="btn-large red waves-effect waves-light" type="reset" name="reset" id="reset" onclick="javascript: window.location.href='./'; return;">Clear</button>
                                        <button class="btn-large <?= $_color ?> waves-effect waves-light" type="submit" name="submit" id="submit">Submit</button>
                                    </div>
                                </div>
                            </form>
                        </div>
                    </div>
                    <? if ( $submitted ) { ?>
                        <div class="card-content">
                            <a href="javascript: jQuery('.form-section .card').toggleClass('big');" class="activator card-title light <?= $_color ?>-text">Change filters <i class="material-icons right">more_vert</i></a>
                        </div>
                    <? } ?>
                </div>
            </div>

            <? if( $submitted && $result ) { ?>
                <div class="section result-section">

                    <div class="row result-header">
                        <blockquote class="col s12 m12 l12 gray-text">
                            <?= str_replace( '-', '/', $from_get ) ?> - <?= str_replace( '-', '/', $to_get ) ?>
                        </blockquote>
                    </div>

                    <div class="row">
                        <div class="col s12 m12 l12">
                            <canvas id="canvas" height="150" width="400" style="width: 100%;"></canvas>
                        </div>
                    </div>
                    <div class="row">
                        <div class="col s12 m12 l12">
                            <table class="hoverable">
                                <thead>
                                    <tr>
                                        <th data-field="field">Field</th>
                                        <th data-field="value">Value</th>
                                    </tr>
                                </thead>
                                <tbody>
                                    <?
                                    $i = 0;
                                    foreach($result as $key => $value) {

                                        ?>
                                        <tr>
                                            <td><?= $_params[$i] ?>:</td>
                                            <td><strong><?= $value ?></strong></td>
                                        </tr>
                                        <?
                                        $i++;

                                    }
                                    ?>
                                </tbody>
                            </table>

                        </div>
                        <? /** CHART
                        <div class="col s12 m12 l4">
                            <div class="row">
                                <div class="col s12 m12 l12">
                                    <canvas id="canvas" height="200" width="200"></canvas>
                                </div>
                            </div>
                            <div class="row">
                                <div class="col s12 m12 l12">
                                    <p class="return_visits"><span></span>Returning Visitors <b><?= number_format(100-$result['ga:percentNewVisits'], 2, ',', '') ?>%</b></p>
                                    <p class="new_visits"><span></span>News Visitors <b><?= str_replace('.', ',', $result['ga:percentNewVisits']) ?>%</b></p>
                                </div>
                            </div>
                        </div>
                        */ ?>
                    </div>
                </div>
            <? } ?>

        <? } else { ?><p class="flow-text">No reports available.</p> <? } ?>
    </div>
<? } ?>

<? # Scripts ?>
<script src="<?= COMPONENTS ?>jquery/dist/jquery.js"></script>
<script src="<?= COMPONENTS ?>jquery-ui/jquery-ui.js"></script>
<script src="<?= COMPONENTS ?>chartjs/Chart.js"></script>
<script type="text/javascript" src="<?= COMPONENTS ?>/materialize/dist/js/materialize.min.js"></script>
<script type="text/javascript" src="script.js"></script>
<? require_once COMMON . 'analize.inc' # Analize script ?>
</body>
</html>