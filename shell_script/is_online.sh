#!/bin/sh

if [nc -zw1 google.com 443]; then
    echo "Online1";
else
    echo "Offline";
fi