#!/bin/bash

input="input.txt"
expected="expected_output.txt"
output="actual_output.txt"

./main < "$input" > "$output"

if diff -q "$output" "$expected" > /dev/null; then
    echo "Test passed."
else
    echo "Test failed!"
    diff --color "$output" "$expected"
fi