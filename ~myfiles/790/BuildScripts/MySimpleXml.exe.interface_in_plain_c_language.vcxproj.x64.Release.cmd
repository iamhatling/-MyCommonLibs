call "D:\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64
pushd "E:\MyProjects\~MyCommonLibs\interface_in_plain_c_language"
msbuild /p:UseEnv=true /p:plfatform=x64 /p:configuration="Release" "interface_in_plain_c_language.vcxproj" /flp:Summary;LogFile="E:\MyProjects\~MyCommonLibs\~myfiles\790\BuildScripts\MySimpleXml.exe.interface_in_plain_c_language.vcxproj.x64.Release.log"
popd
