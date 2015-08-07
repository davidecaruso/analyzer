module.exports = function(grunt) {

    grunt.loadNpmTasks('grunt-wiredep');
    grunt.loadNpmTasks('grunt-contrib-watch');

    grunt.initConfig({

        watch: {
            js: {
                files: ['components/{*/}*.js']
            },
            styles: {
                files: ['components/{*/}*.css']
            },
            tasks: ['wiredep']
        },

        wiredep: {
            task: {
                src: ['index.php']
            }
        }

    });


    grunt.registerTask('default', ['wiredep']);
    grunt.registerTask('changes', ['watch']);
};

