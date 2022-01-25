#!/bin/sh
find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=clang-format.conf -i {} \; 