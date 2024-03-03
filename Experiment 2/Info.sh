#!/bin/bash
#Program to display System information
echo "OS and Version"
uname -a
#echo "Release Number"
#cat /etc/os-release
echo "Kernel Version"
uname -r
#echo "All Available Shells"
#cat /etc/shells
echo "CPU Information"
cat /proc/cpuinfo
echo "Memory Information"
cat /proc/meminfo
#echo "Harddisk Information"
#lsblk
echo "FileSystem(Mounted)"
df -h
