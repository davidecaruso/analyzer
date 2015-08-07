<script type="text/javascript">
    jQuery(function() {

        // Empty properties list
        function unset_properties_list() {

            var property = jQuery('#property');
            property.attr('disabled', 'disabled');
            property.empty().html(' ');
            property.append('<option disabled value="">Choose webproperty</option>');

            return false;
        }

        // Empty profiles list
        function unset_profiles_list() {

            var profile = jQuery('#profile');
            profile.attr('disabled', 'disabled');
            profile.empty().html(' ');
            profile.append('<option disabled value="">Choose profile</option>');

            return false;
        }

        // Retrieves the lists of properties and profiles, setting selected the previously choosed, otherwise setting selected the default option
        function get_props_and_profiles() {

            <?
            $_account    = isset($account_get)   && !empty($account_get) ? "'$account_get'"  : "jQuery('#account').find(':selected').val()";
            $_property   = isset($property_get)  && !empty($property_get)? "'$property_get'" : "jQuery('#property').find(':selected').val()";
            $_profile    = isset($profile_get)   && !empty($profile_get) ? "'$profile_get'"  : "jQuery('#profile').find(':selected').val()";
            ?>

            var _account     = <?= $_account ?>;
            var _property    = <?= $_property ?>;
            var _profile     = <?= $_profile ?>;

            var innerHtml = '';

            jQuery.ajax({
                url: 'report.php',
                data: 'type=all&accountId='+_account+'&propertyId='+_property,
                dataType: 'json',
                success: function (data) {
                    var property = jQuery('#property');
                    unset_properties_list();
                    property.removeAttr('disabled');

                    for (var i in data.webProperties) {
                        var selected = '';
                        if(_property == data.webProperties[i]['id']) {
                            selected = 'selected';
                            innerHtml += '<strong>' + data.webProperties[i]['name'] + ' - </strong>';
                        }
                        property.append('<option value="'+data.webProperties[i]['id']+'"'+selected+'>'+data.webProperties[i]['name']+'</option>');
                        property.trigger('contentChanged');
                    }

                    var profile = jQuery('#profile');
                    unset_profiles_list();
                    profile.removeAttr('disabled');

                    for (var i in data.profilesList) {
                        var selected2 = '';
                        if(_profile == data.profilesList[i]['id']) {
                            selected2 = 'selected';
                            innerHtml += '<span>' + data.profilesList[i]['name'] + '</span><br />';
                        }
                        profile.append('<option value="'+data.profilesList[i]['id']+'"'+selected2+'>'+data.profilesList[i]['name']+'</option>');
                        profile.trigger('contentChanged');
                    }

                    jQuery('.result-header > blockquote').prepend(innerHtml);
                }
            });
            return false;
        }


        // Load account's web-properties
        function get_properties() {
            unset_properties_list();
            unset_profiles_list();
            jQuery.ajax({
                url: 'report.php',
                data: 'type=property&accountId='+jQuery(this).val(),
                dataType: 'json',
                success: function(data) {
                    var property = jQuery('#property');
                    property.removeAttr('disabled');
                    for (var i in data) property.append('<option value="'+data[i]['id']+'">'+data[i]['name']+'</option>');
                    property.trigger('contentChanged');
                }
            });
            return false;
        }

        // Load web-properties's profiles
        function get_profiles() {
            unset_profiles_list();
            var _account = jQuery('#account').find(":selected").val();
            jQuery.ajax({
                url: 'report.php',
                data: 'type=profile&accountId='+_account+'&propertyId='+jQuery(this).val(),
                dataType: 'json',
                success: function(data) {
                    var profile = jQuery('#profile');
                    profile.removeAttr("disabled");
                    for (var i in data) profile.append('<option value="'+data[i]['id']+'">'+data[i]['name']+'</option>');
                    profile.trigger('contentChanged');
                }
            });
            return false;
        }

        // On accounts dropdown change load the web-properties list
        jQuery('#account').change(get_properties);

        // On web-properties dropdown change load the profiles list
        jQuery('#property').change(get_profiles);

        // Event for resetting and updating dropdown lists
        jQuery('select').on('contentChanged', function() {
            jQuery(this).material_select('update');
            jQuery(this).closest('.input-field').children('span.caret').remove();
        });

        // If submitted make selected the choosed voices
        <? if( $submitted ) { ?> get_props_and_profiles(); <? } ?>


        <? if( $submitted ) { ?>
        if( jQuery('#canvas').length ) {

            var data = {
                labels: [
                    <? foreach( $data_graph->rows as $data ) echo '"' . date( 'j M', strtotime( $data[0] ) ) . '", '; ?>
                ],
                datasets: [
                    {
                        label: "From <?= date( 'j M Y', strtotime( $from ) ) ?> to <?= date( 'j M Y', strtotime( $to ) ) ?>",
                        fillColor: "rgba(151,187,205,0.2)",
                        strokeColor: "rgba(151,187,205,1)",
                        pointColor: "rgba(151,187,205,1)",
                        pointStrokeColor: "#fff",
                        pointHighlightFill: "#fff",
                        pointHighlightStroke: "rgba(151,187,205,1)",
                        data: [
                            <? foreach( $data_graph->rows as $data ) echo $data[( count( $data ) - 1) ] . ', '; ?>
                        ]
                    }
                    <? /*
                    {
                        label: "Page views",
                        fillColor: "rgba(220,220,220,0.2)",
                        strokeColor: "rgba(220,220,220,1)",
                        pointColor: "rgba(220,220,220,1)",
                        pointStrokeColor: "#fff",
                        pointHighlightFill: "#fff",
                        pointHighlightStroke: "rgba(220,220,220,1)",
                        data: [
                            <? foreach( $data_graph->rows as $data ) echo ( $data[( count( $data ) - 1 ) ] > 0 ? ( $data[( count( $data ) - 2 ) ] / $data[( count( $data ) - 1 ) ] ) : 1 ) . ', '; ?>
                        ]
                    },
                    {
                        label: "Sessions",
                        fillColor: "rgba(151,187,205,0.2)",
                        strokeColor: "rgba(151,187,205,1)",
                        pointColor: "rgba(151,187,205,1)",
                        pointStrokeColor: "#fff",
                        pointHighlightFill: "#fff",
                        pointHighlightStroke: "rgba(151,187,205,1)",
                        data: [
                            <? foreach( $data_graph->rows as $data ) echo $data[( count( $data ) - 2 ) ] . ', '; ?>
                        ]
                    }
                    */ ?>
                ]
            };
            var myLineChart = new Chart(document.getElementById("canvas").getContext("2d")).Line(data);

            // Disable the chart animation
            //Chart.defaults.global = {animation: false}

            //var pieData = [
            //    {
            //        // Returning visitors
            //        value: <?//= 100 - $result['ga:percentNewVisits'] ?>//,
            //        color: "#058DC7",
            //        label: "Returning visitors",
            //        highlight: "#1CA3DD"
            //    },
            //    {
            //        // New Visitors
            //        value: <?//= str_replace( ',', '.', $result['ga:percentNewVisits'] ) ?>//,
            //        color: "#50B432",
            //        label: "New Visitors",
            //        highlight: "#64C747"
            //    }
            //
            //];
            //var myPie = new Chart(document.getElementById("canvas").getContext("2d")).Pie(pieData);

        }
        <? } ?>
    })
</script>