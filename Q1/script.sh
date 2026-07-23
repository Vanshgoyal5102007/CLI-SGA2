#!/bin/bash
total=0
dup=0
backed=0
declare -A seen_hashes

mkdir -p backup

for file in submissions/*; do
    if [ -f "$file" ]; then
        ((total++))
        hash=$(md5sum "$file" 2>> error.log | awk '{print $1}')
        
        if [[ -n "${seen_hashes[$hash]}" ]]; then
            ((dup++))
        else
            seen_hashes[$hash]=1
            cp "$file" backup/ 2>> error.log
            ((backed++))
        fi
    fi
done

echo -e "Total files processed: $total\nDuplicates found: $dup\nFiles backed up: $backed" > report.txt
cat report.txt