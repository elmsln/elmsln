# ELMS:LN Usage examples

## booting up
`bash start.sh` which will invoke the command to make it start.

We need something in invoke the commands themselves. An example is
```
docker run -v `pwd`:/source jagregory/pandoc -f markdown -t html5 input/myfile.md -o output/myfile.html
```

So we've got -f for the format coming in, -t for the format to convert to and then the inout file followed by the -o and output file. For some reason PDF is actually latex and then a .pdf extension on the file.

This could be handled with some kind of message that's structured in a very basic micro.php file to stamp down a file name to randomly generate on the input and output sides. Then it would hand it back at the end.

Possible structure:
```
{
    "token": "A-HASH-OF-OTHER-STUFF-TO-MATCH",
    "service": "pandoc",
    "ops": {
        "input": {
            "file": "whatever.md",
            "type": "markdown"
        },
        "output": {
            "file": "some-file-name.pdf",
            "type": "latex",
            "endpoint": "courses.elmsln.local/sing100/node/1/pdf-ready"
        }
    }
}
```

Endpoint would be the possibility of notifying an end point that this file has been converted. This could be a useful pattern if PDFs are generated on the fly when a node is updated, and then a referenced stuffed in an end point (as 1 example).
