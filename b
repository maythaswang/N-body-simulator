printf '\nBegin building!\n'

./build.sh

printf '\nBuild finished! Now running the program.\n'
printf %"$COLUMNS"s |tr " " "-"
printf '\n'

./run.sh

printf '\nexit code: '

echo $?
