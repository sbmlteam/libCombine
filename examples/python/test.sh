#!/usr/bin/env bash
##############################
# Test python scripts
##############################
python printExample.py testdata/case_01.omex
rm testdata/out.omex
python createArchiveExample.py testdata/case_01.xml
python printExample.py testdata/out.omex
rm testdata/out.omex