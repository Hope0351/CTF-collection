#!/bin/bash

python3 -u ./test_submissions.py "$1" 2>&1 | tee -a output/log.txt

