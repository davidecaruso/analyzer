jQuery(function(){

    // Initialize menu button for mobile
    jQuery(".button-collapse").sideNav();

    // Initialize dropdownlists
    jQuery('select').material_select();

    // Initialize the datepickers
    jQuery('.datepicker').pickadate({
        selectMonths: true,
        selectYears: 5,
        format: 'd mmmm, yyyy',
        formatSubmit: 'yyyy-mm-dd'
    });

});