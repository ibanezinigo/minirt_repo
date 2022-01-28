NAME = minirt

CC= gcc

CFLAGS= 

MAIN= ft_main
CAMERA = ft_camera
CANVAS = ft_canvas
INTERSECTIONS = ft_intersections
LIGHTS = ft_lights
MATERIALS = ft_materials
MATRICES = ft_matrices
PATTERNS = ft_patterns
PLANES = ft_planes
RAYS = ft_rays
SHAPES = ft_shapes
SPHERES = ft_spheres
TRANSFORMATIONS = ft_transformations
TUPLES = ft_tuples
WORLD = ft_world

SRC = $(addsuffix .c, $(addprefix main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix camera/, $(CAMERA))) \
	  $(addsuffix .c, $(addprefix lights/, $(LIGHTS))) \
	  $(addsuffix .c, $(addprefix canvas/, $(CANVAS))) \
	  $(addsuffix .c, $(addprefix intersections/, $(INTERSECTIONS))) \
	  $(addsuffix .c, $(addprefix materials/, $(MATERIALS))) \
	  $(addsuffix .c, $(addprefix matrices/, $(MATRICES))) \
	  $(addsuffix .c, $(addprefix patterns/, $(PATTERNS))) \
	  $(addsuffix .c, $(addprefix planes/, $(PLANES))) \
	  $(addsuffix .c, $(addprefix rays/, $(RAYS))) \
	  $(addsuffix .c, $(addprefix shapes/, $(SHAPES))) \
	  $(addsuffix .c, $(addprefix spheres/, $(SPHERES))) \
	  $(addsuffix .c, $(addprefix transformations/, $(TRANSFORMATIONS))) \
	  $(addsuffix .c, $(addprefix tuples/, $(TUPLES))) \
	  $(addsuffix .c, $(addprefix world/, $(WORLD))) \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I ./includes -o $(NAME) $(OBJ) 

%.o: %.c
		${CC} ${CFLAGS} -I ./includes -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: