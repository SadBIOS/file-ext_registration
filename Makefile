main = main
icon_resource = icon_assy.rc
icon_obj = icon_obj
output = shell_ext_reg.exe
dll = reg_loader

default:
	windres -v $(icon_resource) -o -coff -o $(icon_obj)
	g++ -shared -O3 -v -Wpedantic -Wall -Wextra -Wwrite-strings --extra-warnings -g3 -o $(dll).dll $(dll).cpp
	g++ -L . -l $(dll) -O3 -v -Wpedantic -Wall -Wextra -Wwrite-strings --extra-warnings -g3 -o $(output) $(main).cpp $(icon_obj) -l gdi32

clean:
	powershell -Command "Remove-Item *.dll, *.exe, *.o  -Force -Verbose"
