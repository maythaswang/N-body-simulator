printf '\nBegin building!\n\n'

./build.sh

printf '\n\nBuild Finished!\nNow running the program.\n\n'

./run.sh
printf '\n\nexit code: '
echo $?
