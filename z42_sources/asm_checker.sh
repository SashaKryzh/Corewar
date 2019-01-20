#!/bin/bash

rm -rf vm_champs/test_cor/original/*.cor
rm -rf vm_champs/test_cor/own/*.cor
KO='\033[091m[ KO ]\033[0m'
OK='\033[092m[ OK ]\033[0m'
get_error()
{
 if (( $1 == $((128 + 6)) )); then
    echo "\033[091m[ ABRT ]\033[0m"
 elif (( $1 == $((128 + 10)) )); then
    echo "\033[091m[ BUS ]\033[0m"
 elif (( $1 == $((128 + 11)) )); then
    echo "\033[091m[ SEGV ]\033[0m"
 elif (( $1 == $((128 + 4)) )); then
    echo "\033[091m[ ILL ]\033[0m"
 elif (( $1 == $((128 + 8)) )); then
    echo "\033[091m[ FPE ]\033[0m"
 elif (( $1 == $((128 + 13)) )); then
    echo "\033[091m[ PIPE ]\033[0m"
 fi
}

counter=0;
echo "\033[093m[...CREATING COR FILES...]\033[0m"
for filename in $(find . -name "*.s"); do
        original_out=$(./asm $filename);
        original_ret=$?
        echo $filename
        mv ./vm_champs/test_cor/*.cor vm_champs/test_cor/original
        own_out=$(../asm/asm $filename);
        own_ret=$?
        mv ./vm_champs/test_cor/*.cor vm_champs/test_cor/own
        get_error own_ret
        if [ $original_ret -ne $own_ret ]; then        
            echo "FAILURE: $filename"
            echo "original: $original_out"
            echo "own: $own_out"
            counter=$((counter+1))
        fi
done

echo "\033[093m[...CHECKING COR FILES...]\033[0m"
for filename in $(find vm_champs/test_cor/original/ -name '*.cor' | awk -F/ '{print $5}'); do
    if (( $(diff vm_champs/test_cor/original/$filename vm_champs/test_cor/own/$filename 2>&1 | wc -l) != '0' )); then
        counter=$((counter+1))
    fi
done
if [ $counter -eq 0 ]; then
    echo "\033[092mALL IS OK, DUDE! ;)\033[092"
else
    echo "\033[091m[...OUPS! SOMETHING FAIL :(...]\033[0m"
fi
