#!/bin/bash
gcc -fno-pie -no-pie -masm=intel -fno-stack-protector $1
