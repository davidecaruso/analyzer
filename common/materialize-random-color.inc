<?php
/*# MATERIALIZE THEME SELECTOR
# ├ COLORS
# ├ COLORS BRIGHTNESSES
# └ COLORS INTENSITIES

# Colors
$materialize_colors = array(
    'red',
    'pink',
    'purple',
    'deep-purple',
    'indigo',
    'blue',
    'light-blue',
    'cyan',
    'teal',
    'green',
    'light-green',
    'lime',
    'yellow',
    'amber',
    'orange',
    'deep-orange',
    'brown',
    'grey',
    'blue-grey'
);

# Colors brightnesses
$materialize_brightnesses = array('', 'lighten', 'darken');

# Colors intensities
$materialize_intensities = array('-1', '-2', '-3', '-4');

# Randomize theme
$_color =       $materialize_colors[ rand(0, ( count($materialize_colors) - 1 )) ];
$_brightness =  $materialize_brightnesses[ rand(0, ( count($materialize_brightnesses) - 1) ) ];
$_intensity =   $materialize_intensities[ rand(0, ( count($materialize_intensities) - 1) ) ];

# Show all colors
echo '<ul style="width: 270px;overflow:hidden;">';
foreach($materialize_colors as $color) {
    $c = 0;
    foreach($materialize_brightnesses as $brightness) {
        foreach($materialize_intensities as $intensity) {
            if($brightness == '' && $c > 0) continue;
            echo "<li style='width: 30px; height: 30px; float:left;' class='{$color} " . ( $brightness == '' ? null : $brightness . $intensity ) . "'></li>";
            $c++;
        }
    }
}
echo '</ul>';*/

# Theme
$_color = 'light-blue';
$_brightness = 'darken';
$_intensity = '-1';