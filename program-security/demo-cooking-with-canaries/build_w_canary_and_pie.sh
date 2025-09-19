#!/bin/bash

gcc -fstack-protector-all -fPIE -pie $1
