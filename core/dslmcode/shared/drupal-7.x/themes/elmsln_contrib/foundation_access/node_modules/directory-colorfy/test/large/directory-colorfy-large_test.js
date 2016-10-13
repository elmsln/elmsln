/*global require:true*/


(function(exports) {
    "use strict";

    var path = require('path');
    var fs = require('fs');
    var DirectoryColorfy = require(path.join('..', '..', 'lib', 'directory-colorfy'));

    var inputDir = path.join("test", "files", "directory-colorfy", "large"),
        outputDir = path.join("test", "files", "temp", "directory-colorfy", "large"),
        testFiles = [
            "0026-diamonds-primary.svg",
            "0119-user-tie-primary.svg",
            "0084-calendar-primary.svg",
            "0048-folder-primary.svg",
            "0026-diamonds-secondary.svg",
            "0119-user-tie-secondary.svg",
            "0084-calendar-secondary.svg",
            "0048-folder-secondary.svg"
        ],
        config = {
            colors: {
                "primary": "green",
                "secondary": "orange"
            }
        };

    function rmDirFiles(dirPath) {
        var files;
        try {
            files = fs.readdirSync(dirPath);
        } catch (e) {
            return;
        }
        if (files.length > 0) {
            for (var i = 0; i < files.length; i++) {
                var filePath = dirPath + '/' + files[i];
                if (fs.statSync(filePath).isFile()) {
                    fs.unlinkSync(filePath);
                }
            }
        }
    }

    exports.convertDir = {
        setUp: function(done) {
            rmDirFiles(outputDir);
            this.dcHuge = new DirectoryColorfy(inputDir, path.resolve(outputDir), config);
            done();
        },
        tearDown: function(done) {
            rmDirFiles(outputDir);
            done();
        },
        convertHugeDirectory: function(test) {
            test.expect(testFiles.length);
            this.dcHuge.convert()
                .then(function() {
                    testFiles.forEach(function(fileName) {
                        test.ok(fs.existsSync(path.join(outputDir, fileName)), path.join(fileName) + " is there");
                    });
                    test.done();
                })
                .catch(function(err) {
                    console.log(err);
                    test.done();
                });
        }
    };


}(typeof exports === 'object' && exports || this));
