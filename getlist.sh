#!/usr/bin/expect
set timeout 20
spawn telnet localhost nntp
send "list newsgroups\r"
send "quit\r"
expect eof
