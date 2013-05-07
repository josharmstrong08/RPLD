#!/bin/bash
#this script was modified from http://stackoverflow.com/questions/7708715/check-if-program-is-running-with-bash-shell-script
#it could be run as a cron job every minute to restart the rpldserver on the Pi if needed

check_process() {
  [ "$1" = "" ]  && return 0
  [ `pgrep -n $1` ] && return 1 || return 0
}

check_process "rpldserver"
[ $? -eq 0 ] && `rpldserver > /dev/null`
