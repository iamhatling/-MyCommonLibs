call "D:\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" amd64
pushd "E:\MyProjects\~MyCommonLibs\PluginFileFactoryFileCommand"
msbuild /p:UseEnv=true /p:plfatform=x64 /p:configuration="ReleaseStatic" "PluginFileFactoryFileCommand.vcxproj" /flp:Summary;LogFile="E:\MyProjects\~MyCommonLibs\~myfiles\790\BuildScripts\MySimpleXml.exe.PluginFileFactoryFileCommand.vcxproj.x64.ReleaseStatic.log"
popd
