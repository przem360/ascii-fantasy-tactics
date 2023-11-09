set pagination off
set logging file gdb.output
set logging on
set print inferior-events off

set $tests=12
set $i=0

while ($i<$tests)
    run < input.txt
    p $i=$i+1
end