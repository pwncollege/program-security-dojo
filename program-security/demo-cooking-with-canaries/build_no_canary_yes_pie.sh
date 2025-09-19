#!/bin/bash

gcc -fno-stack-protector -fPIE -pie $1
