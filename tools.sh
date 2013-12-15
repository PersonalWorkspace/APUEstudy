#!/bin/bash
ll |egrep [a-zA-Z]+tools.h|grep -v altools.h |awk '{print "#include \""$9"\""}'>altools.h 
