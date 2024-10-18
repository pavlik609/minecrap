glgame:
	clang++ include/imgui/*.cpp -Wall -I include/ main.cpp src/glad.c -o test -ldl -lglfw -limgui -lstb
 
