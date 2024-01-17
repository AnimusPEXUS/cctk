#!/bin/bash

find -type f -name '*.cctkpdf' -print -exec ./_prop_gen.py '{}' ';'
