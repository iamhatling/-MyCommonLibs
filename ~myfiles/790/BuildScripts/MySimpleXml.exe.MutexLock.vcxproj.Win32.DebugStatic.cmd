call "D:\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86
pushd "E:\MyProjects\~MyCommonLibs\MutexLock"
msbuild /p:UseEnv=true /p:plfatform=Win32 /p:configuration="DebugStatic" "MutexLock.vcxproj" /flp:Summary;LogFile="E:\MyProjects\~MyCommonLibs\~myfiles\790\BuildScripts\MySimpleXml.exe.MutexLock.vcxproj.Win32.DebugStatic.log"
popd
