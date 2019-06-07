#! /bin/sh

echo Run crond
/usr/sbin/crond

echo Run sshd
/usr/sbin/sshd -D
