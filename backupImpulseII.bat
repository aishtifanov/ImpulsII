copy *.cpp backup\*.cpp
copy *.hpp backup\*.hpp
copy *.h backup\*.h
copy *.dfm backup\*.dfm
copy *.res backup\*.res
copy *.mak backup\*.mak
copy *.exe backup\*.exe
cd backup
pkzipc -add backupIm *.*
copy backupIm.zip i:
