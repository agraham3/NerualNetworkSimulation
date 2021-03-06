#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = outfile

#This is the target that compiles our executable 
all :
	g++ *.cpp src/*.cpp -w -Wall -I src/ -I includes/ \
	-lGL -lGLU -lglut `sdl2-config --cflags --libs` \
	-o $(OBJ_NAME)

mac:
	g++ -g -Wall *.cpp src/*.cpp -w -I src/ -I includes/ \
	-framework OpenGL \
	`sdl2-config --cflags --libs`  \
	-o $(OBJ_NAME)

run :
	./$(OBJ_NAME)
