#!/bin/bash
perf stat -e LLC-misses,LLC-loads $@
