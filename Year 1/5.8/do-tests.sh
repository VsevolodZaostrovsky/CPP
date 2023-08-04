#!/bin/bash

usage() { echo "Usage: $0 [-s] [-d <tests directory>] [prog]" 1>&2; exit 1; }

while getopts ":d:s" o; do
    case "${o}" in
        s)
            use_stream=1
            ;;
        t)
            custom_tests_directory=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

INPUT_TXT=./input.txt
OUTPUT_TXT=./output.txt
test_runner=${1:-./a.out}
tests_directory=${custom_tests_directory:-./UNIT-TESTS}
tmp=last_run_results.txt
nfailed=0

if [ ! -f $test_runner ]; then
  echo "File" $test_runner "NOT FOUND."
  exit -1
fi

if [ ! -d $tests_directory ]; then
  echo "Tests directory" $tests_directory "NOT FOUND."
  exit -1
fi

cleanup () {
  rm -f $tmp
}

trap 'cleanup; exit 1' SIGINT SIGQUIT SIGTERM

for testfile in `find $tests_directory -type f -name "*\.in"`
do
  testname=`basename $testfile .in`
  expected_answer=`dirname $testfile`/${testname}.res
  expected_error=`dirname $testfile`/${testname}.err
  if [[ ! -f $expected_answer ]] && [[ ! -f $expected_error ]]; then
    echo "*** Test" $testname "does not contain corresponding .res or .err file! ***"
    continue
  fi
  # Run the test
  test_passed=0 # Set to false by default
  comment=""
  echo -E -n $testname " "
  if [ -z "${use_stream}" ]; then
    cp $testfile ${INPUT_TXT}
    $test_runner 2>/dev/null >/dev/null
    test_rc=$?
    if [ -f ${OUTPUT_TXT} ]; then
      cp ${OUTPUT_TXT} $tmp
    fi
  else
    $test_runner <$testfile 2>/dev/null >$tmp
    test_rc=$?
  fi
  # Check the answer
  if [[ $test_rc -ne 0 ]] || [[ -f $expected_error ]]; then
    if [[ $test_rc -ne 0 ]] && [[ -f $expected_error ]]; then
       test_passed=1
    else
       comment="(Wrong return code)"
    fi
  else # if [ -f $expected_answer ]; then
    diff -abBiq $tmp $expected_answer >/dev/null 2>/dev/null
    if [ $? -ne 0 ]
    then
      test_passed=0
      if [ ! -f $tmp ]; then comment="(Output file not found)"; fi
    else
      test_passed=1
    fi
  fi

  # Print status
  if [ $test_passed -eq 0 ]; then
    echo -e \\033[31m \\t "FAILED" \\033[0m $comment
    ((nfailed++))
  fi
  if [ $test_passed -eq 1 ]; then
    echo -e \\033[32m \\t "PASSED" \\033[0m
  fi
done 

cleanup
exit $nfailed

