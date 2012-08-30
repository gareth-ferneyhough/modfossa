# Run Make with the "run" target in all directories
# TODO : This should probably be done as a Makefile instead...

for x in $(find . -mindepth 1 -maxdepth 1 -type d)
do
    (
        echo ---------------- $(basename $x) -----------------------
        cd $x
        make run
    )
done
