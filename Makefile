NAME = minirt

CC= gcc

CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3

MAIN = main
CAMERA = ft_camera
CANVAS = ft_canvas
CONES = ft_cones ft_cones_2
CYLINDERS = ft_cylinders ft_cylinders_2
GNL = get_next_line get_next_line_utils
INTERSECTIONS = ft_intersections ft_intersections_2
LIGHTS = ft_lights
MATERIALS = ft_materials
MATRICES = ft_matrices ft_matrices_2 ft_matrices_3
PARSER = ft_parser ft_parser_2
PATTERNS = ft_patterns ft_patterns_2 ft_patterns_3
PLANES = ft_planes
RAYS = ft_rays
SHAPES = ft_shapes
SPHERES = ft_spheres
TRANSFORMATIONS = ft_transformations ft_transformations_2
TUPLES = ft_tuples ft_tuples_1 ft_tuples_2 ft_tuples_3
UTILS = ft_utils ft_utils_2
WORLD = ft_world ft_world_2

SRC = $(addsuffix .c, $(addprefix main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix camera/, $(CAMERA))) \
	  $(addsuffix .c, $(addprefix canvas/, $(CANVAS))) \
	  $(addsuffix .c, $(addprefix cones/, $(CONES))) \
	  $(addsuffix .c, $(addprefix cylinders/, $(CYLINDERS))) \
	  $(addsuffix .c, $(addprefix get_next_line/, $(GNL))) \
	  $(addsuffix .c, $(addprefix intersections/, $(INTERSECTIONS))) \
	  $(addsuffix .c, $(addprefix lights/, $(LIGHTS))) \
	  $(addsuffix .c, $(addprefix materials/, $(MATERIALS))) \
	  $(addsuffix .c, $(addprefix matrices/, $(MATRICES))) \
	  $(addsuffix .c, $(addprefix parser/, $(PARSER))) \
	  $(addsuffix .c, $(addprefix patterns/, $(PATTERNS))) \
	  $(addsuffix .c, $(addprefix planes/, $(PLANES))) \
	  $(addsuffix .c, $(addprefix rays/, $(RAYS))) \
	  $(addsuffix .c, $(addprefix shapes/, $(SHAPES))) \
	  $(addsuffix .c, $(addprefix spheres/, $(SPHERES))) \
	  $(addsuffix .c, $(addprefix transformations/, $(TRANSFORMATIONS))) \
	  $(addsuffix .c, $(addprefix tuples/, $(TUPLES))) \
	  $(addsuffix .c, $(addprefix utils/, $(UTILS))) \
	  $(addsuffix .c, $(addprefix world/, $(WORLD))) \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I ./includes -o $(NAME) $(OBJ) 

%.o: %.c
		@${CC} ${CFLAGS} -I ./includes -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: