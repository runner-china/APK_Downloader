@ echo off  
wget-1.16.2-win32\wget.exe    --no-check-certificate     -t 10 --timeout=30  -c   -i apks/DownloadList__samples.txt  -P apks
echo  ======================================================
echo                        Completed!
echo  ======================================================
pause