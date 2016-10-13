/*global require:true*/
(function(exports) {
    "use strict";

    var path = require('path');
    var fs = require('fs');
    var DirectoryColorfy = require(path.join('..', 'lib', 'directory-colorfy'));

    var folders = ["consecutive-1", "consecutive-2"];
    var conversionsComplete = folders.length,
        conversionsRun = 0;

    var inputDir = path.join("test", "files", "directory-colorfy", "consecutive"),
        outputDirBase = path.join("test", "files", "temp", "directory-colorfy"),

        files = ["book.svg", "book-primary.svg", "book-secondary.svg",
            "cat.svg", "cat-primary.svg", "cat-secondary.svg",
            "home.svg", "home-primary.svg", "home-secondary.svg",
            "pencil.svg", "pencil-primary.svg", "pencil-secondary.svg"
        ],
        notFiles = ["bear.svg"];

    var colors = [{
        "primary": "green",
        "secondary": "orange"
    }, {
        "primary": "red",
        "secondary": "yellow"
    }];


    function removeFiles() {
        folders.forEach(function(folder) {
            files.forEach(function(base) {
                if (fs.existsSync("test/files/temp/" + folder + "/" + base)) {
                    fs.unlinkSync("test/files/temp/" + folder + "/" + base);
                }
            });
        });
    }

    function getTestOk(test, folder) {
        var pathBase = path.join(outputDirBase, folder);

        return function() {
            notFiles.forEach(function(fileName) {
                test.ok(!fs.existsSync(path.join(pathBase, fileName)), path.join(folder, fileName) + " is not there");
            });
            files.forEach(function(fileName) {
                test.ok(fs.existsSync(path.join(pathBase, fileName)), path.join(folder, fileName) + " is there");
            });

            conversionsRun++;

            if (conversionsRun === conversionsComplete) {
                test.done();
            }
        };
    }

    function getDCList() {
        return folders.map(function(folder, index) {
            return new DirectoryColorfy(inputDir, path.resolve(path.join(outputDirBase, folder)), {
                colors: colors[index]
            });
        });
    }

    exports.convertConsecutiveParallel = {
        setUp: function(done) {
            removeFiles();
            this.dcList = getDCList();
            done();
        },
        tearDown: function(done) {
            removeFiles();
            done();
        },
        convert: function(test) {
            test.expect((folders.length * files.length) + (notFiles.length * folders.length));

            conversionsRun = 0;

            this.dcList.forEach(function(dc, index) {
                dc.convert()
                    .then(getTestOk(test, folders[index]))
                    .catch(function(err) {
                        console.log(err);
                        test.done();
                    });
            });
        }
    };

    exports.convertConsecutiveSequential = {
        setUp: function(done) {
            removeFiles();
            this.dcList = getDCList();
            done();
        },
        tearDown: function(done) {
            removeFiles();
            done();
        },
        convert: function(test) {
            test.expect((folders.length * files.length) + (notFiles.length * folders.length));

            conversionsRun = 0;

            var _this = this;
            this.dcList[0].convert()
            .then(function(){
                _this.dcList[1].convert()
                .then(function(){
                    getTestOk(test, folders[0])();
                    getTestOk(test, folders[1])();
                })
                .catch(function(err){
                    console.log(err);
                    test.done();
                });
            });

        }
    };

}(typeof exports === 'object' && exports || this));
