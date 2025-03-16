
cd .

if "%1"=="" ("E:\ok\NEWFOL~2\MATLAB~1\R2020b\bin\win64\gmake"  -f circle_edit_g.mk all) else ("E:\ok\NEWFOL~2\MATLAB~1\R2020b\bin\win64\gmake"  -f circle_edit_g.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1