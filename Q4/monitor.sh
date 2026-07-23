#!/bin/bash
tail -f server.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.txt