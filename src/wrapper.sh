#!/bin/bash
cat $2 | ./bin/compiler 2> /dev/null 1> $4
